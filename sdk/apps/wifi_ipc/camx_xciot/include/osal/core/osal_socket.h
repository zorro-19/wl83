/*****************************************************************************
 * osal_socket.h
 *
 *
 *
 ****************************************************************************/
/*
 * wiki
 * ====
 */
#ifndef OSAL_SOCKET_H_INCLUDE
#define OSAL_SOCKET_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_socket
 * @{
 */
/*****************************************************************************
 * Included Files
 ****************************************************************************/

#if !defined(OSAL_API_H_INCLUDE)
#error "Only 'osal/osal_api.h' can be included directly."
#endif

/*****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* socket udp api */
#define OSAL_SOCKET_UDP

/* socket tcp api */
#define OSAL_SOCKET_TCP

/* unix_path_max 108 */
#define OSAL_MAXADDRLEN 96

/*****************************************************************************
 * Public Types
 ****************************************************************************/

/*
 * Some address details. This is in some ways like a traditional sockets
 * sockaddr, but we have our own to cope with our unique families, etc.
 * The details of this structure are directly exposed to applications.
 * These structures can be obtained via property lookups, etc.
 */
typedef enum {
    E_OSAL_AF_UNSPEC = 0,
    E_OSAL_AF_UNIX   = 2,
    E_OSAL_AF_INET   = 3,
    E_OSAL_AF_INET6  = 4,
} osal_sockaddr_family_t;

typedef struct {
    osal_sockaddr_family_t family;
    char                   addr[OSAL_MAXADDRLEN];
    uint16_t               port;
} osal_ipaddr_t;

typedef struct {
    /* socketfd */
    int socketfd;
} osal_socket_t;

typedef struct {
    /* socketfd */
    int socketfd;
} osal_server_handle_t;
/*****************************************************************************
 * Public Data
 ****************************************************************************/

/*****************************************************************************
 * Inline Functions
 ****************************************************************************/

/****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/**
 * @brief Initialize ipaddr struct.
 *
 * @param[out]  ipaddr - The pointer of ipaddr data.
 *
 * @param[in]   family - socket family.
 *
 * @param[in]   addr   - ip addr string. like "0.0.0.0" or "192.168.1.1"
 *
 * @param[in]   port   - port.
 */
void osal_ipaddr_init(osal_ipaddr_t         *ipaddr,
                      osal_sockaddr_family_t family,
                      const char            *addr,
                      uint16_t               port);

/**
 * @brief Check two ipaddr to be equal.
 *
 * @param[in]   ipaddr1 - ipaddr1.
 *
 * @param[in]   ipaddr2 - ipaddr2.
 */
bool osal_ipaddr_is_equal(osal_ipaddr_t *ipaddr1, osal_ipaddr_t *ipaddr2);

/**
 * @brief ipv4 addr init.
 */
#define OSAL_IPADDR_INIT_IPV4(ipaddrp, addr, port)                           \
    osal_ipaddr_init(ipaddrp, E_OSAL_AF_INET, addr, port)

/**
 * @brief ipv6 addr init.
 */
#define OSAL_IPADDR_INIT_IPV6(ipaddrp, addr, port)                           \
    osal_ipaddr_init(ipaddrp, E_OSAL_AF_INET6, addr, port)

/**
 * @brief unix addr init.
 */
#define OSAL_IPADDR_INIT_UNIX(ipaddrp, addr, port)                           \
    osal_ipaddr_init(ipaddrp, E_OSAL_AF_UNIX, addr, port)

/**
 * @brief Get ip by domain.
 *
 * @param[in]  domain - domain.
 *
 * @param[out] ipaddr - ipaddr.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_gethostbyname(char *domain, char *ipaddr);

/**
 * @brief Get local ip.
 *
 * @param[out]  local - The pointer of result. !!note!! use addr only.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_local_ipaddr(osal_ipaddr_t *local);

/**
 * @brief Get socket name.
 *
 * @param[in]  socket - The socket object.
 *
 * @param[out]  ia - The pointer of result.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_socket_getsockname(osal_socket_t *socket, osal_ipaddr_t *ia);

/**
 * @brief Get peer name.
 *
 * @param[in]  socket - The socket object.
 *
 * @param[out]  ia - The pointer of result.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_socket_getpeername(osal_socket_t *socket, osal_ipaddr_t *ia);

/**
 * @brief Close socket.
 *
 * @param[in]  socket - The socket object.
 */
void osal_socket_close(osal_socket_t *socket);

/**
 * @brief socket accept .
 *
 * @param[in]  socket     - The socket object.
 *
 * @param[out]  peer_addr - The pointer of result.
 *
 * @param[out]  conn      - The pointer of result.
 */
int osal_socket_accept(osal_socket_t *server,
                       osal_ipaddr_t *peer_addr,
                       osal_socket_t *conn);
#ifdef OSAL_SOCKET_UDP
/**
 * @brief Create and initialize a udp object, bind this local ia addr.
 *
 * @param[out] udp       - The pointer of result.
 *
 * @param[in]  addrbind  - The udp bind address.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_udp_open(osal_socket_t *udp, osal_ipaddr_t *addrbind);

/**
 * @brief Create and initialize a udp muiltcast object, bind this local ia addr.
 *
 * @param[out] udp       - The pointer of result.
 *
 * @param[in]  addrbind  - The udp bind address.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_mcudp_open(osal_socket_t *udp, osal_ipaddr_t *addrbind);

/**
 * @brief Connect to remote udp server.
 *
 * @param[in]  udp      - The udp obj obtained by @ref osal_udp_open.
 *
 * @param[in]  addrserv - The udp server address.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_udp_connect(osal_socket_t *udp, osal_ipaddr_t *addrserv);

/**
 * @brief Send date to remote.
 *
 * @param[in]  udp    - The udp obj obtained by @ref osal_udp_open.
 *
 * @param[in]  addrto - The sendto address.
 *
 * @param[in]  buffer - The pointer of buffer.
 *
 * @param[in]  len    - The length of buffer.
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_udp_sendto(osal_socket_t *udp,
                    osal_ipaddr_t *addrto,
                    const uint8_t *buffer,
                    size_t         len);

/**
 * @brief Recv date from remote.
 *
 * @param[in]  udp      - The udp obj obtained by @ref osal_udp_open.
 *
 * @param[in]  addrfrom - The recvfrom address.
 *
 * @param[in]  buffer   - The pointer of buffer.
 *
 * @param[in]  len      - The length of buffer.
 *
 * @param[in]  recvlen  - The recvlength of data.
 *
 * @param[in]  timeout  - Maximum number of milliseconds to wait for data
 *                        0 means no timeout (wait forever)
 *
 * @return status code that indicates the execution status of the function.
 */
int osal_udp_recvfrom(osal_socket_t *udp,
                      osal_ipaddr_t *addrfrom,
                      uint8_t       *buffer,
                      size_t         len,
                      size_t        *recvlen,
                      uint32_t       timeout_msecs);
#endif

#ifdef OSAL_SOCKET_TCP
int osal_tcp_connect(osal_socket_t *tcp,
                     osal_ipaddr_t *addrserv,
                     uint32_t       timeout_msecs);
int osal_tcp_server(osal_socket_t *tcp, uint16_t port);
int osal_tcp_send(osal_socket_t *tcp, const uint8_t *buffer, size_t len);

int osal_tcp_recv(osal_socket_t *tcp,
                  uint8_t       *buffer,
                  size_t         len,
                  size_t        *recvlen,
                  uint32_t       timeout_msecs);
#endif

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
/*****************************************************************************
 * @} (end addtogroup osal_socket)
 */
/****************************************************************************/
#endif /* OSAL_SOCKET_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/
