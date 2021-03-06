/*
 * Amanda, The Advanced Maryland Automatic Network Disk Archiver
 * Copyright (c) 2008 Zmanda Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef ELEMENT_GLUE_H
#define ELEMENT_GLUE_H

#include <glib.h>
#include <glib-object.h>
#include "xfer-element.h"
#include "semaphore.h"

/*
 * Class declaration
 */

GType xfer_element_glue_get_type(void);
#define XFER_ELEMENT_GLUE_TYPE (xfer_element_glue_get_type())
#define XFER_ELEMENT_GLUE(obj) G_TYPE_CHECK_INSTANCE_CAST((obj), xfer_element_glue_get_type(), XferElementGlue)
#define XFER_ELEMENT_GLUE_CONST(obj) G_TYPE_CHECK_INSTANCE_CAST((obj), xfer_element_glue_get_type(), XferElementGlue const)
#define XFER_ELEMENT_GLUE_CLASS(klass) G_TYPE_CHECK_CLASS_CAST((klass), xfer_element_glue_get_type(), XferElementGlueClass)
#define IS_XFER_ELEMENT_GLUE(obj) G_TYPE_CHECK_INSTANCE_TYPE((obj), xfer_element_glue_get_type ())
#define XFER_ELEMENT_GLUE_GET_CLASS(obj) G_TYPE_INSTANCE_GET_CLASS((obj), xfer_element_glue_get_type(), XferElementGlueClass)

/*
 * Main object structure
 */

typedef struct XferElementGlue {
    XferElement __parent__;

    /* the stuff we might use, depending on what flavor of glue we're
     * providing.. */
    int pipe[2];

    /* for push/pull, a ring buffer of ptr/size pairs */
    struct { gpointer buf; size_t size; } *ring;
    semaphore_t *ring_used_sem, *ring_free_sem;
    gint ring_head, ring_tail;

    GThread *thread;
    GThreadFunc threadfunc;
} XferElementGlue;

/*
 * Class definition
 */

typedef struct {
    XferElementClass __parent__;
} XferElementGlueClass;

/* Constructor */

XferElement * xfer_element_glue(void);

/* the mech pairs supported by this object */

extern xfer_element_mech_pair_t *xfer_element_glue_mech_pairs;

#endif
