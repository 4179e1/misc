#include <string.h>
#include "wpposixthread.h"
#include "wpbase.h"

int wp_pthread_create (pthread_t *tidp, const pthread_attr_t *attr, void *(*start_rtn) (void *), void *arg)
{
	int n;
	if ((n = pthread_create (tidp, attr, start_rtn, arg)) != 0)
		wp_error_warning ("pthread_create() error: %s", strerror(n));
	return n;
}

int wp_pthread_join (pthread_t thread, void **rval_ptr)
{
	int n;
	if ((n = pthread_join (thread, rval_ptr)) != 0)
		wp_error_warning ("pthread_join() error: %s", strerror(n));
	return n;
}

int wp_pthread_cancel (pthread_t tid)
{
	int n;
	if ((n = pthread_cancel (tid)) !=0)
		wp_error_warning ("pthread_cancel() error: %s", strerror(n));
	return n;
}

int wp_pthread_detach (pthread_t tid)
{
	int n;
	if ((n = pthread_cancel (tid)) != 0)
		wp_error_warning ("pthread_detach() error: %s", strerror(n));
	return n;
}

int wp_pthread_mutex_init (pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
{
	int n;
	if ((n = pthread_mutex_init (mutex, attr)) != 0)
		wp_error_warning ("pthread_mutex_init() error: %s", strerror(n));
	return n;
}

int wp_pthread_mutex_destroy (pthread_mutex_t *mutex)
{
	int n;
	if ((n = pthread_mutex_destroy (mutex)) != 0)
		wp_error_warning ("pthread_mutex_destroy() error: %s", strerror(n));
	return n;
}

int wp_pthread_mutex_lock (pthread_mutex_t *mutex)
{
	int n;
	if ((n = pthread_mutex_lock (mutex)) != 0)
		wp_error_warning ("pthread_mutex_lock() error: %s", strerror(n));
	return n;
}

int wp_pthread_mutex_trylock (pthread_mutex_t *mutex)
{
	int n;
	if ((n = pthread_mutex_trylock (mutex)) != 0)
		wp_error_warning ("pthread_mutex_trylock() error: %s", strerror(n));
	return n;
}

int wp_pthread_mutex_unlock (pthread_mutex_t *mutex)
{
	int n;
	if ((n = pthread_mutex_unlock (mutex)) != 0)
		wp_error_warning ("pthread_mutex_unlock() error: %s", strerror(n));
	return n;
}
