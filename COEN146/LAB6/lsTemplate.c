// COEN 146L - Lab: Link State routing

/*
 * Name: Logan Calder
 * Date: 02/25/2025
 * Title: Lab6 - Link State Routing
 * Description: This program implements a link state routing algorithm using Dijkstra's algorithm
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>

// defines
#define N 4
#define INFINITE 1000
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

// types
typedef struct routers
{
	char name[50];
	char ip[50];
	int port;

} ROUTERS;

// global variables
ROUTERS routers[N];
int costs[N][N];
int distances[N];
int myid, nodes;
int sock;
struct sockaddr_in addr;
struct sockaddr_in otheraddr;
socklen_t addr_size;
pthread_mutex_t lock;

// print costs
void print_costs(void)
{
	pthread_mutex_lock(&lock);
	printf("matrix:\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d ", costs[i][j]);
		}
		printf("\n");
	}
	pthread_mutex_unlock(&lock);
}

// receive info
void *receive_info(void *arg)
{
	int packet[3];
	while (1)
	{
		recvfrom(sock, packet, sizeof(packet), 0, NULL, NULL);
		int src = ntohl(packet[0]);
		int dest = ntohl(packet[1]);
		int new_cost = ntohl(packet[2]);

		pthread_mutex_lock(&lock);
		costs[src][dest] = new_cost;
		costs[dest][src] = new_cost;
		pthread_mutex_unlock(&lock);

		print_costs();
	}
}

// run_link_state
void *run_link_state(void *arg)
{
	int taken[N];
	int min, spot;
	while (1)
	{
		sleep(rand() % 10 + 10);
		for (int i = 0; i < N; i++)
		{
			taken[i] = 0;
			pthread_mutex_lock(&lock);
			distances[i] = costs[myid][i];
			pthread_mutex_unlock(&lock);
		}
		taken[myid] = 1;
		for (int i = 1; i < N; i++)
		{
			min = INFINITE;
			for (int j = 0; j < N; j++)
			{
				if (!taken[j] && distances[j] < min)
				{
					min = distances[j];
					spot = j;
				}
			}
			taken[spot] = 1;
			for (int j = 0; j < N; j++)
			{
				if (!taken[j])
				{
					pthread_mutex_lock(&lock);
					distances[j] = MIN(distances[j], distances[spot] + costs[spot][j]);
					pthread_mutex_unlock(&lock);
				}
			}
		}
		printf("new distances:\n");
		for (int i = 0; i < N; i++)
		{
			printf("%d ", distances[i]);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	FILE *fp;
	int i, j, id, cost, packet[3];
	pthread_t thr1, thr2;

	if (argc != 5)
	{
		printf("Usage: %s <id> <nodes> <routers> <cost table>\n", argv[0]);
		exit(0);
	}

	myid = atoi(argv[1]);
	nodes = atoi(argv[2]);
	if (myid >= N)
	{
		printf("wrong id\n");
		return 1;
	}

	if (nodes != N)
	{
		printf("wrong number of nodes\n");
		return 1;
	}

	if ((fp = fopen(argv[3], "r")) == NULL)
	{
		printf("can't open %s\n", argv[3]);
		return 1;
	}
	for (i = 0; i < nodes; i++)
		fscanf(fp, "%s%s%d", routers[i].name, routers[i].ip, &routers[i].port);
	fclose(fp);

	if ((fp = fopen(argv[4], "r")) == NULL)
	{
		printf("can't open %s\n", argv[4]);
		return 1;
	}
	for (i = 0; i < nodes; i++)
		for (j = 0; j < nodes; j++)
			fscanf(fp, "%d", &costs[i][j]);
	fclose(fp);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(routers[myid].port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));
	addr_size = sizeof(addr);

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("socket error\n");
		return 1;
	}
	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) != 0)
	{
		printf("bind error\n");
		return 1;
	}

	pthread_mutex_init(&lock, NULL);
	pthread_create(&thr1, NULL, receive_info, NULL);
	pthread_create(&thr2, NULL, run_link_state, NULL);

	for (i = 0; i < 3; i++)
	{
		printf("any changes? ");
		scanf("%d%d", &id, &cost);
		if (id >= N || id == myid)
		{
			printf("wrong id\n");
			break;
		}
		pthread_mutex_lock(&lock);
		costs[myid][id] = cost;
		costs[id][myid] = cost;
		pthread_mutex_unlock(&lock);
		print_costs();
		packet[0] = htonl(myid);
		packet[1] = htonl(id);
		packet[2] = htonl(cost);
		for (j = 0; j < N; j++)
		{
			if (j != myid)
			{
				otheraddr.sin_port = htons(routers[j].port);
				inet_pton(AF_INET, routers[j].ip, &otheraddr.sin_addr.s_addr);
				sendto(sock, packet, sizeof(packet), 0, (struct sockaddr *)&otheraddr, addr_size);
			}
		}
		printf("sent\n");
	}
	sleep(20);
	return 0;
}
