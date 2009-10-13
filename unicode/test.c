#include <stdio.h>

int main(void)
{
	char str[]="abc你好def";
	char str2[1024];
	str2[0]='\0';

	char *ptr = str;
	int i = 0;

	while (*ptr != '\0') {
		if (isascii(*ptr))
		{
			str2[i] = *ptr;
			i++;
		}
		ptr++;
	}

	str[++i] = '\0';
	printf ("%s\n", str);
	printf ("%s\n", str2);

	return 0;
}
