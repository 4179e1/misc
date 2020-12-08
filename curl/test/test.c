#include <stdio.h>
#include <curl/curl.h>
 
int main(void)
{
  CURL *curl;
  CURLcode res;

  FILE *file = fopen ("README", "w+");
  if (file == NULL)
  {
	  fprintf (stderr, "fopen error\n");
	  exit (1);
  }
 
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "ftp://ftp.gnu.org/README");
	curl_easy_setopt (curl, CURLOPT_WRITEDATA, file);
    res = curl_easy_perform(curl);
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  return 0;
}

