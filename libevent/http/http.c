#if 0
clang -g -o `basename $0 .c` $0 `pkg-config --cflags --libs libevent libwp0  glib-2.0`
exit 0
#endif

#define MAX_LENGTH 1024

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include <assert.h>
#include <libwp.h>
#include <glib.h>
#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>

void setup_output_header (struct evhttp_request *request)
{
	struct evkeyvalq *output_headers;

	assert (request != NULL);

	output_headers = evhttp_request_get_output_headers (request);
	evhttp_add_header(output_headers, "Content-Type", "text/html; charset=UTF-8");  
}

void setup_authorization_header (struct evhttp_request *request)
{
	struct evkeyvalq *output_headers;

	assert (request != NULL);

	output_headers = evhttp_request_get_output_headers (request);
	evhttp_add_header (output_headers, "WWW-Authenticate", "Basic realm=\"What's up?\"");
}

void request_authorization (struct evhttp_request *request)
{
	struct evbuffer *buf;

	char auth_page[] = 	"<html>\n"
						"\t<head>\n"
						"\t\t<title>Authentication required!</title>\n"
						"\t</head>\n"
						"\t<body>\n"
						"\t\t<p>Authentication required!</h1>\n"
						"\t</body>\n"
						"</html>";


	buf = evbuffer_new ();
	if (buf == NULL)
	{
		wp_warning ("evbuffer_new() failed");
		evhttp_send_error (request, HTTP_INTERNAL, "INTERNAL ERROR!");
		return;
	}


	setup_authorization_header (request);

	evbuffer_add (buf, auth_page, sizeof (auth_page));

	evhttp_send_reply(request, 401, "Authentication required!", buf);  

	evbuffer_free (buf);

}

static bool auth_user (const char *user, const char *passwd)
{
	//wp_message ("Authorizating User: %s with Passwd: %s", user, passwd);
	if ( (strcmp (user, "lyre") == 0) && (strcmp (passwd, "qwer1234") == 0))
	{
		return true;
	}
	return false;
}


bool do_authorization (struct evhttp_request *request)
{
	struct evkeyvalq *header;
	const char *auth;
	char method[MAX_LENGTH];
	char val[MAX_LENGTH];
	guchar *decode;
	gsize decoded_len = 10;
	char basic_authorization[]="Basic";
	char *user;
	char *passwd;
	bool result;


	header = evhttp_request_get_input_headers (request);
	auth = evhttp_find_header (header, "Authorization");
	if (auth == NULL)
	{
		return false;
	}

	if (sscanf (auth, "%s %s", method, val) != 2)
	{
		/* Malformed header 'Authorization' */
		return false;
	}

	if (strncasecmp (method, basic_authorization, sizeof (basic_authorization)) != 0)
	{
		/* Unsupported authorization method, only implenmented 'Basic' */
		return false;
	}

	/* decoded authorization string should formated as `user:passwd' */
	decode = g_base64_decode (val, &decoded_len);
	user = (char *)decode;
	passwd = strchr (user, ':');

	/* slipt user:passwd failed */
	if ( (passwd == NULL) || (passwd == user) || (*passwd == '\0') )
	{
		g_free (decode);
		return false;
	}
	*passwd++ = '\0';

	result = auth_user (user, passwd);

	g_free (decode);
	
	return result;
}

void do_reply (struct evhttp_request *request, const char *filename)
{
	struct evbuffer *buf;
	struct stat sbuf;
	int fd;
	
	if (wp_stat (filename, &sbuf) < 0)
	{
		evhttp_send_error (request, HTTP_NOTFOUND, "NOT FOUND!");
		return;
	}

	wp_message ("Filename: %s Size: %d", filename, sbuf.st_size);

	fd = wp_open (filename, O_RDONLY, 0);
	if (fd == -1)
	{
		evhttp_send_error (request, HTTP_INTERNAL, "INTERNAL ERROR!");
		return;
	}

	buf = evbuffer_new ();
	if (buf == NULL)
	{
		wp_warning ("evbuffer_new() failed");
		wp_close (fd);

		evhttp_send_error (request, HTTP_INTERNAL, "INTERNAL ERROR!");
		return;
	}

	if (evbuffer_add_file (buf, fd, 0, sbuf.st_size) == -1)
	{
		wp_warning ("evbuffer_add_file() failed");
		evbuffer_free (buf);

		evhttp_send_error (request, HTTP_INTERNAL, "INTERNAL ERROR!");
		return;
	}

	setup_output_header (request);

	evhttp_send_reply (request, HTTP_OK, "OK", buf);
	evbuffer_free (buf);
}


void ev_callback (struct evhttp_request * request, void *data)
{
	const struct evhttp_uri *uri;
	char filename[MAX_LENGTH];

	uri = evhttp_request_get_evhttp_uri (request);
	if (uri == NULL)
	{
		wp_warning ("evhttp_request_get_evhttp_uri() failed");
		evhttp_send_error (request, HTTP_INTERNAL, "INTERNAL ERROR!");
		return;
	}


	if (!do_authorization (request))
	{
		wp_message ("Authorization failed");
		request_authorization (request);
		return;
	}

	const char *path = evhttp_uri_get_path (uri);
	if (path[strlen(path) - 1] == '/')
	{
		snprintf (filename, sizeof(filename), ".%sindex.html", path);
	}
	else
	{
		snprintf (filename, sizeof(filename), ".%s", path);
	}

	do_reply (request, filename);
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

	evhttp_set_allowed_methods (httpd, EVHTTP_REQ_GET | EVHTTP_REQ_POST);

	event_base_dispatch (base);

	return 0;
}
