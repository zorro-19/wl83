/**
 *
 * @file tftp_client.h
 * TFTP client header
 *
 */

/*
 * Redistribution and use in source and binary forms, with or without
 * modification,are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 */

#ifndef LWIP_HDR_APPS_TFTP_CLIENT_H
#define LWIP_HDR_APPS_TFTP_CLIENT_H

#include "lwip/apps/tftp_common.h"

enum tftp_transfer_mode {
    TFTP_MODE_OCTET,
    TFTP_MODE_NETASCII,
    TFTP_MODE_BINARY /* used in old versions only */
};

err_t tftp_init_client(const struct tftp_context *ctx);
err_t tftp_get(void *handle, const ip_addr_t *addr, u16_t port, const char *fname, enum tftp_transfer_mode mode);
err_t tftp_put(void *handle, const ip_addr_t *addr, u16_t port, const char *fname, enum tftp_transfer_mode mode);

#endif /* LWIP_HDR_APPS_TFTP_CLIENT_H */
