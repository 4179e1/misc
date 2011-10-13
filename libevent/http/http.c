#if 0
clang -g -o `basename $0 .c` $0 `pkg-config --cflags --libs libevent libwp0`
exit 0
#endif

#include <stdio.h>
#include <stdlib.h>
#include <libwp.h>
#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>

void ev_callback (struct evhttp_request * request, void *data)
{
	const struct evhttp_uri *uri;
	struct evbuffer *buf;

	uri = evhttp_request_get_evhttp_uri (request);
	if (uri == NULL)
	{
		wp_warning ("evhttp_request_get_evhttp_uri() failed");
		return;
	}

	const char *path = evhttp_uri_get_path (uri);
	wp_message ("Path: %s", path, fragment, scheme);

	buf = evbuffer_new ();
	if (buf == NULL)
	{
		wp_warning ("evbuffer_new() failed");
		return;
	}
	evbuffer_add (buf, "Hello world!", 12);
	evhttp_send_reply (request, HTTP_OK, "OK", buf);

	evbuffer_free (buf);
}

int main(int argc, char *argv[])
{
	struct event_base *base;
	struct evhttp *httpd;

	base = event_base_new ();
	if (base == NULL)
	{
		wp_critical ("event_base_new()failed");
	}

	httpd = evhttp_new (base);
	if (httpd == NULL)
	{
		wp_critical ("ev_http_new() failed");
	}

	if (evhttp_bind_socket (httpd, "0.0.0.0", 6789) == -1)
	{
		wp_critical ("evhttp_bind_socket() failed");
	}

	evhttp_set_gencb (httpd, ev_callback, NULL);

	event_base_dispatch (base);

	return 0;
}
