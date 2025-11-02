/* ngIRCd ELKS stub signal header for Watcom */
#ifndef NGIRCD_INCLUDE_LINUXMT_SIGNAL_H
#define NGIRCD_INCLUDE_LINUXMT_SIGNAL_H

#define SIGHUP   1
#define SIGINT   2
#define SIGQUIT  3
#define SIGILL   4
#define SIGTRAP  5
#define SIGABRT  6
#define SIGBUS   7
#define SIGFPE   8
#define SIGKILL  9
#define SIGUSR1 10
#define SIGSEGV 11
#define SIGUSR2 12
#define SIGPIPE 13
#define SIGALRM 14
#define SIGTERM 15
#define SIGCHLD 17

typedef void (*sighandler_t)(int);

#endif

/* -eof- */
