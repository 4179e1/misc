#define ACE_NTRACE 0
#include "ace/Log_Msg.h"
#include "ace/streams.h"

#define TRACE ACE_TRACE(__func__)

int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
	// Output to default destination (stderr)
	ACE_LOG_MSG->open (argv[0]);
	TRACE;

	ACE_OSTREAM_TYPE *output = new std::ofstream ("log.txt");

	ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("%IThis will go to STDERR\n")));

	ACE_LOG_MSG->open (argv[0], ACE_Log_Msg::SYSLOG, ACE_TEXT ("syslogTest"));
	ACE_LOG_MSG->set_flags(ACE_Log_Msg::STDERR);
	ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("%IThis goes to STDERR & syslog\n")));

	ACE_LOG_MSG->msg_ostream (output, 0);
	ACE_LOG_MSG->set_flags (ACE_Log_Msg::OSTREAM);
	ACE_DEBUG ((LM_DEBUG,
				ACE_TEXT ("%IThis will got to STDERR, ")
				ACE_TEXT ("syslog & an ostream\n")));

	ACE_LOG_MSG->clr_flags (ACE_Log_Msg::OSTREAM);
	delete output;

	return 0;
}
