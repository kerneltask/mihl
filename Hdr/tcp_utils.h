#ifndef TCP_UTILS_H_
#define TCP_UTILS_H_

#ifdef __WINDAUBE__
#   ifdef BUILD_DLL_TCPUTILS
#       define PUBLIC __declspec(dllexport)
#   else
#       define PUBLIC __declspec(dllimport)
#   endif
#else
#   define PUBLIC
#endif

int tcp_read( SOCKET sockfd, char *buffer, int maxlen );

int tcp_write( SOCKET sockfd, const char *buff, int buff_len );

void decode_keys_values( mihl_cnx_t *cnx, char *_request, 
    int *nb_options, char *options_names[], char *options_values[], int maxnb_options,
    int *nb_variables, char *vars_names[], char *vars_values[], int maxnb_values );

int read_file( char *fname, char **file, int *length );

#undef PUBLIC

#endif /*TCP_UTILS_H_*/