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

#include <gdk/gdkdrawable.h>
#include "gdkglprivate.h"
#include "gdkgldrawable.h"

GType
gdk_gl_drawable_get_type (void)
{
  static GType type = 0;

  if (!type)
    {
      static const GTypeInfo type_info = {
        sizeof (GdkGLDrawableClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
                                     "GdkGLDrawable",
                                     &type_info, 0);
    }

  return type;
}

/**
 * gdk_gl_drawable_make_current:
 * @gldrawable: a #GdkGLDrawable.
 * @glcontext: a #GdkGLContext.
 *
 * Attach a OpenGL rendering context to a @gldrawable.
 *
 * Return value: TRUE if it is successful, FALSE otherwise.
 **/
gboolean
gdk_gl_drawable_make_current (GdkGLDrawable *gldrawable,
                              GdkGLContext  *glcontext)
{
  g_return_val_if_fail (GDK_IS_GL_DRAWABLE (gldrawable), FALSE);

  return GDK_GL_DRAWABLE_GET_CLASS (gldrawable)->make_context_current (gldrawable,
                                                                       gldrawable,
                                                                       glcontext);
}

/**
 * gdk_gl_drawable_is_double_buffered:
 * @gldrawable: a #GdkGLDrawable.
 *
 * Returns whether the #GdkGLDrawable supports the double-buffered visual.
 *
 * Return value: TRUE if the double-buffered visual is supported, FALSE otherwise.
 **/
gboolean
gdk_gl_drawable_is_double_buffered (GdkGLDrawable *gldrawable)
{
  g_return_val_if_fail (GDK_IS_GL_DRAWABLE (gldrawable), FALSE);

  return GDK_GL_DRAWABLE_GET_CLASS (gldrawable)->is_double_buffered (gldrawable);
}

/**
 * gdk_gl_drawable_swap_buffers:
 * @gldrawable: a #GdkGLDrawable.
 *
 * Exchange front and back buffers.
 *
 **/
void
gdk_gl_drawable_swap_buffers (GdkGLDrawable *gldrawable)
{
  g_return_if_fail (GDK_IS_GL_DRAWABLE (gldrawable));

  GDK_GL_DRAWABLE_GET_CLASS (gldrawable)->swap_buffers (gldrawable);
}

/**
 * gdk_gl_drawable_wait_gl:
 * @gldrawable: a #GdkGLDrawable.
 *
 * Complete GL execution prior to subsequent GDK drawing calls.
 *
 **/
void
gdk_gl_drawable_wait_gl (GdkGLDrawable *gldrawable)
{
  g_return_if_fail (GDK_IS_GL_DRAWABLE (gldrawable));

  GDK_GL_DRAWABLE_GET_CLASS (gldrawable)->wait_gl (gldrawable);
}

/**
 * gdk_gl_drawable_wait_gdk:
 * @gldrawable: a #GdkGLDrawable.
 *
 * Complete GDK drawing execution prior to subsequent GL calls.
 *
 **/
void
gdk_gl_drawable_wait_gdk (GdkGLDrawable *gldrawable)
{
  g_return_if_fail (GDK_IS_GL_DRAWABLE (gldrawable));

  GDK_GL_DRAWABLE_GET_CLASS (gldrawable)->wait_gdk (gldrawable);
}

/**
 * gdk_gl_drawable_get_gl_config:
 * @gldrawable: a #GdkGLDrawable.
 *
 * Get #GdkGLConfig with which the @gldrawable is configured.
 *
 * Return value: the #GdkGLConfig.
 **/
GdkGLConfig *
gdk_gl_drawable_get_gl_config (GdkGLDrawable *gldrawable)
{
  g_return_val_if_fail (GDK_IS_GL_DRAWABLE (gldrawable), NULL);

  return GDK_GL_DRAWABLE_GET_CLASS (gldrawable)->get_gl_config (gldrawable);
}

/**
 * gdk_gl_drawable_get_drawable:
 * @gldrawable: a #GdkGLDrawable.
 *
 * Get #GdkDrawable associated with the @gldrawable.
 *
 * Return value: the #GdkDrawable.
 **/
GdkDrawable *
gdk_gl_drawable_get_drawable (GdkGLDrawable *gldrawable)
{
  g_return_val_if_fail (GDK_IS_GL_DRAWABLE (gldrawable), NULL);

  return GDK_GL_DRAWABLE_GET_CLASS (gldrawable)->get_drawable (gldrawable);
}

/**
 * gdk_gl_drawable_get_size:
 * @gldrawable: a #GdkGLDrawable
 * @width: location to store GL drawable's width, or %NULL
 * @height: location to store GL drawable's height, or %NULL
 *
 * Fills *@width and *@height with the size of @gldrawable.
 * @width or @height can be %NULL if you only want the other one.
 * 
 **/
void
gdk_gl_drawable_get_size (GdkGLDrawable *gldrawable,
                          gint          *width,
                          gint          *height)
{
  gdk_drawable_get_size (gdk_gl_drawable_get_drawable (gldrawable),
                         width, height);
}

/**
 * gdk_gl_drawable_get_colormap:
 * @gldrawable: a #GdkGLDrawable
 * 
 * Gets the colormap for @gldrawable, if one is set; returns
 * %NULL otherwise.
 * 
 * Return value: the colormap, or %NULL
 **/
GdkColormap *
gdk_gl_drawable_get_colormap (GdkGLDrawable *gldrawable)
{
  return gdk_drawable_get_colormap (gdk_gl_drawable_get_drawable (gldrawable));
}

/**
 * gdk_gl_drawable_get_visual:
 * @gldrawable: a #GdkGLDrawable
 * 
 * Gets the #GdkVisual describing the pixel format of @gldrawable.
 * 
 * Return value: a #GdkVisual
 **/
GdkVisual *
gdk_gl_drawable_get_visual (GdkGLDrawable *gldrawable)
{
  return gdk_drawable_get_visual (gdk_gl_drawable_get_drawable (gldrawable));
}

/**
 * gdk_gl_drawable_get_depth:
 * @gldrawable: a #GdkGLDrawable
 * 
 * Obtains the bit depth of the GL drawable, that is, the number of bits
 * that make up a pixel in the GL drawable's visual. Examples are 8 bits
 * per pixel, 24 bits per pixel, etc.
 * 
 * Return value: number of bits per pixel
 **/
gint
gdk_gl_drawable_get_depth (GdkGLDrawable *gldrawable)
{
  return gdk_drawable_get_depth (gdk_gl_drawable_get_drawable (gldrawable));
}

