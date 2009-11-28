#include <unistd.h>
#include "wpposixio.h"
#include "../../base/wpbase.h"

#ifdef __USE_UNIX98
ssize_t wp_pread (int filedes, void *buf, size_t nbytes, off_t offset)
{
	ssize_t n;
	if ((n = pread (filedes, buf, nbytes, offset)) == -1)
		wp_error_sys_warning ("pread error");
	return n;
}
		
ssize_t wp_pwrite (int filedes, void *buf, size_t nbytes, off_t offset)
{
	ssize_t n;
	if ((n = pwrite (filedes, buf, nbytes, offset)) == -1)
		wp_error_sys_warning ("pwrite error");
	return n;
}
#endif /* __USE_UNIX98 */
