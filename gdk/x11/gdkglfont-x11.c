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

#include "gdkglx.h"
#include "gdkglfont.h"

/**
 * gdk_gl_font_use_gdk_font:
 * @font: a #GdkFont.
 * @first: the index of the first glyph to be taken.
 * @count: the number of glyphs to be taken.
 * @list_base: the index of the first display list to be generated.
 *
 * Create bitmap display lists from a #GdkFont.
 *
 **/
void
gdk_gl_font_use_gdk_font (GdkFont *font,
                          gint     first,
                          gint     count,
                          gint     list_base)
{
  g_return_if_fail (font != NULL);

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_font_use_gdk_font ()"));

  glXUseXFont (gdk_font_id (font), first, count, list_base);
}