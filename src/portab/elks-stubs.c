/*
 * ngIRCd -- The Next Generation IRC Daemon
 *
 * ELKS compatibility shims for networking helpers that are unavailable in
 * the 16-bit libc.
 */

#ifdef NGIRCD_ELKS

#include <stddef.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

#ifdef __WATCOMC__
#include "watcom/syselks.h"
#endif

struct addrinfo;
struct sockaddr;

#ifndef socklen_t
typedef unsigned int socklen_t;
#endif

#ifndef EAI_FAIL
#define EAI_FAIL (-1)
#endif

extern ipaddr_t in_aton(const char *);
extern char *in_ntoa(ipaddr_t);

int
getaddrinfo(const char *node, const char *service,
	    const struct addrinfo *hints, struct addrinfo **res)
{
	(void)node;
	(void)service;
	(void)hints;
	(void)res;
	return EAI_FAIL;
}

void
freeaddrinfo(struct addrinfo *res)
{
	(void)res;
}

int
getnameinfo(const struct sockaddr *sa, socklen_t salen,
	    char *host, socklen_t hostlen,
	    char *serv, socklen_t servlen, int flags)
{
	(void)sa;
	(void)salen;
	(void)host;
	(void)hostlen;
	(void)serv;
	(void)servlen;
	(void)flags;
	return EAI_FAIL;
}

const char *
gai_strerror(int errcode)
{
	(void)errcode;
	return "ELKS resolver unavailable";
}

int
inet_aton(const char *cp, struct in_addr *addr)
{
	ipaddr_t ip = in_aton(cp);

	if (ip == (ipaddr_t)-1)
		return 0;
	addr->s_addr = ip;
	return 1;
}

unsigned long
inet_addr(const char *cp)
{
	ipaddr_t ip = in_aton(cp);

	if (ip == (ipaddr_t)-1)
		return (unsigned long)-1;
	return (unsigned long)ip;
}

char *
inet_ntoa(struct in_addr in)
{
	return in_ntoa(in.s_addr);
}

int
gethostname(char *name, int len)
{
	if (!name || len <= 0) {
		errno = EINVAL;
		return -1;
	}
	strncpy(name, "ngircd", (size_t)len);
	if (len > 0)
		name[len - 1] = '\0';
	return 0;
}

int
getsockopt(int sock, int level, int optname, void *optval, socklen_t *optlen)
{
	(void)sock;
	(void)level;
	(void)optname;
	if (optval && optlen && *optlen >= sizeof(int))
		memset(optval, 0, (size_t)*optlen);
	return 0;
}

int
getsockname(int sock, struct sockaddr *addr, socklen_t *addrlen)
{
	(void)sock;
	(void)addr;
	(void)addrlen;
	errno = ENOSYS;
	return -1;
}

int
chroot(const char *path)
{
	(void)path;
	errno = ENOSYS;
	return -1;
}

int
setpgrp(int pid, int pgid)
{
	(void)pid;
	(void)pgid;
	errno = ENOSYS;
	return -1;
}

int
pipe(int fds[2])
{
#ifdef __WATCOMC__
	syscall_res res;
	sys_setseg(fds);
	res = sys_call1(SYS_pipe, (unsigned)fds);
	__syscall_return(int, res);
#else
	(void)fds;
	errno = ENOSYS;
	return -1;
#endif
}

int
setgroups(int size, const void *list)
{
	(void)size;
	(void)list;
	errno = EPERM;
	return -1;
}

#endif /* NGIRCD_ELKS */

/* -eof- */
