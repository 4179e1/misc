#include <stdio.h>
#include <assert.h>
#include <event.h>
#include <event2/http.h>

int main (void)
{
	struct evkeyvalq header;
	char *query = "q=test&s=some+thing";

	int i = evhttp_parse_query_str (query, &header);
	assert (i == 0);

	const char *q = evhttp_find_header (&header, "q");

	printf ("%s\n", q);

	return 0;
}
