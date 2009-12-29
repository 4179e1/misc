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
#endif /* _WPPOSIXTHREAD_H */
