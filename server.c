#include "headFile.h"
#include "func.c"

int main()
{
	int sockfd,client_fd;
	struct sockaddr_in my_addr;

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
	init_server_add_at_server(&my_addr);
	Bind(sockfd, &my_addr);
	
	printf("Listening:\n");
	while(1)
	{
		Message_Process_Server(sockfd,(struct sockaddr *)&my_addr, sizeof(my_addr));
		
	}
	
	return 0;
}
