#include "tinyosc.h"
#include "wavgen.h"


volatile bool keepRunning = true;
void	osc_close(t_env *e)
{
 	// close the UDP socket
 	close(e->osc_fd);
}

// handle Ctrl+C
static void sigintHandler(int x)
{
	exit(0);
	// maybe call some other close function to quit properly the sdl and evrything else
	// or something eauivalent with the keelRunning variable
  //keepRunning = false;
}
//	
void	osc_init(t_env *e, int port)
{
	int			ret;
	struct	sockaddr_in	sin;

  // register the SIGINT handler (Ctrl+C)
  signal(SIGINT, &sigintHandler);

	// open a socket to listen for datagrams (i.e. UDP packets) on port 9000
	if((e->osc_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("ERROR on socket creation\n");
		exit(1);
	}
	ret = fcntl(e->osc_fd, F_SETFL, O_NONBLOCK); // set the socket to non-blocking
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = INADDR_ANY;
	if ((ret = bind(e->osc_fd, (struct sockaddr *) &(sin), sizeof(struct sockaddr_in))))
	{
		printf("ERROR the port:%d is invalid!\n", port);
		exit(1);
	}
	printf("tinyosc is now listening on port %d.\n", port);
	printf("Press Ctrl+C to stop.\n");
}

void	osc_get_message(t_env *e, void (*f)(tosc_message *, void *))
{
 	static	char	buffer[2048]; // declare a 2Kb buffer to read packet data into
	struct	timeval	timeout = {0, 1000}; // select times out after 1 second
	int		i;

	fd_set readSet;
	FD_ZERO(&readSet);
	FD_SET(e->osc_fd, &readSet);
	
	if (select(e->osc_fd+1, &readSet, NULL, NULL, &timeout) > 0)
	{
		struct sockaddr sa; // can be safely cast to sockaddr_in
		socklen_t sa_len = sizeof(struct sockaddr_in);
		int len = 0;
		while ((len = (int) recvfrom(e->osc_fd, buffer, sizeof(buffer), 0, &sa, &sa_len)) > 0)
		{
			if (tosc_isBundle(buffer))
				printf("i dont manage with bundle\n BYE!\n"), exit(0);
			else
			{
				tosc_message osc;
				tosc_parseMessage(&osc, buffer, len);
				f(&osc, e);
			}
		}
	}
	else
	{
		static	size_t count = 0;
		//printf("TIMEOUT:%d\n", count);
		count++;
	}
}

//	On va faire un comportement specifique a open_bci
//	qui ressoit toutjour les messages par 8: (1 par channel)
void	test_osc_handler(tosc_message *osc, void *data)
{
	t_env	*e;
	int	i;
	int	chan;
	float	amp;

	printf("ook\n");
	e = (t_env*)data;
	for (i = 0; i < BCI_CHAN_NB; i++)
	{
		if ((chan = tosc_getNextInt32(osc)) != 1)
			return ;
		amp = tosc_getNextFloat(osc);
		//amp = 1 - amp;
		amp = (amp < 0.5 ? 0.5 : amp);
		amp = (amp > 0.97 ? 0.97 : amp);
		e->crv_end[0].amp = amp;
		e->crv_end[1].amp = amp;
		//e->crv_end[1].amp = 1.;
		printf("chan:%d	amp:%f\n", chan, amp);
	}
}

void	test_osc(t_env *e)
{

	osc_init(e, 9000);
	while (1)
	{
		osc_get_message(e, test_osc_handler);
	}
}
