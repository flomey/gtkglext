/* GdkGLExt - OpenGL Extension to GDK
 * Copyright (C) 2002  Naofumi Yasufuku
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA.
 */

#ifndef __GDK_GL_CONTEXT_H__
#define __GDK_GL_CONTEXT_H__

#include <gdk/gdktypes.h>

#include <gdk/gdkgltypes.h>

G_BEGIN_DECLS

typedef struct _GdkGLContextClass GdkGLContextClass;

#define GDK_TYPE_GL_CONTEXT              (gdk_gl_context_get_type ())
#define GDK_GL_CONTEXT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_GL_CONTEXT, GdkGLContext))
#define GDK_GL_CONTEXT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_GL_CONTEXT, GdkGLContextClass))
#define GDK_IS_GL_CONTEXT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_GL_CONTEXT))
#define GDK_IS_GL_CONTEXT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_GL_CONTEXT))
#define GDK_GL_CONTEXT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_GL_CONTEXT, GdkGLContextClass))

struct _GdkGLContext
{
  GObject parent_instance;

  GdkGLDrawable *gldrawable;

  GdkGLConfig *glconfig;
  gint render_type;
  GdkGLContext *share_list;
  gboolean is_direct;
};

struct _GdkGLContextClass
{
  GObjectClass parent_class;
};

GType         gdk_gl_context_get_type  (void);

GdkGLContext *gdk_gl_context_new       (GdkGLDrawable *gldrawable,
                                        GdkGLConfig   *glconfig,
                                        gint           render_type,
                                        GdkGLContext  *share_list,
                                        gboolean       direct);

G_END_DECLS

#endif /* __GDK_GL_CONTEXT_H__ */