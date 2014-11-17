#include "headFile.h"
#include "func.c"

int main(int argc, char *argv[])
{
	int sockfd;
	struct hostent *host;
	struct sockaddr_in serv_addr;
	struct timeval tcpStart, tcpEnd;
	float timeuse;

	Dect_input_parm_num(argc);
	host = gethostbyname(argv[1]);
	Dect_hostname(host);

	sockfd= Socket(AF_INET, SOCK_DGRAM, 0);
	init_server_add_at_client(&serv_addr, host);

	Print_Date_Time();
	gettimeofday(&tcpStart, NULL);
	
	Message_Process_Client(stdin, sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	gettimeofday(&tcpEnd, NULL);

	timeuse = TimeUsed(&tcpStart, &tcpEnd);
	printf("Used Time: %f\n", timeuse);
	Print_Date_Time();

	return 0;
}

