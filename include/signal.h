/* ngIRCd ELKS stub signal header */
#ifndef NGIRCD_SIGNAL_H
#define NGIRCD_SIGNAL_H

#include <stddef.h>

typedef void (*sighandler_t)(int);

#define SIGHUP   1
#define SIGINT   2
#define SIGQUIT  3
#define SIGILL   4
#define SIGABRT  6
#define SIGKILL  9
#define SIGUSR1 10
#define SIGSEGV 11
#define SIGUSR2 12
#define SIGPIPE 13
#define SIGALRM 14
#define SIGTERM 15
#define SIGCHLD 17

static inline sighandler_t signal(int sig, sighandler_t handler)
{
	(void)sig;
	(void)handler;
	return (sighandler_t)0;
}

static inline int raise(int sig)
{
	(void)sig;
	return 0;
}

#define SIG_IGN ((sighandler_t)1)
#define SIG_DFL ((sighandler_t)0)

static inline int sigblock(int mask)
{
	(void)mask;
	return 0;
}

static inline int sigsetmask(int mask)
{
	(void)mask;
	return 0;
}

#endif

/* -eof- */
