#include "unp.h"

int main (int argc, char **argv) {

	char *ptr;
	char **pptr;
	char str[INET_ADDRSTRLEN];
	struct hostent *hptr;

	while (--argc > 0) {
		ptr = *++argv;
		if ( (hptr = gethostbyname(ptr)) == NULL) {
			err_msg("gethostbyname error for host: %s: %s",
				ptr, hstrerror(h_errno));
			 continue;
		}

		printf("official hostname: %s\n", hptr->h_name);

		for (pptr = hptr->h_aliases; *pptr != NULL; pptr++) {
			printf("\talias %s\n", *pptr);
		}

		pptr = hptr->h_addr_list;

		for (; *pptr != NULL; pptr++) {
			printf("\taddress: %s\n",
				Inet_ntop(hptr->h_addrtype, *pptr, str,
					  sizeof(str)));
		}
	}
	exit(0);

}
