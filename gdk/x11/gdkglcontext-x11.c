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

#include "gdkgldrawable.h"
#include "gdkglconfig.h"
#include "gdkglprivate-x11.h"
#include "gdkglcontext-x11.h"

static void     gdk_gl_context_impl_x11_init         (GdkGLContextImplX11      *impl);
static void     gdk_gl_context_impl_x11_class_init   (GdkGLContextImplX11Class *klass);

static GObject *gdk_gl_context_impl_x11_constructor  (GType                     type,
                                                      guint                     n_construct_properties,
                                                      GObjectConstructParam    *construct_properties);
static void     gdk_gl_context_impl_x11_finalize     (GObject                  *object);

static gpointer parent_class = NULL;

GType
gdk_gl_context_impl_x11_get_type (void)
{
  static GType type = 0;

  if (!type)
    {
      static const GTypeInfo type_info = {
        sizeof (GdkGLContextImplX11Class),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) gdk_gl_context_impl_x11_class_init,
        (GClassFinalizeFunc) NULL,
        NULL,                   /* class_data */
        sizeof (GdkGLContextImplX11),
        0,                      /* n_preallocs */
        (GInstanceInitFunc) gdk_gl_context_impl_x11_init,
      };

      type = g_type_register_static (GDK_TYPE_GL_CONTEXT,
                                     "GdkGLContextImplX11",
                                     &type_info, 0);
    }

  return type;
}

static void
gdk_gl_context_impl_x11_init (GdkGLContextImplX11 *impl)
{
  /* 0-initialization is good for all other fields. */

  GDK_GL_NOTE (FUNC, g_message (" -- gdk_gl_context_impl_x11_init ()"));

  impl->is_constructed = FALSE;
}

static void
gdk_gl_context_impl_x11_class_init (GdkGLContextImplX11Class *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  GDK_GL_NOTE (FUNC, g_message (" -- gdk_gl_context_impl_x11_class_init ()"));

  parent_class = g_type_class_peek_parent (klass);

  object_class->constructor = gdk_gl_context_impl_x11_constructor;
  object_class->finalize    = gdk_gl_context_impl_x11_finalize;
}

static GObject *
gdk_gl_context_impl_x11_constructor (GType                  type,
                                     guint                  n_construct_properties,
                                     GObjectConstructParam *construct_properties)
{
  GObject *object;
  GdkGLContext *glcontext;
  GdkGLContextImplX11 *impl;

  GdkGLContextImplX11 *share_impl = NULL;
  GLXContext share_glxcontext = NULL;

  XVisualInfo *xvinfo;

  object = G_OBJECT_CLASS (parent_class)->constructor (type,
                                                       n_construct_properties,
                                                       construct_properties);

  GDK_GL_NOTE (FUNC, g_message (" -- gdk_gl_context_impl_x11_constructor ()"));

  glcontext = GDK_GL_CONTEXT (object);
  impl = GDK_GL_CONTEXT_IMPL_X11 (object);

  /*
   * Create an OpenGL rendering context.
   */

  if (glcontext->share_list != NULL)
    {
      share_impl = GDK_GL_CONTEXT_IMPL_X11 (glcontext->share_list);
      share_glxcontext = share_impl->glxcontext;
    }

  impl->xdisplay = gdk_x11_gl_config_get_xdisplay (glcontext->glconfig);
  xvinfo = gdk_x11_gl_config_get_xvinfo (glcontext->glconfig);

  impl->glxcontext = glXCreateContext (impl->xdisplay,
                                       xvinfo,
                                       share_glxcontext,
                                       glcontext->is_direct == TRUE ? True : False );
  if (impl->glxcontext == NULL)
    goto FAIL;

  glcontext->is_direct = glXIsDirect (impl->xdisplay, impl->glxcontext) ? TRUE : FALSE;

  /*
   * Successfully constructed?
   */

  impl->is_constructed = TRUE;

 FAIL:
  return object;
}

static void
gdk_gl_context_impl_x11_finalize (GObject *object)
{
  GdkGLContextImplX11 *impl = GDK_GL_CONTEXT_IMPL_X11 (object);

  GDK_GL_NOTE (FUNC, g_message (" -- gdk_gl_context_impl_x11_finalize ()"));

  if (impl->glxcontext != NULL)
    {
      if (impl->glxcontext == glXGetCurrentContext ())
        glXMakeCurrent (impl->xdisplay, None, NULL);

      glXDestroyContext (impl->xdisplay, impl->glxcontext);
      impl->glxcontext = NULL;
    }

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

GdkGLContext *
_gdk_x11_gl_context_new (GdkGLDrawable *gldrawable,
                         GdkGLConfig   *glconfig,
                         gint           render_type,
                         GdkGLContext  *share_list,
                         gboolean       direct)
{
  GdkGLContext *glcontext;
  GdkGLContextImplX11 *impl;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_context_new ()"));

  /*
   * Instanciate the GdkGLContextImplX11 object.
   */

  glcontext = g_object_new (GDK_TYPE_GL_CONTEXT_IMPL_X11,
                            "gldrawable",  gldrawable,
                            "glconfig",    glconfig,
                            "render_type", render_type,
                            "share_list",  share_list,
                            "is_direct",   direct,
                            NULL);
  impl = GDK_GL_CONTEXT_IMPL_X11 (glcontext);

  if (!impl->is_constructed)
    {
      g_object_unref (G_OBJECT (glcontext));
      return NULL;
    }

  return glcontext;
}

Display *
gdk_x11_gl_context_get_xdisplay (GdkGLContext *glcontext)
{
  g_return_val_if_fail (GDK_IS_GL_CONTEXT (glcontext), NULL);

  return GDK_GL_CONTEXT_IMPL_X11 (glcontext)->xdisplay;
}

GLXContext
gdk_x11_gl_context_get_glxcontext (GdkGLContext *glcontext)
{
  g_return_val_if_fail (GDK_IS_GL_CONTEXT (glcontext), NULL);

  return GDK_GL_CONTEXT_IMPL_X11 (glcontext)->glxcontext;
}