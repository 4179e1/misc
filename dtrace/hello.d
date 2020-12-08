#!/usr/sbin/dtrace -s

dtrace:::BEGIN
{
	trace ("Hello, world!");
}

END
{
	trace ("Good bye!");
}
