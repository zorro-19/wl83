#include "app_config.h"
#include "usb_host.h"
#include "usbnet.h"
#include "cdc_defs.h"
#include "device_drive.h"
#include "host/usb_ctrl_transfer.h"

#if TCFG_HOST_WIRELESS_ENABLE || TCFG_HOST_RNDIS_ENABLE

#define LOG_TAG_CONST       USB
#define LOG_TAG             "[net]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"

#define	EL3RST		(40)	/* Level 3 reset */
#define ETH_ALEN    (6)
/* #define	ETIMEDOUT	(238)	[> Connection timed out <] */

static USBNET_RX_COMPLETE_CB usbnet_rx_complete_cb = NULL;

static void keepalive_period_task(void *priv);
static void (*usbnet_at_port_rx_handler)(u8 *buf, u32 len) = NULL;

static int set_power(struct usb_host_device *host_dev, u32 value)
{
    return DEV_ERR_NONE;
}

static int get_power(struct usb_host_device *host_dev, u32 value)
{
    return DEV_ERR_NONE;
}

static struct wireless_device_t wireless_dev[USB_MAX_HW_NUM];

static const struct interface_ctrl wireless_ctrl = {
    .interface_class = USB_CLASS_WIRELESS_CONTROLLER,
    .set_power = set_power,
    .get_power = get_power,
    .ioctl = NULL,
};

static const struct interface_ctrl at_port_ctrl = {
    .interface_class = USB_CLASS_VENDOR_SPEC,
    .set_power = set_power,
    .get_power = get_power,
    .ioctl = NULL,
};

static const struct usb_interface_info wireless_inf[USB_MAX_HW_NUM] = {
    {
        .ctrl = (struct interface_ctrl *) &wireless_ctrl,
        .dev.wireless = &wireless_dev[0],
    },
#if USB_MAX_HW_NUM > 1
    {
        .ctrl = (struct interface_ctrl *) &wireless_ctrl,
        .dev.wireless = &wireless_dev[1],
    }
#endif
};

static const struct usb_interface_info at_port_inf[USB_MAX_HW_NUM] = {
    {
        .ctrl = (struct interface_ctrl *) &at_port_ctrl,
        .dev.wireless = &wireless_dev[0],
    },
#if USB_MAX_HW_NUM > 1
    {
        .ctrl = (struct interface_ctrl *) &at_port_ctrl,
        .dev.wireless = &wireless_dev[1],
    }
#endif
};


void __attribute__((weak)) copy_usbnet_mac_addr(u8 *mac)
{

}


void usb_net_stop_process(usb_dev usb_id)
{
    if (wireless_dev[usb_id].epin_buf) {
        usb_h_free_ep_buffer(usb_id, wireless_dev[usb_id].epin_buf);
        wireless_dev[usb_id].epin_buf = NULL;
    }
    if (wireless_dev[usb_id].epout_buf) {
        usb_h_free_ep_buffer(usb_id, wireless_dev[usb_id].epout_buf);
        wireless_dev[usb_id].epout_buf = NULL;
    }
    if (wireless_dev[usb_id].inbuf) {
        free(wireless_dev[usb_id].inbuf);
        wireless_dev[usb_id].inbuf = NULL;
    }
}


void usb_net_at_port_stop_process(usb_dev usb_id)
{
    if (wireless_dev[usb_id].epin_buf_at) {
        usb_h_free_ep_buffer(usb_id, wireless_dev[usb_id].epin_buf_at);
        wireless_dev[usb_id].epin_buf_at = NULL;
    }
    if (wireless_dev[usb_id].epout_buf_at) {
        usb_h_free_ep_buffer(usb_id, wireless_dev[usb_id].epout_buf_at);
        wireless_dev[usb_id].epout_buf_at = NULL;
    }
}


int is_wireless_rndis(struct usb_interface_descriptor *desc)
{
    return (desc->bInterfaceClass == USB_CLASS_WIRELESS_CONTROLLER &&
            desc->bInterfaceSubClass == 1 &&
            desc->bInterfaceProtocol == 3);
}


int usbnet_host_bulk_only_send(usb_dev usb_id, u8 *buf, u32 len)
{
    return usb_h_bulk_write(usb_id, wireless_dev[usb_id].host_epout, wireless_dev[usb_id].txmaxp, wireless_dev[usb_id].epout, buf, len);
}


int usbnet_host_at_data_send(usb_dev usb_id, u8 *buf, u32 len)
{
    return usb_h_bulk_write(usb_id, wireless_dev[usb_id].host_epout_at, wireless_dev[usb_id].txmaxp_at, wireless_dev[usb_id].epout_at, buf, len);
}


void usbnet_set_rx_complete_cb(USBNET_RX_COMPLETE_CB cb)
{
    usbnet_rx_complete_cb = cb;
}

int usbnet_get_rxmaxp(usb_dev usb_id)
{
    return wireless_dev[usb_id].rxmaxp;
}

void usbnet_host_bulk_only_receive_int(usb_dev usb_id)
{
    if (wireless_dev[usb_id].inbuf) {
        //触发传输由上层决定，否则buffer会有改写的风险
        usb_h_ep_read_async(usb_id, wireless_dev[usb_id].host_epin, wireless_dev[usb_id].epin, NULL, 0, USB_ENDPOINT_XFER_BULK, 1);
    }
}


static void usbnet_rx_isr(struct usb_host_device *host_dev, u32 ep)
{
    int rx_len = 0;
    usb_dev usb_id = host_device2id(host_dev);
    u32 target_ep = wireless_dev[usb_id].epin;

    if (!wireless_dev[usb_id].inbuf) {
        return;
    }

    rx_len = usb_h_ep_read_async(usb_id, ep, target_ep, wireless_dev[usb_id].inbuf, wireless_dev[usb_id].rxmaxp, USB_ENDPOINT_XFER_BULK, 0);
    if (rx_len > 0 && usbnet_rx_complete_cb) {
        usbnet_rx_complete_cb(usb_id, wireless_dev[usb_id].inbuf, rx_len);
    }
    if (rx_len <= 0 || !usbnet_rx_complete_cb) {
        usb_h_ep_read_async(usb_id, ep, target_ep, NULL, 0, USB_ENDPOINT_XFER_BULK, 1);
    }
}


void usbnet_at_port_rx_handler_register(void (*func)(u8 *buf, u32 len))
{
    usbnet_at_port_rx_handler = func;
}


static void usbnet_at_port_rx_isr(struct usb_host_device *host_dev, u32 ep)
{
    int rx_len = 0;
    usb_dev usb_id = host_device2id(host_dev);
    u32 target_ep = wireless_dev[usb_id].epin_at;
    u8 usb_recv_buf[64];
    u8 usb_recv_len = sizeof(usb_recv_buf);

    /* printf("usb%d lte rx hep %d %d tep %d \n", usb_id, ep, wireless_dev.host_epin_at, target_ep); */
    rx_len = usb_h_ep_read_async(usb_id, ep, target_ep, usb_recv_buf, usb_recv_len, USB_ENDPOINT_XFER_BULK, 0);
    if (rx_len > 0) {
        if (usbnet_at_port_rx_handler) {
            usbnet_at_port_rx_handler(usb_recv_buf, rx_len);
        }
    }

    usb_h_ep_read_async(usb_id, ep, target_ep, NULL, 0, USB_ENDPOINT_XFER_BULK, 1);
}


s32 usbnet_at_port_parser(struct usb_host_device *host_dev, u8 interface_num, const u8 *pBuf)
{
    s32 len = 0;
    u8 rx_interval = 0;
    const usb_dev usb_id = host_device2id(host_dev);
    struct usb_endpoint_descriptor *end_desc = NULL;
    struct usb_interface_descriptor *interface = NULL;
    host_dev->interface_info[interface_num] = &at_port_inf[usb_id];

    u32 cur_len;
    u32 cur_type;
    u32 cur_subtype;
    u8 is_next_interface = 0;
    u8 stage = 0;
    const u8 cs_interface_1[] = {0x05, 0x24, 0x00, 0x10, 0x01};
    const u8 cs_interface_2[] = {0x05, 0x24, 0x01, 0x00, 0x00};
    const u8 cs_interface_3[] = {0x04, 0x24, 0x02, 0x02};
    const u8 cs_interface_4[] = {0x05, 0x24, 0x06, 0x00, 0x00};

    while (1) {
        cur_len = pBuf[len + 0];
        cur_type = pBuf[len + 1];
        cur_subtype = pBuf[len + 2];

        /* printf("cur_len = %x, cur_type = %x, cur_subtype = %x", cur_len, cur_type, cur_subtype); */

        if (cur_type == USB_DT_INTERFACE_ASSOCIATION) {
            if (is_next_interface) {
                break;
            }
            /* put_buf(pBuf + len, cur_len); */
        } else if (cur_type == USB_DT_INTERFACE) {
            interface = (struct usb_interface_descriptor *)(pBuf + len);
            if (interface->bLength != USB_DT_INTERFACE_SIZE) {
                break;
            }
            if (is_next_interface) {
                break;
            }
            is_next_interface = 1;
            /* put_buf(pBuf + len, cur_len); */
        } else if (cur_type == USB_DT_CS_INTERFACE) {
            /* put_buf(pBuf + len, cur_len); */
            switch (stage) {
            case 0:
                if (!memcmp(pBuf + len, cs_interface_1, sizeof(cs_interface_1))) {
                    stage = 1;
                } else {
                    stage = 0;
                }
                break;
            case 1:
                if (!memcmp(pBuf + len, cs_interface_2, sizeof(cs_interface_2))) {
                    stage = 2;
                } else {
                    stage = 0;
                }
                break;
            case 2:
                if (!memcmp(pBuf + len, cs_interface_3, sizeof(cs_interface_3))) {
                    stage = 3;
                } else {
                    stage = 0;
                }
                break;
            case 3:
                if (!memcmp(pBuf + len, cs_interface_4, sizeof(cs_interface_4))) {
                    stage = 4;
                } else {
                    stage = 0;
                }
                break;
            }
        } else if (cur_type == USB_DT_ENDPOINT) {
            /* put_buf(pBuf + len, cur_len); */
            end_desc = (struct usb_endpoint_descriptor *)(pBuf + len);
            if (stage != 4) { //过滤符合AT COM的CS INTERFACE
                goto __parser_next;
            }

            if ((end_desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_BULK) {
                if (end_desc->bEndpointAddress & USB_DIR_IN) {
                    if (end_desc->bEndpointAddress != 0x84 && \
                        end_desc->bEndpointAddress != 0x86) {  //4G模块有好几个接形式一样的interface-endpoint接口，固定取AT COM端点
                        goto __parser_next;
                    }
                    wireless_dev[usb_id].host_epin_at = usb_get_ep_num(usb_id, USB_DIR_IN, USB_ENDPOINT_XFER_BULK);
                    wireless_dev[usb_id].epin_at   = end_desc->bEndpointAddress & 0x0f;
                    wireless_dev[usb_id].rxmaxp_at = end_desc->wMaxPacketSize;
                    rx_interval = end_desc->bInterval;
                    log_info("AT IN : id = %d, host_epin_at = %d, epin_at = %d, rxmaxp_at = %d", usb_id, wireless_dev[usb_id].host_epin_at, wireless_dev[usb_id].epin_at, wireless_dev[usb_id].rxmaxp_at);
                    if (usb_id == 0) {
                        wireless_dev[usb_id].rxmaxp_at = 64;
                    }
#if HUSB_MODE && (FUSB_MODE == 0)
                    if (wireless_dev[usb_id].rxmaxp_at > 512) {
                        wireless_dev[usb_id].rxmaxp_at = 512;
                    }
#endif
                    usb_h_set_ep_isr(host_dev, wireless_dev[usb_id].host_epin_at | USB_DIR_IN, usbnet_at_port_rx_isr, host_dev);
                    if (!wireless_dev[usb_id].epin_buf_at) {
                        wireless_dev[usb_id].epin_buf_at = usb_h_alloc_ep_buffer(usb_id, wireless_dev[usb_id].host_epin_at | USB_DIR_IN, wireless_dev[usb_id].rxmaxp_at * 2);
                    }
#if USB_HUB
                    usb_hub_rxreg_set(usb_id, wireless_dev[usb_id].host_epin_at, wireless_dev[usb_id].epin_at, &(host_dev->private_data.hub_info));
#else
                    usb_write_rxfuncaddr(usb_id, wireless_dev[usb_id].host_epin_at, host_dev->private_data.devnum);
#endif
                    /* usb_write_rxfuncaddr(usb_id, wireless_dev[usb_id].host_epin_at, host_dev->private_data.devnum); */
                    usb_h_ep_config(usb_id, wireless_dev[usb_id].host_epin_at | USB_DIR_IN, USB_ENDPOINT_XFER_BULK, 1, rx_interval, wireless_dev[usb_id].epin_buf_at, wireless_dev[usb_id].rxmaxp_at);

                    usb_h_ep_read_async(usb_id, wireless_dev[usb_id].host_epin_at, wireless_dev[usb_id].epin_at, NULL, 0, USB_ENDPOINT_XFER_BULK, 1);
                } else {
                    if (end_desc->bEndpointAddress != 0x03 && \
                        end_desc->bEndpointAddress != 0x0F) {  //4G模块有好几个接形式一样的interface-endpoint接口，固定取AT COM端点
                        goto __parser_next;
                    }
                    wireless_dev[usb_id].host_epout_at = usb_get_ep_num(usb_id, USB_DIR_OUT, USB_ENDPOINT_XFER_BULK);
                    wireless_dev[usb_id].epout_at  = end_desc->bEndpointAddress & 0x0f;
                    wireless_dev[usb_id].txmaxp_at = end_desc->wMaxPacketSize;
                    log_info("AT OUT : id = %d, host_epout_at = %d, epout_at = %d, txmaxp_at = %d", usb_id, wireless_dev[usb_id].host_epout_at, wireless_dev[usb_id].epout_at, wireless_dev[usb_id].txmaxp_at);
                    if (usb_id == 0) {
                        wireless_dev[usb_id].txmaxp_at = 64;
                    }
#if HUSB_MODE && (FUSB_MODE == 0)
                    if (wireless_dev[usb_id].txmaxp_at > 512) {
                        wireless_dev[usb_id].txmaxp_at = 512;
                    }
#endif
                    if (!wireless_dev[usb_id].epout_buf_at) {
                        wireless_dev[usb_id].epout_buf_at = usb_h_alloc_ep_buffer(usb_id, wireless_dev[usb_id].host_epout_at | USB_DIR_OUT, wireless_dev[usb_id].txmaxp_at);
                    }
#if USB_HUB
                    usb_hub_txreg_set(usb_id, wireless_dev[usb_id].host_epout_at, wireless_dev[usb_id].epout_at, &(host_dev->private_data.hub_info));
#else
                    usb_write_txfuncaddr(usb_id, wireless_dev[usb_id].host_epout_at, host_dev->private_data.devnum);
#endif

                    /* usb_write_txfuncaddr(usb_id, wireless_dev[usb_id].host_epout_at, host_dev->private_data.devnum); */
                    usb_h_ep_config(usb_id, wireless_dev[usb_id].host_epout_at | USB_DIR_OUT, USB_ENDPOINT_XFER_BULK, 0, 0, wireless_dev[usb_id].epout_buf_at, wireless_dev[usb_id].txmaxp_at);
                }
            }
        } else if (cur_type == USB_DT_CS_ENDPOINT) {
            /* put_buf(pBuf + len, cur_len); */
        } else {
            break;
        }
__parser_next:
        len += cur_len;
    }

    return len;
}


s32 usbnet_generic_cdc_parser(struct usb_host_device *host_dev, u8 interface_num, const u8 *pBuf)
{
    int len = 0;
    u8 rx_interval = 0;
    const usb_dev usb_id = host_device2id(host_dev);
    host_dev->interface_info[interface_num] = &wireless_inf[usb_id];
    struct usb_interface_descriptor *interface = (struct usb_interface_descriptor *)pBuf;
    wireless_inf[usb_id].dev.wireless->parent = host_dev;
    struct usb_endpoint_descriptor *end_desc = NULL;
    const u8 *buf = pBuf;

    if (interface->bInterfaceClass == USB_CLASS_CDC_DATA) {
        log_info("usb_cdc_parser");
        len += sizeof(struct usb_interface_descriptor);
        goto __set_config;
    }

    len += sizeof(struct usb_interface_descriptor);
    buf += sizeof(struct usb_interface_descriptor);

    while (1) {
        if (buf[1] != USB_DT_CS_INTERFACE) {
            if (buf[1] == USB_DT_INTERFACE_ASSOCIATION) { //下一个设备
                break;
            }
            goto next_desc;
        }
        /* use bDescriptorSubType to identify the CDC descriptors.
         * We expect devices with CDC header and union descriptors.
         * For CDC Ethernet we need the ethernet descriptor.
         * For RNDIS, ignore two (pointless) CDC modem descriptors
         * in favor of a complicated OID-based RPC scheme doing what
         * CDC Ethernet achieves with a simple descriptor.
         */
        switch (buf[2]) {
        case USB_CDC_HEADER_TYPE:
            break;

        case USB_CDC_ACM_TYPE:
            /* paranoia:  disambiguate a "real" vendor-specific
             * modem interface from an RNDIS non-modem.
             */
            break;

        case USB_CDC_UNION_TYPE:
            len += buf [0];	/* bLength */
            buf += buf [0];
            if (buf[1] == USB_DT_ENDPOINT) {
                len += USB_DT_ENDPOINT_SIZE;
                len += USB_DT_INTERFACE_SIZE;

__set_config:
                for (int endnum = 0; endnum < 2; endnum++) {
                    end_desc = (struct usb_endpoint_descriptor *)(pBuf + len);

                    if (end_desc->bDescriptorType != USB_DT_ENDPOINT ||
                        end_desc->bLength < USB_DT_ENDPOINT_SIZE) {
                        return -USB_DT_ENDPOINT;
                    }
                    len += USB_DT_ENDPOINT_SIZE;

                    if ((end_desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_BULK) {
                        if (end_desc->bEndpointAddress & USB_DIR_IN) {
                            wireless_dev[usb_id].host_epin = usb_get_ep_num(usb_id, USB_DIR_IN, USB_ENDPOINT_XFER_BULK);
                            wireless_dev[usb_id].epin   = end_desc->bEndpointAddress & 0x0f;
                            wireless_dev[usb_id].rxmaxp = end_desc->wMaxPacketSize;
                            if (usb_id == 0) {
                                wireless_dev[usb_id].rxmaxp = 64;
                            }
#if HUSB_MODE && (FUSB_MODE == 0)
                            if (wireless_dev[usb_id].rxmaxp > 512) {
                                wireless_dev[usb_id].rxmaxp = 512;
                            }
#endif
                            rx_interval = end_desc->bInterval;
                            log_info("CDC IN : id = %d, host_epin = %d, epin = %d, rxmaxp = %d", usb_id, wireless_dev[usb_id].host_epin, wireless_dev[usb_id].epin, wireless_dev[usb_id].rxmaxp);
                        } else {
                            wireless_dev[usb_id].host_epout = usb_get_ep_num(usb_id, USB_DIR_OUT, USB_ENDPOINT_XFER_BULK);
                            wireless_dev[usb_id].epout  = end_desc->bEndpointAddress & 0x0f;
                            wireless_dev[usb_id].txmaxp = end_desc->wMaxPacketSize;
                            if (usb_id == 0) {
                                wireless_dev[usb_id].txmaxp = 64;
                            }
#if HUSB_MODE && (FUSB_MODE == 0)
                            if (wireless_dev[usb_id].txmaxp > 512) {
                                wireless_dev[usb_id].txmaxp = 512;
                            }
#endif
                            log_info("CDC OUT2 : id = %d, host_epout = %d, epout = %d, txmaxp = %d", usb_id, wireless_dev[usb_id].host_epout, wireless_dev[usb_id].epout, wireless_dev[usb_id].txmaxp);
                        }
                    }
                }

                usb_h_set_ep_isr(host_dev, wireless_dev[usb_id].host_epin | USB_DIR_IN, usbnet_rx_isr, host_dev);
                if (!wireless_dev[usb_id].epin_buf) {
                    wireless_dev[usb_id].epin_buf = usb_h_alloc_ep_buffer(usb_id, wireless_dev[usb_id].host_epin | USB_DIR_IN, wireless_dev[usb_id].rxmaxp * 2);
                }
                if (!wireless_dev[usb_id].inbuf) {
                    wireless_dev[usb_id].inbuf = malloc(wireless_dev[usb_id].rxmaxp);
                }
#if USB_HUB
                usb_hub_rxreg_set(usb_id, wireless_dev[usb_id].host_epin, wireless_dev[usb_id].epin, &(host_dev->private_data.hub_info));
#else
                usb_write_rxfuncaddr(usb_id, wireless_dev[usb_id].host_epin, host_dev->private_data.devnum);
#endif
                /* usb_write_rxfuncaddr(usb_id, wireless_dev[usb_id].host_epin, host_dev->private_data.devnum); */
                usb_h_ep_config(usb_id, wireless_dev[usb_id].host_epin | USB_DIR_IN, USB_ENDPOINT_XFER_BULK, 1, rx_interval, wireless_dev[usb_id].epin_buf, wireless_dev[usb_id].rxmaxp);

                if (!wireless_dev[usb_id].epout_buf) {
                    wireless_dev[usb_id].epout_buf = usb_h_alloc_ep_buffer(usb_id, wireless_dev[usb_id].host_epout | USB_DIR_OUT, wireless_dev[usb_id].txmaxp);
                }

#if USB_HUB
                usb_hub_txreg_set(usb_id, wireless_dev[usb_id].host_epout, wireless_dev[usb_id].epout, &(host_dev->private_data.hub_info));
#else
                usb_write_txfuncaddr(usb_id, wireless_dev[usb_id].host_epout, host_dev->private_data.devnum);
#endif

                /* usb_write_txfuncaddr(usb_id, wireless_dev[usb_id].host_epout, host_dev->private_data.devnum); */
                usb_h_ep_config(usb_id, wireless_dev[usb_id].host_epout | USB_DIR_OUT, USB_ENDPOINT_XFER_BULK, 0, 0, wireless_dev[usb_id].epout_buf, wireless_dev[usb_id].txmaxp);

                /* usb_h_ep_read_async(usb_id, wireless_dev[usb_id].host_epin, wireless_dev[usb_id].epin, NULL, 0, USB_ENDPOINT_XFER_BULK, 1); */
            }
            return len;
        /* break; */

        case USB_CDC_ETHERNET_TYPE:
            break;

        case USB_CDC_MDLM_TYPE:
            break;

        case USB_CDC_MDLM_DETAIL_TYPE:
            break;
        }
next_desc:
        len += buf[0];	/* bLength */
        buf += buf[0];
    }

    return len;
}


/*
 * RPC done RNDIS-style.  Caller guarantees:
 * -rndis_command message is properly byteswapped
 * - there's no other request pending
 * - buf can hold up to 1KB response (required by RNDIS spec)
 * On return, the first few entries are already byteswapped.
 *
 * Call context is likely probe(), before interface name is known,
 * which is why we won't try to use it in the diagnostics.
 */
int rndis_command(struct usb_host_device *device, struct rndis_msg_hdr *buf, int buflen)
{
    int			master_ifnum;
    int			retval;
    unsigned		count;
    __le32			rsp;
    static u32			xid = 0;
    u32			 msg_len, request_id;

    /* REVISIT when this gets called from contexts other than probe() or
     * disconnect(): either serialize, or dispatch responses on xid
     */

    /* Issue the request; xid is unique, don't bother byteswapping it */
    if (likely(buf->msg_type != RNDIS_MSG_HALT &&
               buf->msg_type != RNDIS_MSG_RESET)) {
        xid++;
        if (!xid) {
            xid++;
        }
        buf->request_id = (__le32) xid;
    }
    master_ifnum = 0;//info->control->cur_altsetting->desc.bInterfaceNumber;//控制接口描述符
    retval = usb_control_msg(device,
                             USB_CDC_SEND_ENCAPSULATED_COMMAND,//0x00
                             USB_TYPE_CLASS | USB_RECIP_INTERFACE,//0x21
                             0, master_ifnum,
                             buf, le32_to_cpu(buf->msg_len)
                            );
    if (unlikely(retval < 0 || xid == 0)) {
        return retval;
    }
    /* Poll the control channel; the request probably completed immediately */
    rsp = buf->msg_type | RNDIS_MSG_COMPLETION;
    for (count = 0; count < 10; count++) {
        memset(buf, 0, CONTROL_BUFFER_SIZE);
        retval = usb_control_msg(device,
                                 USB_CDC_GET_ENCAPSULATED_RESPONSE,
                                 USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
                                 0, master_ifnum,
                                 buf, buflen);

        if (likely(retval == 0)) {
            msg_len = le32_to_cpu(buf->msg_len);
            request_id = (u32) buf->request_id;
            if (likely(buf->msg_type == rsp)) {
                if (likely(request_id == xid)) {
                    /* log_info( */
                    /*     "rndis reply status %08x\n", */
                    /*     le32_to_cpu(buf->status)); */
                    if (unlikely(rsp == RNDIS_MSG_RESET_C)) {
                        return 0;
                    } else if (unlikely(rsp == RNDIS_MSG_KEEPALIVE_C)) {
                        log_info("RNDIS_MSG_KEEPALIVE_C");
                        return 0;
                    }

                    if (likely(RNDIS_STATUS_SUCCESS == buf->status)) {
                        return 0;
                    }

                    return -EL3RST;
                }
                log_info(
                    "rndis reply id %d expected %d",
                    request_id, xid);
                /* then likely retry */
            } else switch (buf->msg_type) {
                case RNDIS_MSG_INDICATE:	/* fault/event */
                    //rndis_msg_indicate(dev, (void *)buf, buflen);
                    log_info("RNDIS_MSG_INDICATE");
                    /* put_buf(buf, buflen); */
                    break;
                case RNDIS_MSG_KEEPALIVE: {	/* ping */
                    struct rndis_keepalive_c *msg = (void *)buf;

                    msg->msg_type = RNDIS_MSG_KEEPALIVE_C;
                    msg->msg_len = cpu_to_le32(sizeof * msg);
                    msg->status = RNDIS_STATUS_SUCCESS;
                    retval = usb_control_msg(device,
                                             USB_CDC_SEND_ENCAPSULATED_COMMAND,
                                             USB_TYPE_CLASS | USB_RECIP_INTERFACE,
                                             0, master_ifnum,
                                             msg, sizeof * msg
                                            );
                    if (unlikely(retval < 0))
                        log_info(
                            "rndis keepalive err %d",
                            retval);
                }
                break;
                default:
                    log_info(
                        "unexpected rndis msg %08x len %d",
                        le32_to_cpu(buf->msg_type), msg_len);
                    break;
                }
        } else {
            /* device probably issued a protocol stall; ignore */
            log_error("rndis response error, code %d\n", retval);
        }
        msleep(20);
    }
    log_error("rndis response timeout\n");
    return -ETIMEDOUT;
}


/*
 * rndis_query:
 *
 * Performs a query for @oid along with 0 or more bytes of payload as
 * specified by @in_len. If @reply_len is not set to -1 then the reply
 * length is checked against this value, resulting in an error if it
 * doesn't match.
 *
 * NOTE: Adding a payload exactly or greater than the size of the expected
 * response payload is an evident requirement MSFT added for ActiveSync.
 *
 * The only exception is for OIDs that return a variably sized response,
 * in which case no payload should be added.  This undocumented (and
 * nonsensical!) issue was found by sniffing protocol requests from the
 * ActiveSync 4.1 Windows driver.
 */
static int rndis_query(struct usb_host_device *device,
                       void *buf, __le32 oid, u32 in_len,
                       void **reply, int *reply_len)
{
    int retval;
    union {
        void			*buf;
        struct rndis_msg_hdr	*header;
        struct rndis_query	*get;
        struct rndis_query_c	*get_c;
    } u;
    u32 off, len;

    u.buf = buf;

    memset(u.get, 0, sizeof * u.get + in_len);
    u.get->msg_type = RNDIS_MSG_QUERY;
    u.get->msg_len = cpu_to_le32(sizeof * u.get + in_len);
    u.get->oid = oid;
    u.get->len = cpu_to_le32(in_len);
    u.get->offset = cpu_to_le32(20);

    /* put_buf((u8*)u.header,u.header->msg_len); */

    retval = rndis_command(device, u.header, CONTROL_BUFFER_SIZE);
    if (unlikely(retval < 0)) {
        log_error("RNDIS_MSG_QUERY(0x%08x) failed, %d\n",
                  oid, retval);
        return retval;
    }

    off = le32_to_cpu(u.get_c->offset);
    len = le32_to_cpu(u.get_c->len);

    if (unlikely((8 + off + len) > CONTROL_BUFFER_SIZE)) {
        goto response_error;
    }

    if (*reply_len != -1 && len != *reply_len) {
        goto response_error;
    }

    *reply = (unsigned char *) &u.get_c->request_id + off;
    *reply_len = len;

    return retval;

response_error:
    log_error("RNDIS_MSG_QUERY(0x%08x) "
              "invalid response - off %d len %d\n",
              oid, off, len);
    return -EDOM;
}


int generic_rndis_bind(struct usb_host_device *device, int flags)
{
    int			retval;

    union {
        void			           *buf;
        struct rndis_msg_hdr	   *header;
        struct rndis_init	       *init;
        struct rndis_init_c	       *init_c;
        struct rndis_query	       *get;
        struct rndis_query_c       *get_c;
        struct rndis_set	       *set;
        struct rndis_set_c	       *set_c;
        struct rndis_halt	       *halt;
        struct rndis_keepalive     *alive;
        struct rndis_keepalive_c   *alive_c;
    } u;
    u32	tmp;
    __le32	phym_unspec, *phym, *conn_status = NULL;
    int	reply_len;
    unsigned char *bp;

    /* we can't rely on i/o from stack working, or stack allocation */
    u.buf = malloc(CONTROL_BUFFER_SIZE);
    if (!u.buf) {
        return -ENOMEM;
    }

    //retval = usbnet_generic_cdc_bind(dev, intf);

    u.init->msg_type = RNDIS_MSG_INIT;
    u.init->msg_len = cpu_to_le32(sizeof * u.init);
    u.init->major_version = cpu_to_le32(1);
    u.init->minor_version = cpu_to_le32(0);
    u.init->max_transfer_size = 0x4000;

    retval = rndis_command(device, u.header, CONTROL_BUFFER_SIZE);

    if (unlikely(retval < 0)) {
        /* it might not even be an RNDIS device!! */
        log_error("RNDIS init failed, %d\n", retval);
        goto fail_and_release;
    }
    log_info("RNDIS_MSG_INIT_C:\r\n \
              status = %d\r\n \
              major_version = %d\r\n \
              minor_version = %d\r\n \
              device_flags = %d\r\n \
              medium = %d\r\n \
              max_packets_per_message = %d\r\n \
              max_transfer_size = %d\r\n \
              packet_alignment = %d\r\n \
              af_list_offset = %d\r\n \
              af_list_size = %d\n", \
             u.init_c->status, u.init_c->major_version, u.init_c->minor_version, u.init_c->device_flags, u.init_c->medium, \
             u.init_c->max_packets_per_message, u.init_c->max_transfer_size, u.init_c->packet_alignment, \
             u.init_c->af_list_offset, u.init_c->af_list_size);

    tmp = le32_to_cpu(u.init_c->max_transfer_size);
#if 0
    if (tmp < dev->hard_mtu) {
        if (tmp <= net->hard_header_len) {
            log_info(
                "dev can't take %u byte packets (max %u)\n",
                dev->hard_mtu, tmp);
            retval = -EINVAL;
            goto halt_fail_and_release;
        }
        dev_warn(
            "dev can't take %u byte packets (max %u), "
            "adjusting MTU to %u\n",
            dev->hard_mtu, tmp, tmp - net->hard_header_len);
        dev->hard_mtu = tmp;
        net->mtu = dev->hard_mtu - net->hard_header_len;
    }

    /* REVISIT:  peripheral "alignment" request is ignored ... */
    log_info(
        "hard mtu %u (%u from dev), rx buflen %Zu, align %d\n",
        dev->hard_mtu, tmp, dev->rx_urb_size,
        1 << le32_to_cpu(u.init_c->packet_alignment));



    /* module has some device initialization code needs to be done right
     * after RNDIS_INIT */
    if (dev->driver_info->early_init &&
        dev->driver_info->early_init(dev) != 0) {
        goto halt_fail_and_release;
    }

    /* Check physical medium */

#endif
    phym = NULL;
    reply_len = sizeof * phym;
    retval = rndis_query(device, u.buf, OID_GEN_PHYSICAL_MEDIUM,
                         0, (void **) &phym, &reply_len);

    /* log_info("QUERY->OID_GEN_PHYSICAL_MEDIUM, retval = %d, phym = %x", retval, *phym); */

    if (retval != 0 || !phym) {
        /* OID is optional so don't fail here. */
        phym_unspec = RNDIS_PHYSICAL_MEDIUM_UNSPECIFIED;
        phym = &phym_unspec;
    }
    if ((flags & FLAG_RNDIS_PHYM_WIRELESS) &&
        *phym != RNDIS_PHYSICAL_MEDIUM_WIRELESS_LAN) {
        log_error("driver requires wireless physical medium, but device is not\n");
        retval = -ENODEV;
        goto halt_fail_and_release;
    }
    if ((flags & FLAG_RNDIS_PHYM_NOT_WIRELESS) &&
        *phym == RNDIS_PHYSICAL_MEDIUM_WIRELESS_LAN) {
        log_error("driver requires non-wireless physical medium, but device is wireless\n");
        retval = -ENODEV;
        goto halt_fail_and_release;
    }

    reply_len = sizeof * phym;
    retval = rndis_query(device, u.buf, OID_GEN_MEDIA_CONNECT_STATUS,
                         0, (void **)&conn_status, &reply_len);
    log_info("QUERY->OID_GEN_MEDIA_CONNECT_STATUS, retval = %d, conn_status = %x", retval, *conn_status);


    reply_len = ETH_ALEN;
    retval = rndis_query(device, u.buf, OID_802_3_CURRENT_ADDRESS,
                         48, (void **) &bp, &reply_len);

    log_info("QUERY->OID_802_3_CURRENT_ADDRESS, retval = %d: \
              addr = [%X:%X:%X:%X:%X:%X]", retval, bp[0], bp[1], bp[2], bp[3], bp[4], bp[5]);

    /* Get designated host ethernet address */
    reply_len = ETH_ALEN;
    retval = rndis_query(device, u.buf, OID_802_3_PERMANENT_ADDRESS,
                         48, (void **) &bp, &reply_len);

    if (unlikely(retval < 0)) {
        log_error("rndis get ethaddr, %d\n", retval);
        goto halt_fail_and_release;
    }
    log_info("QUERY->OID_802_3_PERMANENT_ADDRESS: \
              addr = [%X:%X:%X:%X:%X:%X]", bp[0], bp[1], bp[2], bp[3], bp[4], bp[5]);
    copy_usbnet_mac_addr(bp);

#if 0
    memcpy(net->dev_addr, bp, ETH_ALEN);
    memcpy(net->perm_addr, bp, ETH_ALEN);
#endif

    /* set a nonzero filter to enable data transfers */
#if 0
    memset(u.set, 0, sizeof * u.set);
    u.set->msg_type = RNDIS_MSG_SET;
    u.set->msg_len = cpu_to_le32(4 + sizeof * u.set);
    u.set->oid = OID_GEN_CURRENT_PACKET_FILTER;
    u.set->len = cpu_to_le32(4);
    u.set->offset = cpu_to_le32((sizeof * u.set) - 8);
    *(__le32 *)(u.buf + sizeof * u.set) = RNDIS_DEFAULT_FILTER;


    /* put_buf((u8*)u.header,u.header->msg_len); */

    retval = rndis_command(device, u.header, CONTROL_BUFFER_SIZE);
    log_info("SET->RNDIS_DEFAULT_FILTER:\r\n \
              status = %d\n", u.set_c->status);

    if (unlikely(retval < 0)) {
        log_info("rndis set packet filter, %d\n", retval);
        goto halt_fail_and_release;
    }

#else
    ////////////////////////////////////////////////////////
    memset(u.set, 0, sizeof * u.set);
    u.set->msg_type = RNDIS_MSG_SET;
    u.set->msg_len = cpu_to_le32(4 + sizeof * u.set);
    u.set->oid = OID_GEN_CURRENT_PACKET_FILTER;
    u.set->len = cpu_to_le32(4);
    u.set->offset = cpu_to_le32((sizeof * u.set) - 8);
    *(__le32 *)((u8 *)u.buf + sizeof * u.set) = cpu_to_le32(0x03);
    /* put_buf(u.set, 4 + sizeof * u.set); */
    retval = rndis_command(device, u.header, CONTROL_BUFFER_SIZE);
    log_info("SET->RNDIS_DEFAULT_FILTER, 0x03:  retval = %d", retval);

    u8 val[6] = {0x33, 0x33, 0x00, 0x00, 0x00, 0x01};
    memset(u.set, 0, sizeof * u.set);
    u.set->msg_type = RNDIS_MSG_SET;
    u.set->msg_len = cpu_to_le32(6 + sizeof * u.set);
    u.set->oid = OID_802_3_MULTICAST_LIST;
    u.set->len = cpu_to_le32(6);
    u.set->offset = cpu_to_le32((sizeof * u.set) - 8);
    memcpy((__le32 *)((u8 *)u.buf + sizeof * u.set), val, 6);
    /* put_buf(u.set, 6 + sizeof * u.set); */
    retval = rndis_command(device, u.header, CONTROL_BUFFER_SIZE);
    log_info("SET->OID_802_3_MULTICAST_LIST:  retval = %d", retval);

    memset(u.set, 0, sizeof * u.set);
    u.set->msg_type = RNDIS_MSG_SET;
    u.set->msg_len = cpu_to_le32(4 + sizeof * u.set);
    u.set->oid = OID_GEN_CURRENT_PACKET_FILTER;
    u.set->len = cpu_to_le32(4);
    u.set->offset = cpu_to_le32((sizeof * u.set) - 8);
    *(__le32 *)((u8 *)u.buf + sizeof * u.set) = cpu_to_le32(0x07);
    /* put_buf(u.set, 4 + sizeof * u.set); */
    retval = rndis_command(device, u.header, CONTROL_BUFFER_SIZE);
    log_info("SET->RNDIS_DEFAULT_FILTER, 0x07:  retval = %d", retval);

    memset(u.set, 0, sizeof * u.set);
    u.set->msg_type = RNDIS_MSG_SET;
    u.set->msg_len = cpu_to_le32(4 + sizeof * u.set);
    u.set->oid = OID_GEN_CURRENT_PACKET_FILTER;
    u.set->len = cpu_to_le32(4);
    u.set->offset = cpu_to_le32((sizeof * u.set) - 8);
    *(__le32 *)((u8 *)u.buf + sizeof * u.set) = cpu_to_le32(0x0f);
    /* put_buf(u.set, 4 + sizeof * u.set); */
    retval = rndis_command(device, u.header, CONTROL_BUFFER_SIZE);
    log_info("SET->RNDIS_DEFAULT_FILTER, 0x0f:  retval = %d", retval);
#endif

    memset(u.alive, 0, sizeof * u.alive);
    u.alive->msg_type = RNDIS_MSG_KEEPALIVE;
    u.alive->msg_len = cpu_to_le32(sizeof * u.alive);
    retval = rndis_command(device, u.header, CONTROL_BUFFER_SIZE);
    log_info("SET->RNDIS_MSG_KEEPALIVE, retval = %d", retval);

    /* thread_fork("keepalive_period_task", 6, 512, 0, NULL, keepalive_period_task, NULL); */
    ////////////////////////////////////////////////////////

    retval = 0;

    free(u.buf);

    return retval;

halt_fail_and_release:
    memset(u.halt, 0, sizeof * u.halt);
    u.halt->msg_type = RNDIS_MSG_HALT;
    u.halt->msg_len = cpu_to_le32(sizeof * u.halt);

    (void) rndis_command(device, (void *)u.halt, CONTROL_BUFFER_SIZE);
fail_and_release:
    /* usb_set_intfdata(info->data, NULL); */
    /* usb_driver_release_interface(driver_of(intf), info->data); */
    /* info->data = NULL; */
    free(u.buf);
    return retval;
}

#if 0
static void keepalive_period_task(void *priv)
{
    int retval = 0;
    struct usb_host_device *host_dev = host_id2device(0);

    union {
        void			           *buf;
        struct rndis_msg_hdr	   *header;
        struct rndis_keepalive     *alive;
        struct rndis_keepalive_c   *alive_c;
    } u;

    u.buf = malloc(CONTROL_BUFFER_SIZE);

    for (;;) {
        memset(u.alive, 0, sizeof * u.alive);
        u.alive->msg_type = RNDIS_MSG_KEEPALIVE;
        u.alive->msg_len = cpu_to_le32(sizeof * u.alive);
        retval = rndis_command(host_dev, u.header, CONTROL_BUFFER_SIZE);
        log_info("%s, retval = %d\n", __FUNCTION__, retval);
        os_time_dly(100);
    }
}
#endif

#endif

