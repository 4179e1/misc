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


int wp_pthread_attr_init (pthread_attr_t *attr)
{
	int n;
	if ((n = pthread_attr_init (attr)) != 0)
		wp_error_warning ("pthread_attr_init() error: %s", strerror(n));
	return n;
}

int wp_pthread_attr_destroy (pthread_attr_t *attr)
{
	int n;
	if ((n = pthread_attr_destroy (attr)) != 0)
		wp_error_warning ("pthread_attr_destroy() error: %s", strerror (n));
	return n;
}

int wp_pthread_attr_getdetachstate (const pthread_attr_t *attr, int *detachstate)
{
	int n;
	if ((n = pthread_attr_getdetachstate (attr, detachstate)) != 0)
		wp_error_warning ("pthread_attr_getdetachstate() error: %s", strerror (n));
	return n;
}

int wp_pthread_attr_setdetachstate (pthread_attr_t *attr, int detachstate)
{
	int n;
	if ((n = pthread_attr_setdetachstate (attr, detachstate)) != 0)
		wp_error_warning ("pthread_attr_setdetachstate() error: %s", strerror (n));
	return n;
}
	
int wp_pthread_attr_getstack (const pthread_attr_t *attr, void **stackaddr, size_t *stacksize)
{
	int n;
	if ((n = pthread_attr_getstack (attr, stackaddr, stacksize)) != 0)
		wp_error_warning ("pthread_attr_getstack() error: %s", strerror (n));
	return n;
}

int wp_pthread_attr_setstack (pthread_attr_t *attr, void *stackaddr, size_t stacksize)
{
	int n;
	if ((n = pthread_attr_setstack (attr, stackaddr, stacksize)) != 0)
		wp_error_warning ("pthread_attr_setstack() error: %s", strerror (n));
	return n;
}

int wp_pthread_attr_getguardsize (const pthread_attr_t *attr, size_t *guardsize)
{
	int n;
	if ((n = pthread_attr_getguardsize (attr, guardsize)) != 0)
		wp_error_warning ("pthread_attr_getguardsize() error: %s", strerror (n));
	return n;
}

int wp_pthread_attr_setguardsize (pthread_attr_t *attr, size_t guardsize)
{
	int n;
	if ((n = pthread_attr_setguardsize (attr, guardsize)) != 0)
		wp_error_warning ("pthread_attr_setguardsize() error: %s", strerror (n));
	return n;
}


#ifdef __USE_UNIX98
int wp_pthread_setconcurrency (int level)
{
	int n;
	if ((n = pthread_setconcurrency (level)) != 0)
		wp_error_warning ("pthread_attr_setconcurrency() error: %s", strerror(n));
	return n;
}
#endif /* __USE_UNIX98 */

int wp_pthread_mutexattr_init (pthread_mutexattr_t *attr)
{
	int n;
	if ((n = pthread_mutexattr_init (attr)) != 0)
		wp_error_warning ("pthread_mutexattr_init() error: %s", strerror (n));
	return n;
}

int wp_pthread_mutexattr_destroy (pthread_mutexattr_t *attr)
{
	int n;
	if ((n = pthread_mutexattr_destroy (attr)) != 0)
		wp_error_warning ("pthread_mutexattr_destroy() error: %s", strerror (n));
	return n;
}

int wp_pthread_mutexattr_getpshared (const pthread_mutexattr_t *attr, int *pshared)
{
	int n;
	if ((n = pthread_mutexattr_getpshared (attr, pshared)) != 0)
		wp_error_warning ("pthread_mutexattr_getpshared() error: %s", strerror (n));
	return n;
}

int wp_pthread_mutexattr_setpshared (pthread_mutexattr_t *attr, int pshared)
{
	int n;
	if ((n = pthread_mutexattr_setpshared (attr, pshared)) != 0)
		wp_error_warning ("pthread_mutexattr_setpshared() error: %s", strerror (n));
	return n;
}

#ifdef __USE_UNIX98
int wp_pthread_mutexattr_gettype (const pthread_mutexattr_t *attr, int *type)
{
	int n;
	if ((n = pthread_mutexattr_gettype (attr, type)) != 0)
		wp_error_warning ("pthread_mutexattr_gettype() error: %s", strerror (n));
	return n;
}

int wp_pthread_mutexattr_settype (pthread_mutexattr_t *attr, int type)
{
	int n;
	if ((n = pthread_mutexattr_settype (attr, type)) != 0)
		wp_error_warning ("pthread_mutexattr_settype() error: %s", strerror (n));
	return n;
}
#endif /* __USE_UNIX98 */

int wp_pthread_rwlockattr_init (pthread_rwlockattr_t *attr)
{
	int n;
	if ((n = pthread_rwlockattr_init (attr)) != 0)
		wp_error_warning ("pthread_rwlockattr_init() error: %s", strerror (n));
	return n;
}

int wp_pthread_rwlockattr_destroy (pthread_rwlockattr_t *attr)
{
	int n;
	if ((n = pthread_rwlockattr_destroy (attr)) != 0)
		wp_error_warning ("pthread_rwlockattr_destroy() error: %s", strerror (n));
	return n;
}

int wp_pthread_rwlockattr_getpshared (const pthread_rwlockattr_t *attr, int *pshared)
{
	int n;
	if ((n = pthread_rwlockattr_getpshared (attr, pshared)) != 0)
		wp_error_warning ("pthread_rwlockattr_getpshared() error: %s", strerror (n));
	return n;
}

int wp_pthread_rwlockattr_setpshared (pthread_rwlockattr_t *attr, int pshared)
{
	int n;
	if ((n = pthread_rwlockattr_setpshared (attr, pshared)) != 0)
		wp_error_warning ("pthread_rwlockattr_setpshared() error: %s", strerror (n));
	return n;
}

int wp_pthread_condattr_init (pthread_condattr_t *attr)
{
	int n;
	if ((n = pthread_condattr_init (attr)) != 0)
		wp_error_warning ("pthread_condattr_init() error: %s", strerror (n));
	return n;
}

int wp_pthread_condattr_destroy (pthread_condattr_t *attr)
{
	int n;
	if ((n = pthread_condattr_destroy (attr)) != 0)
		wp_error_warning ("pthread_condattr_destroy() error: %s", strerror (n));
	return n;
}

int wp_pthread_condattr_getpshared (const pthread_condattr_t *attr, int *pshared)
{
	int n;
	if ((n = pthread_condattr_getpshared (attr, pshared)) != 0)
		wp_error_warning ("pthread_condattr_getpshared() error: %s", strerror (n));
	return n;
}

int wp_pthread_condattr_setpshared (pthread_condattr_t *attr, int pshared)
{
	int n;
	if ((n = pthread_condattr_setpshared (attr, pshared)) != 0)
		wp_error_warning ("pthread_condattr_setpshared() error: %s", strerror (n));
	return n;
}

int wp_pthread_key_create (pthread_key_t *keyp, void (*destroctor)(void *))
{
	int n;
	if ((n = pthread_key_create(keyp, destroctor)) != 0)
		wp_error_warning ("pthread_key_create() error: %s", strerror (n));
	return n;
}

int wp_pthread_key_delete (pthread_key_t key)
{
	int n;
	if ((n = pthread_key_delete (key)) != 0)
		wp_error_warning ("pthread_key_delete() error: %s", strerror (n));
	return n;
}

int wp_pthread_once (pthread_once_t *initflag, void (*initfn)(void))
{
	int n;
	if ((n = pthread_once (initflag, initfn)) != 0)
		wp_error_warning ("pthread_once() error: %s", strerror (n));
	return n;
}

void *wp_pthread_getspecific (pthread_key_t key)
{
	void *p;
	if ((p = pthread_getspecific (key)) == NULL)
		wp_error_warning ("pthread_getspecific() error");
	return p;
}

int wp_pthread_setspecific (pthread_key_t key, const void *value)
{
	int n;
	if ((n = pthread_setspecific (key, value)) != 0)
		wp_error_warning ("pthrad_setspecific() error: %s", strerror (n));
	return n;
}

int wp_pthread_setcancelstate (int state, int *oldstate)
{
	int n;
	if ((n = pthread_setcancelstate (state, oldstate)) != 0)
		wp_error_warning ("pthread_setcancelstate() error: %s", strerror (n));
	return n;
}

int wp_pthread_setcanceltype (int type, int *oldtype)
{
	int n;
	if ((n = pthread_setcanceltype (type, oldtype)) != 0)
		wp_error_warning ("pthread_setcanceltype() error: %s", strerror (n));
	return n;
}

int wp_phtread_sigmask (int how, const sigset_t *set, sigset_t *oset)
{
	int n;
	if ((n = pthread_sigmask (how, set, oset)) != 0)
		wp_error_warning ("pthread_sigmask() error: %s", strerror (n));
	return n;
}

int wp_pthread_kill (pthread_t thread, int signo)
{
	int n;
	if ((n = pthread_kill (thread, signo)) != 0)
		wp_error_warning ("pthread_kill() error: %s", strerror (n));
	return n;
}

int wp_pthread_atfork (void (*prepare) (void), void (*parent) (void), void (*child) (void))
{
	int n;
	if ((n = pthread_atfork (prepare, parent, child)) != 0)
		wp_error_warning ("pthread_atfork() error: %s", strerror (n));
	return n;
}
