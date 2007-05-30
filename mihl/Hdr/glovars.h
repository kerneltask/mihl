#ifndef GLOVARS_H_
#define GLOVARS_H_


#ifdef __MAIN__
#   define GLOBAL
#   define INIT(X) =X
#else
#   define GLOBAL extern
#   define INIT(X)
#endif

#ifdef __WINDAUBE__

#   define ERRNO WSAGetLastError()

#   define EADDRINUSE  WSAEADDRINUSE 
#   define EWOULDBLOCK WSAEWOULDBLOCK
#   define ECONNRESET  WSAECONNRESET

#   define SHUT_RDWR SD_BOTH
    typedef int socklen_t;

#   define vsnprintf _vsnprintf
#   define open _open

    typedef unsigned int uint32_t;

#   define MSG_NOSIGNAL 0

#else

#   define ERRNO errno
#   define SOCKET_ERROR -1

#   define Sleep(X) sleep(X/1000)

#   define closesocket close

#   define O_BINARY 0

#endif

#define STRNCPY( DST, SRC, LEN ) \
    strncpy( DST, SRC, LEN-1 ); \
    DST[LEN-1] = 0;

typedef struct {
    char *tag;                      // Tag, such as "/" 
    int partial;                    // If 0, do strcmp(), else strncmp(partial)
    mihl_pf_handle_get_t *pf_get;   // If not NULL, function to execute
    mihl_pf_handle_post_t *pf_post; // If not NULL, function to execute
    char *filename;                 // If not NULL, filename to send
    char *content_type;             // Content-type, such as "image/jpeg" or "text/javascript"
    int close_connection;           // Should we close the connection after the operation ?
    void *param;                    // TBD
} mihl_handle_t;

struct mihl_ctx {
    char bind_addr[32];         ///< HTTP bind address
    int port;                   ///< HTTP TCP port (80, 8080, etc.)
    int maxnb_cnx;              ///< Max umer of allowed connections
    unsigned log_level;         ///< MIHL_LOG_ERROR, etc.
    SOCKET sockfd;              ///< TBD
    int read_buffer_maxlen;     ///< TBD
    char *read_buffer;          ///< TBD
    int nb_connexions;          ///< Number of current connexions
    mihl_cnx_t *connexions;     ///< Description of the active connexions
    int nb_handles;             ///< TBD
    mihl_handle_t *handles;     ///< TBD
};

struct mihl_cnx {
    mihl_ctx_t *ctx;                // Mihsl context pointer
    int active;                     // Is this connexion active ?
    SOCKET sockfd;                  // Socked (as returned by accept)
    mihl_cnxinfo_t info;            // Exporteable information
    int keep_alive;                 // 'Keep-Alive:'
    int is_keep_alive;              // 'Connection:'
    char *html_buffer;              // HTML output buffer (mihl_add, mihl_send)
    int html_buffer_len;            // Current length
    int html_buffer_sz;             // Length allocated (8K increment)
};

#define MIN(A,B) (((A)<(B))?(A):(B))

#define FREE( pvar ) \
    if ( pvar ) { \
        free( pvar ); \
        pvar = NULL; \
    }

#endif /*GLOVARS_H_*/
