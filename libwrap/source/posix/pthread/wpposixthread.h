#ifndef _WPPOSIXTHREAD_H
#define _WPPOSIXTHREAD_H

#include <pthread.h>

int wp_pthread_create (pthread_t *tidp, const pthread_attr_t *attr, void *(*start_rtn) (void *), void *arg);
int wp_pthread_join (pthread_t thread, void **rval_ptr);

int wp_pthread_cancel (pthread_t tid);

int wp_pthread_detach (pthread_t tid);

int wp_pthread_mutex_init (pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int wp_pthread_mutex_destroy (pthread_mutex_t *mutex);
int wp_pthread_mutex_lock (pthread_mutex_t *mutex);
int wp_pthread_mutex_trylock (pthread_mutex_t *mutex);
int wp_pthread_mutex_unlock (pthread_mutex_t *mutex);

int wp_pthread_rwlock_init (pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr);
int wp_pthread_rwlock_destroy (pthread_rwlock_t *rwlock);
int wp_pthread_rwlock_rdlock (pthread_rwlock_t *rwlock);
int wp_pthread_rwlock_wrlock (pthread_rwlock_t *rwlock);
int wp_pthread_rwlock_unlock (pthread_rwlock_t *rwlock);
int wp_pthread_rwlock_tryrdlock (pthread_rwlock_t *rwlock);
int wp_pthread_rwlock_trywrlock (pthread_rwlock_t *rwlock);

int wp_pthread_cond_init (pthread_cond_t *cond, pthread_condattr_t *buf);
int wp_pthread_cond_destroy (pthread_cond_t *cond);
int wp_pthread_cond_wait (pthread_cond_t *cond, pthread_mutex_t *mutex);
int wp_pthread_cond_timedwait (pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *timeout);
int wp_pthread_cond_signal (pthread_cond_t *cond);
int wp_pthread_cond_broadcast (pthread_cond_t *cond);
#endif /* _WPPOSIXTHREAD_H */
