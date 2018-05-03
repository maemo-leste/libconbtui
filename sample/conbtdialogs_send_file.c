/**
  Bluetooth UI Library for Maemo

  This sample demonstrates the use of conbtdialogs API and especially
  send_file function. Compile the program with conbtdialogs and dbus:

  gcc -Wall `pkg-config --libs --cflags dbus-glib-1 conbtdialogs` -o send_file conbtdialogs_send_file.c

  Run with list of URLS:

  ./send_file file:///home/user/MyDocs/.sounds/Everyday.mp3

  Copyright (C) 2006 Nokia. All rights reserved.

  @author Aapo Makela <aapo.makela@nokia.com>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License version 2.1 as
  published by the Free Software Foundation.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
  General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this library; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#define DBUS_API_SUBJECT_TO_CHANGE

#include <glib.h>
#include <conbtdialogs-dbus.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib.h>


DBusGConnection *connection = NULL;
GMainLoop *mainloop = NULL;


static gboolean initialize(void)
{
    GError *error = NULL;

    g_type_init ();

    /* Create main loop */
    mainloop = g_main_loop_new(NULL, TRUE);
    if ( mainloop == NULL ) return FALSE;

    /* Create DBUS connection */
    connection = dbus_g_bus_get(DBUS_BUS_SYSTEM, &error);

    if (connection == NULL )
    {
        g_print ("Error: %s\n", error->message);
        g_clear_error (&error);
        return FALSE;
    }

    return TRUE;
}


static gboolean uninitialize(void)
{
    /* Quit main loop and unref it */
    if (mainloop != NULL)
    {
        g_main_loop_quit(mainloop);
        g_main_loop_unref(mainloop);
    }

    return TRUE;
}


static DBusHandlerResult file_sent_signal ( DBusConnection *connection,
                                            DBusMessage *message,
                                            void *data )
{
    gboolean success = FALSE;

    /* check signal */
    if (!dbus_message_is_signal(message,
                                CONBTDIALOGS_DBUS_INTERFACE,
                                CONBTDIALOGS_SEND_FILE_SIG))
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

    /* get args */
    if ( !dbus_message_get_args ( message, NULL,
                                  DBUS_TYPE_BOOLEAN, &success,
                                  DBUS_TYPE_INVALID ) )
      return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

    /* print if file sending was success or failure */
    g_print ( "File sending was a " );

    if (success) g_print("success\n"); else g_print("failure\n");
    dbus_connection_close(connection);
    uninitialize();

    return DBUS_HANDLER_RESULT_HANDLED;
}


gint main(gint argc, gchar **argv)
{
    GError *error = NULL;
    gchar **files = NULL;
    gint idx = 0;
    DBusGProxy *proxy;
    DBusConnection *sys_conn;
    gchar *filter_string = NULL;

    if (argc < 2) return 1;

    if (initialize() == FALSE) {
        uninitialize();
        return 1;
    }

    /* Copy urls to GLib compatible char array */
    files = g_new0(gchar*, argc);

    for (idx = 1; idx < argc; idx++)
        files[idx-1] = g_strdup(argv[idx]);

    files[argc-1] = NULL;

    /* Open connection for btdialogs service */
    proxy = dbus_g_proxy_new_for_name(connection,
                                      CONBTDIALOGS_DBUS_SERVICE,
                                      CONBTDIALOGS_DBUS_PATH,
                                      CONBTDIALOGS_DBUS_INTERFACE);

    /* Send send file request to btdialogs service */
    if (!dbus_g_proxy_call(proxy, CONBTDIALOGS_SEND_FILE_REQ,
                           &error,
                           G_TYPE_STRV, files, G_TYPE_INVALID,
                           G_TYPE_INVALID))
    {
        g_print("Error: %s\n", error->message);
        g_clear_error(&error);
        g_strfreev (files);
        g_object_unref(G_OBJECT(proxy));
        uninitialize();
        return 1;
    }
    g_strfreev (files);
    files = NULL;

    g_object_unref(G_OBJECT(proxy));

    /* Now wait for file sent signal, use low level bindings as glib
       bindings require signal marshaller registered */
    sys_conn = dbus_bus_get(DBUS_BUS_SYSTEM, NULL);
    g_assert(dbus_connection_add_filter(sys_conn,
                                        file_sent_signal,
                                        NULL,
                                        NULL ));
    filter_string =
       g_strdup_printf ("type='signal',interface='%s'", CONBTDIALOGS_DBUS_INTERFACE);

    dbus_bus_add_match(sys_conn, filter_string, NULL);
    dbus_connection_unref(sys_conn);

    /* Run mainloop */
    g_main_loop_run(mainloop);

    return 0;
}
