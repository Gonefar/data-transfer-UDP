void Dect_input_parm_num(int num)
{
	if(num <2)
	{
		fprintf(stderr, "Please enter the server's hostname!");
		exit(1);
	}

}

void Dect_hostname(struct hostent *host)
{	
	if(host == NULL)
	{
		herror("gethostbyname error!");
		exit(1);
	}

}

int Socket(int IP, int SOCK_KIND, int FLAG)
{
	int sockfd;
	
	if((sockfd = socket(IP, SOCK_KIND, FLAG)) == -1)
	{
		perror("socket error!");
		exit(1);
	}
	
	return sockfd;
}

void Connect(int sockfd, struct sockaddr_in serv_addr)
{
	if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("connect error");
		exit(1);
	}

}

void Bind(int sockfd, struct sockaddr_in *my_addr)
{
	if(bind(sockfd,(struct sockaddr *)my_addr, sizeof(struct sockaddr)) < 0)
	{
		perror("bind error!");
		exit(1);
	}

}

void Listen(int sockfd, int listen_num)
{
	if(listen(sockfd, listen_num) < 0)
	{
		perror("listen");
		exit(1);
	}

}

int Accept(int sockfd, struct sockaddr_in *remote_addr)
{
	int sin_size = sizeof(struct sockaddr_in);
	int client_fd;
	if((client_fd =accept(sockfd,(struct sockaddr *)remote_addr, &sin_size))==-1)
	{
		perror("accept error");
		return 0;
	}
	
	return client_fd;
}
void init_server_add_at_client(struct sockaddr_in *serv_addr, struct hostent *host)
{
	bzero(serv_addr, sizeof(struct sockaddr_in));     
	serv_addr->sin_family = AF_INET;
	serv_addr->sin_port = htons(SERVPORT);
	serv_addr->sin_addr = *((struct in_addr *)host->h_addr);

}

void init_server_add_at_server(struct sockaddr_in *my_addr)
{
	bzero(my_addr, sizeof(struct sockaddr_in));
	my_addr->sin_family = AF_INET;
	my_addr->sin_port = htons(SERVPORT);
	my_addr->sin_addr.s_addr = htonl(INADDR_ANY);

}
float TimeUsed(struct timeval *tcpStart, struct timeval *tcpEnd)
{
	float timeuse;
	
	timeuse = 1000000 * (tcpEnd->tv_sec - tcpStart->tv_sec) + tcpEnd->tv_usec - tcpStart->tv_usec;
	timeuse /= 1000000;

	return timeuse;

}

void Print_Date_Time(void)
{
	time_t ticks;
	char timeBuff[100];
	
	ticks = time(NULL);
	snprintf(timeBuff, sizeof(timeBuff), "%.24s\r\n", ctime(&ticks));
	printf("The time %s\n", timeBuff);

}
char *AllocDataAdd(int size)
{
	char *p = NULL;
	p = malloc(size);
		
	if(p == NULL)
		{
			printf("Allocate data address wrong\n");
			return NULL;
		}

	return p;
}


	
void writeValue(char *p, int len)
{
	int i = 0;
	
	for(i = 0; i < len; i++)
		{
			p[i] = 'a';
		}
}

float Calcu_Rate_With_Data(float timeDiff, char *data)
{
	int   datasize = 0;
	float rate = 0;
	
	while(data != NULL)
		{
			datasize++;
			data++;
		}

	rate = datasize * sizeof(char) / timeDiff;

	return rate;
}

void *Malloc(int size)
{
	void *p = NULL;
	p = malloc(size);
		if(p == NULL)
		{
			printf("Allocate data address wrong\n");
			return NULL;
		}

	return p;
}

void PrintSockAdd(struct sockaddr * my_add)
{
	printf("family:%d\n", my_add->sa_family);
	//printf("port:%d\n", my_add->sin_port);
	printf("addr:%s\n", my_add->sa_data);

}

char *Convert_Int_To_Char(int num)
{
	char *p = malloc(sizeof(char) * 32);
	char temp;
	int choice = 0;
	int count = 0, i;
	
	bzero(p, sizeof(char) * 16);
	if(p == NULL)
		{
			printf("creat pointer err\n");
			return NULL;
		}

	do
		{
			choice = num % 10;
			switch(choice)
				{
					case 0:
						strcat(p, "0");
						count++;
						break;
					case 1:
						strcat(p, "1");
						count++;
						break;
					case 2:
						strcat(p, "2");
						count++;
						break;
					case 3:
						strcat(p, "3");
						count++;
						break;
					case 4:
						strcat(p, "4");
						count++;
						break;
					case 5:
						strcat(p, "5");
						count++;
						break;
					case 6:
						strcat(p, "6");
						count++;
						break;
					case 7:
						strcat(p, "7");
						count++;
						break;
					case 8:
						strcat(p, "8");
						count++;
						break;
					case 9:
						strcat(p, "9");
						count++;
						break;
					default:
						break;

				}
		}while((num = num / 10) > 0);

	for(i = 0; i < count/2; i++)
		{
			temp = p[i];
			p[i] = p[count - 1 - i];
			p[count - 1 - i] = temp;
		}
			
	p[count] = '\0';
	return p;
	
}

void Message_Process_Server( int sockfd, struct sockaddr *serv_addr, int socklen)
{
	int recvlen = 0;
	int count = 0;
	char buff[DATA_SIZE];
	char *p = NULL;

	p = buff;

	while(1)
		{
			recvlen = recvfrom(sockfd, p, DATA_SIZE, 0, serv_addr, &socklen);
			//printf("recv length:%d\n", recvlen);

			p[recvlen] = '\0';
			//printf("buff:%s\n", p);
			if(recvlen > 0)
				{
					count++;
				}
			
			//printf("Receive %d packets\n", count);
			sendto(sockfd, p, recvlen, 0, serv_addr, socklen);
			p = buff;
			bzero(buff, sizeof(buff));
		}

}

float Time_Diff_ms(struct timeval *tcpStart, struct timeval *tcpEnd)
{
	float diff = 0;
	diff = (tcpEnd->tv_sec - tcpStart->tv_sec)*1000000 + (tcpEnd->tv_usec - tcpStart->tv_usec);
	return diff/1000;
}


int Message_Process_Client(FILE *fp, int sockfd, struct sockaddr *serv_addr, int socklen)
{
	int recvlen, len, i;
	int count = 0, total_recv_bytes = 0, print_count = 1;
	float time_diff, time_diff_sum = 0, calcu_time_ms = 10;
	int recvbytes = 0;
	char senddata[PACK_SIZE], recvdata[PACK_SIZE+1];
	char *temp = NULL;
	struct sockaddr *preply_addr;
	struct timeval tcpinit, tcpEnd;
	
	preply_addr = (struct sockaddr *)AllocDataAdd(socklen);
	gettimeofday(&tcpinit, NULL);
	for(i = 0; i < PACK_NUM; i++)
	{
		len = socklen;
		temp = Convert_Int_To_Char(i);
		//strcpy(senddata, "hello, my friend, You are connected!");
		memset(senddata, 'a', 1000);
		strcat(senddata, temp);
		free(temp);
		sendto(sockfd, senddata, strlen(senddata), 0, serv_addr, socklen);
		bzero(senddata, sizeof(senddata));
		recvlen = recvfrom(sockfd, recvdata, DATA_SIZE, 0 , preply_addr, &len);
		recvbytes += recvlen;
		total_recv_bytes += recvlen;

		//printf("recvdata:%s\n", recvdata);
		if(recvlen > 0)
			{
				count++;
			}

		gettimeofday(&tcpEnd, NULL);
		//printf("time diff:%f\n", Time_Diff_ms(&tcpinit, &tcpEnd));

		if((time_diff = Time_Diff_ms(&tcpinit, &tcpEnd)) >= calcu_time_ms * print_count)
			{
				time_diff -= time_diff_sum;				
				time_diff_sum += time_diff;
				//printf("recvbytes:%d\n", recvbytes);
				//printf("timedff:%f\n", time_diff);
				printf("In the %d period, the rate: %f KBps in the latest 10 ms\n", print_count, recvbytes/time_diff);
				print_count++;
				recvbytes = 0;

			}
		
		//printf("Receive back:%d packets\n", count);
		if((len != socklen) || (memcmp(serv_addr, (struct sockaddr *)preply_addr, socklen) != 0))
			{
				printf("reply from ignored\n");
				continue;

			}

		recvdata[recvlen] = '\0';
		//printf("Back:%s\n", recvdata);

	}

	time_diff = Time_Diff_ms(&tcpinit, &tcpEnd);
	printf("time diff %f, total bytes %d\n", time_diff, total_recv_bytes);
	printf("Average rate is %f KBps\n", total_recv_bytes / time_diff);
	return total_recv_bytes;

}


void sendFile(int sockfd, FILE *fp, char *buffer)
{
	bzero(buffer, BUFFER_SIZE);
	int file_block_length = 0;

	while( (file_block_length = fread(buffer,sizeof(char),BUFFER_SIZE,fp))>0)
			{
				printf("file_block_length = %d\n",file_block_length);                
				if(send(sockfd, buffer, file_block_length, 0)<0)
				{
					printf("Send File:\t%s Failed\n", fp);
					break;
				}
				bzero(buffer, BUFFER_SIZE);
			}
			fclose(fp);
			printf("File:\t%s Transfer Finished\n", fp);
			close(sockfd);
}



