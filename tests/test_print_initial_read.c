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

#define BUF_SIZE 1024
//here we should use unsigned as signed char can cause problems
unsigned char buffer[BUF_SIZE] = {0};

static void pretty_print (const unsigned char* _buffer, int _size);

int
main (int argc, char** argv)
{
    if (argc != 3)
    {
	fprintf (stderr, "Usage: ./a.out <node> [<service>]\n");
	exit (EXIT_SUCCESS);
    }
    //1. name resolution: 
    struct addrinfo hints;
    struct addrinfo* res;
    memset (&hints, 0, sizeof (hints));
    hints.ai_family = AF_INET; // only support IPv4
    hints.ai_socktype = SOCK_STREAM; //tcp stream

    int status;
    if ((status = getaddrinfo (argv[1], argv[2], &hints, &res)) != 0)
    {
	perror ("getaddrinfo error: ");
	exit (EXIT_FAILURE);
    }
    //1.1 go through the lists.
    int client_sfd;
    int conn_retval;
    struct addrinfo* rp;
    for(rp = res; rp != NULL; rp = rp->ai_next) 
    {

    //2. create a socket and connect to remote address.
	client_sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
	if (client_sfd == -1)
	{
	    close (client_sfd);
	    perror ("socket errror: ");
	    continue;
	}
	conn_retval = connect (client_sfd, rp->ai_addr, rp->ai_addrlen);
	if (conn_retval == -1)
	{
	    close (client_sfd);
	    perror ("connect errror: ");
	    continue;
	}
	break;
    }
    if ((client_sfd == -1)||(conn_retval == -1))
    {
	fprintf (stderr, "socket and connect all failed\n");
	exit (EXIT_FAILURE);
    }
    freeaddrinfo (res);
    //3. event loop
    int read_size = 0;
    for (;;)
    {
	//3. read data
	while ((read_size = read (client_sfd, buffer, sizeof(buffer)))!=-1)
	{
	    pretty_print (buffer, read_size);
	    if (read_size < sizeof(buffer))
		break;
	}

	printf ("\n");

	//4. write data
	//write
    }
    //5. close connection
    close (client_sfd);
}


static void
pretty_print (const unsigned char* _buffer, int _size)
{
    if (_size == 0)
	return;
#define N_COLS 16
    static int line_num= 0;
    if (line_num == 0)
    {
	printf ("\n");
	printf ("COL\\ROW\t 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
	printf ("\n");
    }
    printf("read_size = 0x%03x\n", _size);

    int row = _size/16 + 1 ;  //row numbers.
    int i;
    int j;
    for (i = 0; i < row; i++)
    {
	printf ("%02x\t", i+line_num);
	//print numbers
	for (j = 0; j < N_COLS; j++)
	{
	    printf(" %02x", _buffer[i*N_COLS+j]);
	}
	printf ("\n  \t");
	//print ascii
	for (j = 0; j < N_COLS; j++)
	{
	    if (isprint (_buffer[i*N_COLS+j]))
		printf("  %c", _buffer[i*N_COLS+j]);
	    else
		printf(" ..");
	}
	printf ("\n");
    }
    line_num += row;
}
