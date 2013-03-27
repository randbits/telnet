/*
 *	./a.out <node> [<service>]
 *
 *	NOTE: inet_pton and inet_ntop
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>		//include def for struct addrinfo

static void print_addrinfo (struct addrinfo* _info);

char buffer[INET6_ADDRSTRLEN];

int
main (int argc, char** argv)
{
    if ((argc != 2)&&(argc != 3))
    {
	fprintf (stderr, "Usage: ./a.out <node> [<service>]\n");
	exit (EXIT_SUCCESS);
    }
    int status;
    struct addrinfo hints;
    struct addrinfo* res;
    memset (&hints, 0, sizeof (hints));
    hints.ai_family = AF_UNSPEC;  //don't care IPv4 or IPv6.
    hints.ai_socktype = SOCK_STREAM; //tcp stream

    if ((status = getaddrinfo (argv[1], argv[2], &hints, &res)) != 0)
    {
	perror ("getaddrinfo error: ");
	exit (EXIT_FAILURE);
    }
    //go through the list.
    struct addrinfo* rp;
    int count = 1;
    for(rp = res; rp != NULL; rp = rp->ai_next) 
    {
	printf ("%d\n", count);
	print_addrinfo (rp);
	count++;
    }

    freeaddrinfo (res);
}

static void
print_addrinfo (struct addrinfo* _info)
{
    memset (&buffer, 0, sizeof (buffer));

    void* addr;
    int port;
    //ai_flags;
    //2. family
    if (_info->ai_family == AF_INET)
    {
	addr = &(((struct sockaddr_in *)(_info->ai_addr))->sin_addr);
	port = ntohs(((struct sockaddr_in *)(_info->ai_addr))->sin_port);
	printf ("ai_family: AF_INET\n");
    }
    else if (_info->ai_family == AF_INET6)
    {
	addr = &(((struct sockaddr_in6 *)(_info->ai_addr))->sin6_addr);
	port = ntohs(((struct sockaddr_in6 *)(_info->ai_addr))->sin6_port);
	printf ("ai_family: AF_INET6\n");
    }
    else
	printf ("ai_family: %d\n", _info->ai_family);
    //3. socket type
    if (_info->ai_socktype == SOCK_STREAM)
	printf ("ai_socktype: SOCK_STREAM\n");
    else if (_info->ai_socktype == SOCK_DGRAM)
	printf ("ai_socktype: SOCK_DGRAM\n");
    else
	printf ("ai_socktype: %d\n", _info->ai_socktype);
    //3. protocol
    printf ("ai_protocol: %d\n", _info->ai_protocol);
    //4. addr 
    inet_ntop(_info->ai_family, addr, buffer, sizeof(buffer));
    printf ("ai_addr: %s (port: %d)\n", buffer, port);
    //5. canonname
    printf ("ai_canonname; %s\n", _info->ai_canonname);
}
