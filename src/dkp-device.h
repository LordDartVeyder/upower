/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2008 David Zeuthen <david@fubar.dk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef __DKP_DEVICE_H__
#define __DKP_DEVICE_H__

#include <glib-object.h>
#include <polkit-dbus/polkit-dbus.h>
#include <devkit-gobject.h>

#include "dkp-daemon.h"

G_BEGIN_DECLS

#define DKP_SOURCE_TYPE_DEVICE	(dkp_device_get_type ())
#define DKP_DEVICE(o)	   	(G_TYPE_CHECK_INSTANCE_CAST ((o), DKP_SOURCE_TYPE_DEVICE, DkpDevice))
#define DKP_DEVICE_CLASS(k)	(G_TYPE_CHECK_CLASS_CAST((k), DKP_SOURCE_TYPE_DEVICE, DkpDeviceClass))
#define DKP_IS_DEVICE(o)	(G_TYPE_CHECK_INSTANCE_TYPE ((o), DKP_SOURCE_TYPE_DEVICE))
#define DKP_IS_DEVICE_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), DKP_SOURCE_TYPE_DEVICE))
#define DKP_DEVICE_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), DKP_SOURCE_TYPE_DEVICE, DkpDeviceClass))

typedef struct
{
	GObject		 parent;
} DkpDevice;

typedef struct
{
	GObjectClass	 parent_class;

	/* vtable */
	gboolean	(*changed)		(DkpDevice	*device,
						 DevkitDevice	*d,
						 gboolean	 synthesized);
	void		(*removed)		(DkpDevice	*device);
	const char	*(*get_object_path)	(DkpDevice	*device);
} DkpDeviceClass;

GType		 dkp_device_get_type		(void);
DkpDevice	*dkp_device_new			(DkpDaemon	*daemon,
						 DevkitDevice	*d);
gboolean	 dkp_device_changed	 	(DkpDevice	*device,
						 DevkitDevice	*d,
						 gboolean	 synthesized);
void		 dkp_device_removed	 	(DkpDevice	*device);
const char	*dkp_device_get_object_path	(DkpDevice	*device);

G_END_DECLS

#endif /* __DKP_DEVICE_H__ */