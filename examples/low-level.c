#include <gtk/gtk.h>

#include <gdk/gdkgl.h>

#include <GL/gl.h>
#include <GL/glu.h>

static GdkGLConfig *glconfig = NULL;
static GdkGLWindow *glwindow = NULL;
static GdkGLContext *glcontext = NULL;

static const gint config_attributes[] = {
  GDK_GL_DOUBLEBUFFER,
  GDK_GL_RGBA,
  GDK_GL_RED_SIZE,        1,
  GDK_GL_GREEN_SIZE,      1,
  GDK_GL_BLUE_SIZE,       1,
  GDK_GL_DEPTH_SIZE,      12,
  GDK_GL_ATTRIB_LIST_NONE
};

static void
print_gl_config_attrib (GdkGLConfig *glconfig,
                        const gchar *attrib_str,
                        gint         attrib,
                        gboolean     is_boolean)
{
  gint value;

  g_print ("%s = ", attrib_str);
  if (gdk_gl_config_get_attrib (glconfig, attrib, &value))
    {
      if (is_boolean)
        g_print ("%s\n", value == TRUE ? "TRUE" : "FALSE");
      else
        g_print ("%d\n", value);
    }
  else
    g_print ("*** Cannot get %s attribute value\n", attrib_str);
}

static void
examine_gl_config_attrib (GdkGLConfig *glconfig)
{
  g_print ("\nOpenGL visual configurations :\n");

  print_gl_config_attrib (glconfig, "GDK_GL_USE_GL",           GDK_GL_USE_GL,           TRUE);
  print_gl_config_attrib (glconfig, "GDK_GL_BUFFER_SIZE",      GDK_GL_BUFFER_SIZE,      FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_LEVEL",            GDK_GL_LEVEL,            FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_RGBA",             GDK_GL_RGBA,             TRUE);
  print_gl_config_attrib (glconfig, "GDK_GL_DOUBLEBUFFER",     GDK_GL_DOUBLEBUFFER,     TRUE);
  print_gl_config_attrib (glconfig, "GDK_GL_STEREO",           GDK_GL_STEREO,           TRUE);
  print_gl_config_attrib (glconfig, "GDK_GL_AUX_BUFFERS",      GDK_GL_AUX_BUFFERS,      FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_RED_SIZE",         GDK_GL_RED_SIZE,         FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_GREEN_SIZE",       GDK_GL_GREEN_SIZE,       FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_BLUE_SIZE",        GDK_GL_BLUE_SIZE,        FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_ALPHA_SIZE",       GDK_GL_ALPHA_SIZE,       FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_DEPTH_SIZE",       GDK_GL_DEPTH_SIZE,       FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_STENCIL_SIZE",     GDK_GL_STENCIL_SIZE,     FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_ACCUM_RED_SIZE",   GDK_GL_ACCUM_RED_SIZE,   FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_ACCUM_GREEN_SIZE", GDK_GL_ACCUM_GREEN_SIZE, FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_ACCUM_BLUE_SIZE",  GDK_GL_ACCUM_BLUE_SIZE,  FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_ACCUM_ALPHA_SIZE", GDK_GL_ACCUM_ALPHA_SIZE, FALSE);

  g_print ("\n");
}

static void
init (GtkWidget *widget,
      gpointer   data)
{
  /*
   * Set OpenGL-capability to widget->window
   */

  gdk_window_set_gl_capability (widget->window, glconfig, NULL);

  /* Get GdkGLWindow */
  glwindow = gdk_window_get_gl_window (widget->window);

  /*
   * Create OpenGL rendering context.
   */

  if (glcontext == NULL)
    {
      glcontext = gdk_gl_context_new (GDK_GL_DRAWABLE (glwindow),
                                      glconfig,
                                      GDK_GL_RGBA_TYPE,
                                      NULL,
                                      TRUE);
      if (glcontext == NULL)
        {
          g_print ("Connot create the OpenGL rendering context\n");
          gtk_exit (1);
        }

      g_print ("The OpenGL rendering context is created\n");
    }

  /* OpenGL begin. */
  if (gdk_gl_drawable_make_current (GDK_GL_DRAWABLE (glwindow), glcontext))
    {
      GLUquadricObj *qobj;
      static GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};
      static GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};

      gdk_gl_drawable_wait_gdk (GDK_GL_DRAWABLE (glwindow));

      qobj = gluNewQuadric ();
      gluQuadricDrawStyle (qobj, GLU_FILL);
      glNewList (1, GL_COMPILE);
      gluSphere (qobj, 1.0, 20, 20);
      glEndList ();

      glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
      glLightfv (GL_LIGHT0, GL_POSITION, light_position);
      glEnable (GL_LIGHTING);
      glEnable (GL_LIGHT0);
      glEnable (GL_DEPTH_TEST);

      glClearColor (1.0, 1.0, 1.0, 1.0);
      glClearDepth (1.0);

      glViewport (0, 0,
                  widget->allocation.width, widget->allocation.height);

      glMatrixMode (GL_PROJECTION);
      glLoadIdentity ();
      gluPerspective (40.0, 1.0, 1.0, 10.0);

      glMatrixMode (GL_MODELVIEW);
      glLoadIdentity ();
      gluLookAt (0.0, 0.0, 3.0,
                 0.0, 0.0, 0.0,
                 0.0, 1.0, 0.0);
      glTranslatef (0.0, 0.0, -3.0);

      gdk_gl_drawable_wait_gl (GDK_GL_DRAWABLE (glwindow));
    }
  /* OpenGL end. */
}

static void
destroy (GtkWidget *widget,
         gpointer   data)
{
  if (widget->window != NULL)
    gdk_window_unset_gl_capability (widget->window);

  if (glconfig != NULL)
    g_object_unref (G_OBJECT (glconfig));

  if (glcontext != NULL)
    g_object_unref (G_OBJECT (glcontext));
}

static gboolean
reshape (GtkWidget         *widget,
         GdkEventConfigure *event,
         gpointer           data)
{
  /* gtk_drawing_area sends configure_event when it is realized. */
  if (glwindow == NULL)
    return TRUE;

  /* OpenGL begin. */
  if (gdk_gl_drawable_make_current (GDK_GL_DRAWABLE (glwindow), glcontext))
    {
      gdk_gl_drawable_wait_gdk (GDK_GL_DRAWABLE (glwindow));

      glViewport (0, 0,
                  widget->allocation.width, widget->allocation.height);

      gdk_gl_drawable_wait_gl (GDK_GL_DRAWABLE (glwindow));
    }
  /* OpenGL end. */

  return TRUE;
}

static gboolean
display (GtkWidget      *widget,
         GdkEventExpose *event,
         gpointer        data)
{
  /* OpenGL begin. */
  if (gdk_gl_drawable_make_current (GDK_GL_DRAWABLE (glwindow), glcontext))
    {
      gdk_gl_drawable_wait_gdk (GDK_GL_DRAWABLE (glwindow));

      glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glCallList (1);

      if (gdk_gl_config_is_double_buffer (glconfig))
        gdk_gl_drawable_swap_buffers (GDK_GL_DRAWABLE (glwindow));
      else
        glFlush ();

      gdk_gl_drawable_wait_gl (GDK_GL_DRAWABLE (glwindow));
    }
  /* OpenGL end. */

#if 0

  gdk_draw_arc (widget->window,
                widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
                TRUE,
                0.4*widget->allocation.width,
                0.4*widget->allocation.height,
                0.2*widget->allocation.width,
                0.2*widget->allocation.height,
                0, 64 * 360);

#endif

  return TRUE;
}

#if 0
static gboolean
idle (GtkWidget *widget)
{
  /* OpenGL begin. */
  if (gdk_gl_drawable_make_current (GDK_GL_DRAWABLE (glwindow), glcontext))
    {
      gdk_gl_drawable_wait_gdk (GDK_GL_DRAWABLE (glwindow));

      glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glCallList (1);

      if (gdk_gl_config_is_double_buffer (glconfig))
        gdk_gl_drawable_swap_buffers (GDK_GL_DRAWABLE (glwindow));
      else
        glFlush ();

      gdk_gl_drawable_wait_gl (GDK_GL_DRAWABLE (glwindow));
    }
  /* OpenGL end. */

  return TRUE;
}
#endif

static gboolean
destroy_gl_context (GtkWidget *widget)
{
  if (widget->window != NULL)
    gdk_window_unset_gl_capability (widget->window);

  if (glconfig != NULL)
    g_object_unref (G_OBJECT (glconfig));

  if (glcontext != NULL)
    g_object_unref (G_OBJECT (glcontext));

  return FALSE;
}

static gint
quit (GtkWidget *widget,
      GdkEvent  *event,
      gpointer   data)
{
  gtk_main_quit ();

  return FALSE;
}

int
main (int argc,
      char *argv[])
{
  gint major, minor;

  GtkWidget *window;
  GtkWidget *vbox;
  GtkWidget *drawing_area;
  GtkWidget *button;

  gtk_init (&argc, &argv);

  /*
   * OpenGL extension is supported?
   */

  if (!gdk_gl_query_extension ())
    {
      g_print ("\n*** OpenGL extension is not supported\n");
      gtk_exit (1);
    }

  gdk_gl_query_version (&major, &minor);
  g_print ("\nOpenGL extension is supported - version %d.%d\n",
           major, minor);

  /*
   * Configure OpenGL-capable visual.
   */

  /* Try double buffered visual */
  glconfig = gdk_gl_config_new (&config_attributes[0]);
  if (glconfig == NULL)
    {
      g_print ("*** Cannot find the OpenGL-capable visual with double buffering support.\n");
      g_print ("*** Trying single buffering visual.\n");

      /* Try single buffered visual */
      glconfig = gdk_gl_config_new (&config_attributes[1]);
      if (glconfig == NULL)
        {
          g_print ("*** Cannot find an OpenGL-capable visual\n");
          gtk_exit (1);
        }
    }

  examine_gl_config_attrib (glconfig);

  /*
   * Top-level window.
   */

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (window, "Simple");

  g_signal_connect (G_OBJECT (window), "delete_event",
                    G_CALLBACK (quit), NULL);

  vbox = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox);
  gtk_widget_show (vbox);

  /*
   * Drawing area for drawing OpenGL scene.
   */

  drawing_area = gtk_drawing_area_new ();
  gtk_widget_set_size_request (drawing_area, 200, 200);

  /* Set OpenGL-capable colormap. */
  gtk_widget_set_colormap (drawing_area,
                           gdk_gl_config_get_colormap (glconfig));

  /* Disable backing store feature of the widget. */
  gtk_widget_set_double_buffered (drawing_area, FALSE);

  gtk_box_pack_start (GTK_BOX (vbox), drawing_area, TRUE, TRUE, 0);

  gtk_widget_set_events (drawing_area,
                         GDK_EXPOSURE_MASK |
                         GDK_BUTTON_PRESS_MASK);

  g_signal_connect (G_OBJECT (drawing_area), "realize",
		    G_CALLBACK (init), NULL);
  g_signal_connect (G_OBJECT (drawing_area), "unrealize",
		    G_CALLBACK (destroy), NULL);
  g_signal_connect (G_OBJECT (drawing_area), "configure_event",
		    G_CALLBACK (reshape), NULL);
  g_signal_connect (G_OBJECT (drawing_area), "expose_event",
		    G_CALLBACK (display), NULL);

  gtk_widget_show (drawing_area);

  /*
   * Simple quit button.
   */

  button = gtk_button_new_with_label ("Quit");
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);

  g_signal_connect (G_OBJECT (button), "clicked",
                    G_CALLBACK (quit), NULL);

  gtk_widget_show (button);

  /*
   * Show window.
   */

  gtk_widget_show (window);

  /*
   * Main loop.
   */

  /* Destroy the GLX context explicitly when application is terminated. */
  gtk_quit_add (0, (GtkFunction) destroy_gl_context, drawing_area);

#if 0
  gtk_idle_add((GtkFunction) idle, drawing_area);
#endif

  gtk_main ();

  return 0;
}