#!/usr/sbin/dtrace -s
#pragma D option quiet

/* activity.d -- Record fork() and exec() activity */

proc::do_fork:create
{
	/* Extract PID of child process from the psinfo_t pointed by args[0] */
	/* TODO: what is args[0]
	   http://docs.oracle.com/cd/E37670_01/E38608//dt_proc_prov.html
	 */

	childpid = args[0]->pr_pid;
	
	time[childpid] = timestamp;
	p_pid[childpid] = pid; /* Current process ID (Parent PID of new child) */
	p_name[childpid] = execname; /* Parent command name */
	p_exec[childpid] = ""; /* Child has not yet been exec'ed */
}

proc::do_execve_common:exec
/p_pid[pid] != 0/
{
	p_exec[pid] = args[0];	/* Child process path name */
}

proc::do_exit:exit
/p_pid[pid] != 0 && p_exec[pid] != ""/
{
	printf ("%s (%d) executed %s (%d) for %d microseconds\n", 
		p_name[pid], p_pid[pid], p_exec[pid], pid, (timestamp - time[pid])/1000);
}

proc::do_exit:exit
{
	printf ("%s (%d) forked itself (as %d) for %d microseconds\n",
		p_name[pid], p_pid[pid], pid, (timestamp - time[pid])/1000);
}
