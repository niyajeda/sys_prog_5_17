#ifndef __SOCK__
#define __SOCK__

int prepare_socket(int portnum);
void close_socket(void);
int manage_connections(int anzverbindungen, int (*managerfunction) (FILE * datastream, char *information));

#endif /*__SOCK__ */