#include <Ecore.h>

#include <stdio.h>

#include "internal/client_ipc.h"
#include "xmms/xmmsclient.h"
#include "internal/xmmsclient_int.h"

static int
on_fd_data (void *udata, Ecore_Fd_Handler *handler)
{
	xmmsc_ipc_t *ipc = udata;

	if (ecore_main_fd_handler_active_get (handler, ECORE_FD_ERROR)) {
		xmmsc_ipc_error_set (ipc, "Remote host disconnected, or something!");
		xmmsc_ipc_disconnect (ipc);

		return 0;
	}

	if (ecore_main_fd_handler_active_get (handler, ECORE_FD_READ))
		xmmsc_ipc_io_in_callback (ipc);

	if (ecore_main_fd_handler_active_get (handler, ECORE_FD_WRITE))
		xmmsc_ipc_io_out_callback (ipc);

	return 1;
}

void on_prepare (void *udata, Ecore_Fd_Handler *handler)
{
	xmmsc_ipc_t *ipc = udata;
	int flags = ECORE_FD_READ | ECORE_FD_ERROR;

	if (xmmsc_ipc_io_out (ipc))
		flags |= ECORE_FD_WRITE;

	ecore_main_fd_handler_active_set (handler, flags);
}

gboolean
xmmsc_ipc_setup_with_ecore (xmmsc_connection_t *c)
{
	Ecore_Fd_Handler *fdh;
	int flags = ECORE_FD_READ | ECORE_FD_ERROR;

	if (xmmsc_ipc_io_out (c->ipc))
		flags |= ECORE_FD_WRITE;

	fdh = ecore_main_fd_handler_add (xmmsc_ipc_fd_get (c->ipc), flags,
	                                 on_fd_data, c->ipc, NULL, NULL);
	ecore_main_fd_handler_prepare_callback_set (fdh, on_prepare, c->ipc);

	return TRUE;
}

