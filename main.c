#include "copyrt.h"
#include <stdio.h>
#include "uuid.h"

/* puid -- print a UUID */
void puid(uuid_t u)
{
    int i;

    printf("%8.8lx-%4.4x-%4.4x-%2.2x%2.2x-", u.time_low, u.time_mid,
    u.time_hi_and_version, u.clock_seq_hi_and_reserved,
    u.clock_seq_low);
    for (i = 0; i < 6; i++)
        printf("%2.2x", u.node[i]);
    printf("\n");
}

/* Simple driver for UUID generator */
int 
main(int argc, char **argv)
{
	uuid_t u;
	uuid_create(&u);
	puid(u);

	return 0;
}
