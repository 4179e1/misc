#!/usr/sbin/dtrace -s

/* TODO  is this thread safe ? */

syscall::read:entry,
syscall::write:entry
/pid == $1/
{
  ts[probefunc] = timestamp;
  printf ("tid %d %s\n", tid, probefunc);
}

syscall::read:return,
syscall::write:return
/pid == $1 && ts[probefunc] != 0/
{
  printf ("tid %d %s ", tid, probefunc);
  printf("%d nsecs\n", timestamp - ts[probefunc]);
}
