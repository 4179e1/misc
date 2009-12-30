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

int wp_pthread_rwlock_init (pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr)
{
	int n;
	if ((n = pthread_rwlock_init (rwlock, attr)) != 0)
		wp_error_warning ("pthread_rwlock_init() error: %s", strerror(n));
	return n;
}

int wp_pthread_rwlock_destroy (pthread_rwlock_t *rwlock)
{
	int n;
	if ((n = pthread_rwlock_destroy (rwlock)) != 0)
		wp_error_warning ("pthread_rwlock_destroy() error: %s", strerror(n));
	return n;
}

int wp_pthread_rwlock_rdlock (pthread_rwlock_t *rwlock)
{
	int n;
	if ((n = pthread_rwlock_rdlock (rwlock)) != 0)
		wp_error_warning ("pthread_rwlock_rdlock() error: %s", strerror(n));
	return n;
}

int wp_pthread_rwlock_wrlock (pthread_rwlock_t *rwlock)
{
	int n;
	if ((n = pthread_rwlock_wrlock (rwlock)) != 0)
		wp_error_warning ("pthread_rwlock_wrlock() error: %s", strerror(n));
	return n;
}

int wp_pthread_rwlock_unlock (pthread_rwlock_t *rwlock)
{
	int n;
	if ((n = pthread_rwlock_unlock (rwlock)) != 0)
		wp_error_warning ("pthread_rwlock_unlock() error: %s", strerror(n));
	return n;
}

int wp_pthread_rwlock_tryrdlock (pthread_rwlock_t *rwlock)
{
	int n;
	if ((n = pthread_rwlock_tryrdlock (rwlock)) != 0)
		wp_error_warning ("pthread_rwlock_tryrdlock() error: %s", strerror (n));
	return n;
}

int wp_pthread_rwlock_trywrlock (pthread_rwlock_t *rwlock)
{
	int n;
	if ((n = pthread_rwlock_trywrlock (rwlock)) != 0)
		wp_error_warning ("pthread_rwlock_trywrlock() error: %s", strerror (n));
	return n;
}

int wp_pthread_cond_init (pthread_cond_t *cond, pthread_condattr_t *buf)
{
	int n;
	if ((n = pthread_cond_init (cond, buf)) != 0)
		wp_error_warning ("pthread_cond_init() error: %s", strerror(n));
	return n;
}

int wp_pthread_cond_destroy (pthread_cond_t *cond)
{
	int n;
	if ((n = pthread_cond_destroy (cond)) != 0)
		wp_error_warning ("pthread_cond_destroy() error: %s", strerror(n));
	return n;
}

int wp_pthread_cond_wait (pthread_cond_t *cond, pthread_mutex_t *mutex)
{
	int n;
	if ((n = pthread_cond_wait (cond, mutex)) != 0)
		wp_error_warning ("pthread_cond_wait() error: %s", strerror(n));
	return n;
}

int wp_pthread_cond_timedwait (pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *timeout)
{
	int n;
	if ((n = pthread_cond_timedwait (cond, mutex, timeout)) != 0)
		wp_error_warning ("pthread_cond_timedwait() error: %s", strerror (n));
	return n;
}

int wp_pthread_cond_signal (pthread_cond_t *cond)
{
	int n;
	if ((n = pthread_cond_signal (cond)) != 0)
		wp_error_warning ("pthread_cond_signal() error: %s", strerror(n));
	return n;
}

int wp_pthread_cond_broadcast (pthread_cond_t *cond)
{
	int n;
	if ((n = pthread_cond_broadcast (cond)) != 0)
		wp_error_warning ("pthread_cond_broadcast() error: %s", strerror(n));
	return n;
}
