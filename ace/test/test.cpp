#define ACE_NTRACE 0
#include "ace/Log_Msg.h"

#define TRACE ACE_TRACE(__func__)
void foo (void)
{
	TRACE;
}

int main (void)
{
	ACE_LOG_MSG->priority_mask (LM_TRACE | LM_DEBUG | LM_NOTICE, ACE_Log_Msg::PROCESS);
	TRACE;
	ACE_LOG_MSG->priority_mask (LM_NOTICE, ACE_Log_Msg::PROCESS);
	foo ();
	return 0;
}

