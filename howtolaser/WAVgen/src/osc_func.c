#include "tinyosc.h"
#include "wavgen.h"

typedef	struct	s_osc
{
	int			fd;
//	struct	sockaddr_in	sin;
	// buffer ?
}		t_osc;

#define	BCI_CHAN_NB	8


void	osc_close(t_osc *osc)
{
 	// close the UDP socket
 	close(osc->fd);
}
//static volatile bool keepRunning = true;

// handle Ctrl+C
static void sigintHandler(int x)
{
	exit(0);
  //keepRunning = false;
}
//	
void	osc_init(t_osc *o, int port)
{
	int			ret;
	struct	sockaddr_in	sin;

  // register the SIGINT handler (Ctrl+C)
  signal(SIGINT, &sigintHandler);

	// open a socket to listen for datagrams (i.e. UDP packets) on port 9000
	if((o->fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("ERROR on socket creation\n");
		exit(1);
	}
	ret = fcntl(o->fd, F_SETFL, O_NONBLOCK); // set the socket to non-blocking
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = INADDR_ANY;
	if ((ret = bind(o->fd, (struct sockaddr *) &(sin), sizeof(struct sockaddr_in))))
	{
		printf("ERROR the port:%d is invalid!\n", port);
		exit(1);
	}
	printf("tinyosc is now listening on port %d.\n", port);
	printf("Press Ctrl+C to stop.\n");
}

//	On va faire un truc propre a open_bci qui envoie toutjour les messages par 8: (1 par channel)
void	osc_get_message(t_osc *o)
{
 	static	char	buffer[2048]; // declare a 2Kb buffer to read packet data into
	struct	timeval	timeout = {0, 1000}; // select times out after 1 second
	int		i;

	fd_set readSet;
	FD_ZERO(&readSet);
	FD_SET(o->fd, &readSet);
	
	if (select(o->fd+1, &readSet, NULL, NULL, &timeout) > 0)
	{
		struct sockaddr sa; // can be safely cast to sockaddr_in
		socklen_t sa_len = sizeof(struct sockaddr_in);
		int len = 0;
		while ((len = (int) recvfrom(o->fd, buffer, sizeof(buffer), 0, &sa, &sa_len)) > 0)
		{
			if (tosc_isBundle(buffer))
				printf("i dont nanage with bundle\n BYE!\n"), exit(0);
			else
			{
				tosc_message osc;
				tosc_parseMessage(&osc, buffer, len);
				tosc_printMessage(&osc);
			}
		}
	}
	else
	{
		static	int count = 0;
		printf("TIMEOUT:%d\n", count++);
	}
}


void	test_osc()
{
	t_osc	osc;

	osc_init(&osc, 9000);
	while (1)
	{
		osc_get_message(&osc);
	}
	osc_close(&osc);
}
