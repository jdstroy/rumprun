/*
 * Like rumprun, except connects to a remote service.
 * Note, std* will be directed to the remote service (and they are
 * not even open by default), so example.so needs to be judiciously
 * selected, at least for now.
 */

#include "rumprun_common.c"

#include <rump/rumpclient.h>
#include <rump/rump_syscalls.h>

int
main(int argc, char *argv[])
{
	int ret, fd;

	ret = rumpclient_init();
	if (ret != 0)
		die("rumpclient init failed");
	/* this has to be the greatest hack ever */
	while ((fd = rump_sys_kqueue()) < 3)
		continue;
	rump_sys_close(fd);
	rumprun_so(argc, argv);
	/* NOTREACHED */
	return 0;
}
