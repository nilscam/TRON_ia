
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int	main()
{
	char	ac[256];
	struct hostent *phe;
	struct in_addr locaddr;
	char	mydata[1024];
	
	gethostname(ac, sizeof(ac));
	phe = gethostbyname(ac);
	memcpy(&locaddr, phe->h_addr_list[0], sizeof(struct in_addr));

	strcpy(mydata, inet_ntoa(locaddr));

	printf("ip = [%s]\n", mydata);
	return 0;
}
