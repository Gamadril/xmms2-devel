/*  XMMS2 - X Music Multiplexer System
 *  Copyright (C) 2003	Peter Alm, Tobias Rundstr�m, Anders Gustafsson
 * 
 *  PLUGINS ARE NOT CONSIDERED TO BE DERIVED WORK !!!
 * 
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *                   
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 */




#include "util.h"
#include "transport.h"
#include "playlist.h"
#include "medialib.h"
#include "plugin.h"
#include "plugin_int.h"

#include <glib.h>

int
main (int argc, char **argv)
{
	xmms_plugin_t *a;
	xmms_medialib_t *medialib;

	g_thread_init (NULL);

	if (!xmms_plugin_init ())
		return 1;

	a = xmms_medialib_find_plugin ("sqlite");
	if (!a) 
		return 1;

	medialib = xmms_medialib_init (a);
	g_return_val_if_fail (medialib, -1);

	if (argc < 1) return 1;

	xmms_medialib_add_dir (medialib, argv[1]);


	xmms_medialib_close (medialib);

	return 0;
		
}

