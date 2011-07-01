#include "ace/INET_Addr.h"
#include "ace/SOCK_Stream.h"
#include "ace/SOCK_Connector.h"
#include "ace/Log_Msg.h"
#include <iostream>

int ACE_TMAIN (int argc, char *argv[])
{
	ACE_INET_Addr srvr (50000, ACE_LOCALHOST);
	ACE_SOCK_Connector connector;
	ACE_SOCK_Stream peer;
	
	if (connector.connect (peer, srvr) == -1)
	{
		ACE_ERROR_RETURN ((LM_ERROR, ACE_TEXT ("%p\n"), ACE_TEXT("connect")), 1);
	}

	int bc;
	char buf[64];

	peer.send_n ("uptime\n", 7);
	bc = peer.recv (buf, sizeof (buf));
	
	std::cout << bc;

	peer.close ();

	return (0);
}
