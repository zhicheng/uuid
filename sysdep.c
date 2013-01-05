#include "sysdep.h"

#include "copyrt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <net/if_types.h>
#include <openssl/md5.h>

typedef unsigned long long unsigned64;

/* system dependent call to get IEEE node ID.
   This sample implementation generates a random node ID. */
void 
get_ieee_node_identifier(uuid_node_t *node)
{
	int mib[6];
	size_t len;
	char *buf;
	unsigned char *ptr;
	struct if_msghdr *ifm;
	struct sockaddr_dl *sdl;

	mib[0] = CTL_NET;
	mib[1] = AF_ROUTE;
	mib[2] = 0;
	mib[3] = AF_LINK;
	mib[4] = NET_RT_IFLIST;

	/* XXX "en0" should only work Darwin base System */
	/* You should change if this is not work on your platform (Other BSD) */
	if ((mib[5] = if_nametoindex("en0")) == 0) {	
		printf("Error: if_nametoindex error\n");
		return;
	}
	if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0) {
		printf("Error: sysctl, take 1\n");
		return;
	}
	if ((buf = malloc(len)) == NULL) {
		printf("Could not allocate memory. error!\n");
		return;
	}
	if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
		printf("Error: sysctl, take 2");
		free(buf);
		return;
	}
	ifm = (struct if_msghdr *)buf;
	sdl = (struct sockaddr_dl *)(ifm + 1);
	ptr = (unsigned char *)LLADDR(sdl);

	memcpy(node, LLADDR(sdl), 6);
	free(buf);
}

/* system dependent call to get the current system time. Returned as
   100ns ticks since UUID epoch, but resolution may be less than
   100ns. */
/* remove Windows support */
void 
get_system_time(uuid_time_t *uuid_time)
{
	struct timeval tp;

	gettimeofday(&tp, (struct timezone *)0);

	/*
	 * Offset between UUID formatted times and Unix formatted times.
	 * UUID UTC base time is October 15, 1582. Unix base time is January
	 * 1, 1970.
	 */
	*uuid_time = ((unsigned64) tp.tv_sec * 10000000)
	    + ((unsigned64) tp.tv_usec * 10)
	    + I64(0x01B21DD213814000);
}

