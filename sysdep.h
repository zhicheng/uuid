#ifndef __SYSDEP_H__
#define __SYSDEP_H__

#include "copyrt.h"

#include <sys/types.h>
#include <sys/time.h>
#include <sys/sysctl.h>

/* change to point to where MD5 .h's live; RFC 1321 has sample
   implementation */
#include <openssl/md5.h>
#include <openssl/sha.h>

/* set the following to the number of 100ns ticks of the actual
   resolution of your system's clock */
#define UUIDS_PER_TICK 1024

/* Set the following to a calls to get and release a global lock */
#define LOCK
#define UNLOCK

typedef unsigned long unsigned32;
typedef unsigned short unsigned16;
typedef unsigned char unsigned8;
typedef unsigned char byte;

/* Set this to what your compiler uses for 64-bit data type */
#define unsigned64_t unsigned long long
#define I64(C) C##LL

typedef unsigned64_t uuid_time_t;
typedef struct {
	char	nodeID[6];
} uuid_node_t;

void get_ieee_node_identifier(uuid_node_t *node);
void get_system_time(uuid_time_t *uuid_time);
void get_random_info(char seed[16]);

#endif /* __SYSDEP_H__ */

