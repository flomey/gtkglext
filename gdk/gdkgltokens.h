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

#ifndef __GDK_GL_TOKENS_H__
#define __GDK_GL_TOKENS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * Success return value (same as 'Success' of X11)
 */
typedef enum
{
  GDK_GL_SUCCESS = 0
} GdkGLSuccess;

/*
 * Attribute list terminator (same as 'None' of X11)
 */
typedef enum
{
  GDK_GL_ATTRIB_LIST_NONE = 0
} GdkGLAttribListNone;

/*
 * Ripped from the OpenGL(R) Sample Implementation by SGI.
 */

/*
** License Applicability. Except to the extent portions of this file are
** made subject to an alternative license as permitted in the SGI Free
** Software License B, Version 1.1 (the "License"), the contents of this
** file are subject only to the provisions of the License. You may not use
** this file except in compliance with the License. You may obtain a copy
** of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
** Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
** 
** http://oss.sgi.com/projects/FreeB
** 
** Note that, as provided in the License, the Software is distributed on an
** "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
** DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
** CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
** PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
** 
** Original Code. The Original Code is: OpenGL Sample Implementation,
** Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
** Inc. The Original Code is Copyright (c) 1991-2000 Silicon Graphics, Inc.
** Copyright in any portions created by third parties is as indicated
** elsewhere herein. All Rights Reserved.
** 
** Additional Notice Provisions: The application programming interfaces
** established by SGI in conjunction with the Original Code are The
** OpenGL(R) Graphics System: A Specification (Version 1.2.1), released
** April 1, 1999; The OpenGL(R) Graphics System Utility Library (Version
** 1.3), released November 4, 1998; and OpenGL(R) Graphics with the X
** Window System(R) (Version 1.3), released October 19, 1998. This software
** was created using the OpenGL(R) version 1.2.1 Sample Implementation
** published by SGI, but has not been independently verified as being
** compliant with the OpenGL(R) version 1.2.1 Specification.
*/

/*
#define GLX_VERSION_1_1 1
#define GLX_VERSION_1_2 1
#define GLX_VERSION_1_3 1
*/

/*
 * Visual Config Attributes (glXGetConfig, glXGetFBConfigAttrib)
 */
typedef enum
{
  GDK_GL_USE_GL           = 1,  /* support GLX rendering */
  GDK_GL_BUFFER_SIZE      = 2,  /* depth of the color buffer */
  GDK_GL_LEVEL            = 3,  /* level in plane stacking */
  GDK_GL_RGBA             = 4,  /* true if RGBA mode */
  GDK_GL_DOUBLEBUFFER     = 5,  /* double buffering supported */
  GDK_GL_STEREO           = 6,  /* stereo buffering supported */
  GDK_GL_AUX_BUFFERS      = 7,  /* number of aux buffers */
  GDK_GL_RED_SIZE         = 8,  /* number of red component bits */
  GDK_GL_GREEN_SIZE       = 9,  /* number of green component bits */
  GDK_GL_BLUE_SIZE        = 10, /* number of blue component bits */
  GDK_GL_ALPHA_SIZE       = 11, /* number of alpha component bits */
  GDK_GL_DEPTH_SIZE       = 12, /* number of depth bits */
  GDK_GL_STENCIL_SIZE     = 13, /* number of stencil bits */
  GDK_GL_ACCUM_RED_SIZE   = 14, /* number of red accum bits */
  GDK_GL_ACCUM_GREEN_SIZE = 15, /* number of green accum bits */
  GDK_GL_ACCUM_BLUE_SIZE  = 16, /* number of blue accum bits */
  GDK_GL_ACCUM_ALPHA_SIZE = 17  /* number of alpha accum bits */
} GdkGLVisualConfigAttribute;

/*
 * FBConfig-specific attributes
 */
typedef enum
{
  GDK_GL_X_VISUAL_TYPE           = 0x22,
  GDK_GL_CONFIG_CAVEAT           = 0x20, /* Like visual_info VISUAL_CAVEAT_EXT */
  GDK_GL_TRANSPARENT_TYPE        = 0x23,
  GDK_GL_TRANSPARENT_INDEX_VALUE = 0x24,
  GDK_GL_TRANSPARENT_RED_VALUE   = 0x25,
  GDK_GL_TRANSPARENT_GREEN_VALUE = 0x26,
  GDK_GL_TRANSPARENT_BLUE_VALUE  = 0x27,
  GDK_GL_TRANSPARENT_ALPHA_VALUE = 0x28,
  GDK_GL_DRAWABLE_TYPE           = 0x8010,
  GDK_GL_RENDER_TYPE             = 0x8011,
  GDK_GL_X_RENDERABLE            = 0x8012,
  GDK_GL_FBCONFIG_ID             = 0x8013,
  GDK_GL_MAX_PBUFFER_WIDTH       = 0x8016,
  GDK_GL_MAX_PBUFFER_HEIGHT      = 0x8017,
  GDK_GL_MAX_PBUFFER_PIXELS      = 0x8018,
  GDK_GL_VISUAL_ID               = 0x800B
} GdkGLFBConfigAttribute;

/*
 * Error return values from glXGetConfig.  Success is indicated by
 * a value of 0.
 */
typedef enum
{
  GDK_GL_BAD_SCREEN    = 1, /* screen # is bad */
  GDK_GL_BAD_ATTRIBUTE = 2, /* attribute to get is bad */
  GDK_GL_NO_EXTENSION  = 3, /* no glx extension on server */
  GDK_GL_BAD_VISUAL    = 4, /* visual # not known by GLX */
  GDK_GL_BAD_CONTEXT   = 5, /* returned only by import_context EXT? */
  GDK_GL_BAD_VALUE     = 6, /* returned only by glXSwapIntervalSGI? */
  GDK_GL_BAD_ENUM      = 7  /* unused? */
} GdkGLConfigError;

/* FBConfig attribute values */

/*
 * Generic "don't care" value for glX ChooseFBConfig attributes (except
 * GLX_LEVEL)
 */
typedef enum
{
  GDK_GL_DONT_CARE              = 0xFFFFFFFF,

  /* GLX_RENDER_TYPE bits */
  GDK_GL_RGBA_BIT               = 0x00000001,
  GDK_GL_COLOR_INDEX_BIT        = 0x00000002,

  /* GLX_DRAWABLE_TYPE bits */
  GDK_GL_WINDOW_BIT             = 0x00000001,
  GDK_GL_PIXMAP_BIT             = 0x00000002,
  GDK_GL_PBUFFER_BIT            = 0x00000004,

  /* GLX_CONFIG_CAVEAT attribute values */
  GDK_GL_NONE                   = 0x8000,
  GDK_GL_SLOW_CONFIG            = 0x8001,
  GDK_GL_NON_CONFORMANT_CONFIG  = 0x800D,

  /* GLX_X_VISUAL_TYPE attribute values */
  GDK_GL_TRUE_COLOR             = 0x8002,
  GDK_GL_DIRECT_COLOR           = 0x8003,
  GDK_GL_PSEUDO_COLOR           = 0x8004,
  GDK_GL_STATIC_COLOR           = 0x8005,
  GDK_GL_GRAY_SCALE             = 0x8006,
  GDK_GL_STATIC_GRAY            = 0x8007,

  /* GLX_TRANSPARENT_TYPE attribute values */
  /* GDK_GL_NONE                   = 0x8000, */
  GDK_GL_TRANSPARENT_RGB        = 0x8008,
  GDK_GL_TRANSPARENT_INDEX      = 0x8009,

  /* glXCreateGLXPbuffer attributes */
  GDK_GL_PRESERVED_CONTENTS     = 0x801B,
  GDK_GL_LARGEST_PBUFFER        = 0x801C,
  GDK_GL_PBUFFER_HEIGHT         = 0x8040, /* New for GLX 1.3 */
  GDK_GL_PBUFFER_WIDTH          = 0x8041, /* New for GLX 1.3 */

  /* glXQueryGLXPBuffer attributes */
  GDK_GL_WIDTH                  = 0x801D,
  GDK_GL_HEIGHT                 = 0x801E,
  GDK_GL_EVENT_MASK             = 0x801F,

  /* glXCreateNewContext render_type attribute values */
  GDK_GL_RGBA_TYPE              = 0x8014,
  GDK_GL_COLOR_INDEX_TYPE       = 0x8015,

  /* glXQueryContext attributes */
  /* GDK_GL_FBCONFIG_ID            = 0x8013, */
  /* GDK_GL_RENDER_TYPE            = 0x8011, */
  GDK_GL_SCREEN                 = 0x800C,

  /* glXSelectEvent event mask bits */
  GDK_GL_PBUFFER_CLOBBER_MASK   = 0x08000000,

  /* GLXPbufferClobberEvent event_type values */
  GDK_GL_DAMAGED                = 0x8020,
  GDK_GL_SAVED                  = 0x8021,

  /* GLXPbufferClobberEvent draw_type values */
  GDK_GL_WINDOW                 = 0x8022,
  GDK_GL_PBUFFER                = 0x8023,

  /* GLXPbufferClobberEvent buffer_mask bits */
  GDK_GL_FRONT_LEFT_BUFFER_BIT  = 0x00000001,
  GDK_GL_FRONT_RIGHT_BUFFER_BIT = 0x00000002,
  GDK_GL_BACK_LEFT_BUFFER_BIT   = 0x00000004,
  GDK_GL_BACK_RIGHT_BUFFER_BIT  = 0x00000008,
  GDK_GL_AUX_BUFFERS_BIT        = 0x00000010,
  GDK_GL_DEPTH_BUFFER_BIT       = 0x00000020,
  GDK_GL_STENCIL_BUFFER_BIT     = 0x00000040,
  GDK_GL_ACCUM_BUFFER_BIT       = 0x00000080
} GdkGLGenericValue;

/*
 * Extension return values from glXGetConfig.  These are also
 * accepted as parameter values for glXChooseVisual.
 */
typedef enum
{
  GDK_GL_X_VISUAL_TYPE_EXT           = 0x22, /* visual_info extension type */
  GDK_GL_TRANSPARENT_TYPE_EXT        = 0x23, /* visual_info extension */
  GDK_GL_TRANSPARENT_INDEX_VALUE_EXT = 0x24, /* visual_info extension */
  GDK_GL_TRANSPARENT_RED_VALUE_EXT   = 0x25, /* visual_info extension */
  GDK_GL_TRANSPARENT_GREEN_VALUE_EXT = 0x26, /* visual_info extension */
  GDK_GL_TRANSPARENT_BLUE_VALUE_EXT  = 0x27, /* visual_info extension */
  GDK_GL_TRANSPARENT_ALPHA_VALUE_EXT = 0x28, /* visual_info extension */

  /* Property values for visual_type */
  GDK_GL_TRUE_COLOR_EXT              = 0x8002,
  GDK_GL_DIRECT_COLOR_EXT            = 0x8003,
  GDK_GL_PSEUDO_COLOR_EXT            = 0x8004,
  GDK_GL_STATIC_COLOR_EXT            = 0x8005,
  GDK_GL_GRAY_SCALE_EXT              = 0x8006,
  GDK_GL_STATIC_GRAY_EXT             = 0x8007,

  /* Property values for transparent pixel */
  GDK_GL_NONE_EXT                    = 0x8000,
  GDK_GL_TRANSPARENT_RGB_EXT         = 0x8008,
  GDK_GL_TRANSPARENT_INDEX_EXT       = 0x8009,

  /* Property values for visual_rating */
  GDK_GL_VISUAL_CAVEAT_EXT           = 0x20,   /* visual_rating extension type */
  GDK_GL_SLOW_VISUAL_EXT             = 0x8001,
  GDK_GL_NON_CONFORMANT_VISUAL_EXT   = 0x800D
} GdkGLExtensionValue;

/*
 * Names for attributes to glXGetClientString.
 */
typedef enum
{
  GDK_GL_VENDOR     = 0x1,
  GDK_GL_VERSION    = 0x2,
  GDK_GL_EXTENSIONS = 0x3
} GdkGLClientStringAttribute;

/*
 * Names for attributes to glXQueryContextInfoEXT.
 */
typedef enum
{
  GDK_GL_SHARE_CONTEXT_EXT = 0x800A, /* id of share context */
  GDK_GL_VISUAL_ID_EXT     = 0x800B, /* id of context's visual */
  GDK_GL_SCREEN_EXT        = 0x800C  /* screen number */
} GdkGLContextInfoExtensionAttribute;

/* GLX Extension Strings */
/*
#define GLX_EXT_import_context	1
#define GLX_EXT_visual_info	1
#define GLX_EXT_visual_rating	1
*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GDK_GL_TOKENS_H__ */