#include <stdio.h>

void strcatt(char *s, char *t)
{
	while(*s)
		s++;
	while(*s++ = *t++)
		;
}

main()
{
	char s[20] = "abc"; //这里主要的问题是没有正确地为连接结果分配空间。C 没有提供自动管理的字符串类型。C 编译器只为源码中明确提到的对象分配空间 (对于字符串, 这包括字符数组和串常量)。程序员必须为字符串连接这样的运行期操作的结果分配足够的空间
	char t[] = "def";
	printf("%s\n",s);
	printf("%s\n",t);
	strcatt(s, t);
	printf("%s\n",s);
	return 0;

}
