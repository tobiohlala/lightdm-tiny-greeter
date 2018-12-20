/**
 * lightdm-tiny-greeter.c
 *
 * Copyright (c) 2018, Tobias Heilig
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the authors may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **/


#include <stdlib.h>
#include <gtk/gtk.h>
#include <lightdm.h>

#include "config.h"


static LightDMGreeter *greeter;


/* GTK components */
static GtkWidget *login_window;
static GtkLabel  *prompt_label;
static GtkEntry  *prompt_entry;
static GtkLabel  *message_label;


/* GtkEntry activate callback */
static void
login_cb ()
{

    gtk_label_set_text (message_label, "");

    if (lightdm_greeter_get_is_authenticated (greeter)) {
        // authentication completed - start session
        lightdm_greeter_start_session_sync (greeter, session, NULL);
    } else if (lightdm_greeter_get_in_authentication (greeter)) {
        // authentication in progress - send password
        lightdm_greeter_respond (greeter, gtk_entry_get_text (prompt_entry), NULL);
    } else {
        // authentication request - send username
        lightdm_greeter_authenticate (greeter, gtk_entry_get_text (prompt_entry), NULL);
    }

}


/* LightDM show-message callback */
static void
show_message_cb (LightDMGreeter *ldm, const gchar *text, LightDMPromptType type)
{

    gtk_label_set_text (message_label, text);

}


/* LightDM show-prompt callback */
static void
show_prompt_cb (LightDMGreeter *ldm, const gchar *text, LightDMPromptType type)
{

    gtk_label_set_text (prompt_label, type == LIGHTDM_PROMPT_TYPE_SECRET ? pass_text : user_text);
    gtk_entry_set_text (prompt_entry, "");
    gtk_entry_set_visibility (prompt_entry, type == LIGHTDM_PROMPT_TYPE_SECRET ? 0 : 1);

}


/* LightDM authentication-complete callback */
static void
authentication_complete_cb (LightDMGreeter *ldm)
{

    if (!lightdm_greeter_get_is_authenticated (ldm)) {
        gtk_label_set_text (message_label, "Authentication Failure.");

    } else if (!lightdm_greeter_start_session_sync (ldm, session, NULL)) {
        gtk_label_set_text (message_label, "Failed to start session.");

    }

    lightdm_greeter_authenticate (ldm, NULL, NULL);

}


int
main (int argc, char **argv)
{

    GtkCssProvider  *provider;
    GtkBuilder      *builder;
    GdkScreen       *screen;
    GdkDisplay      *display;
    GdkMonitor      *monitor;
    GdkRectangle     geometry;
    GMainLoop       *main_loop;


    gtk_init (&argc, &argv);


    provider = gtk_css_provider_new ();

    // load style sheet
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (
            screen,
            GTK_STYLE_PROVIDER (provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_data (provider, style, -1, NULL);


    builder = gtk_builder_new ();

    // load user interface
    gtk_builder_add_from_string (builder, ui, -1, NULL);

    // get components
    login_window  = GTK_WIDGET (gtk_builder_get_object (builder, "login_window"));
    prompt_label  = GTK_LABEL  (gtk_builder_get_object (builder, "prompt_label"));
    prompt_entry  = GTK_ENTRY  (gtk_builder_get_object (builder, "prompt_entry"));
    message_label = GTK_LABEL  (gtk_builder_get_object (builder, "message_label"));

    // connect gtk signals
    g_signal_connect (prompt_entry, "activate", G_CALLBACK (login_cb), NULL);

    // show window
    monitor = gdk_display_get_primary_monitor (display);
    gdk_monitor_get_geometry (monitor, &geometry);
    gtk_window_set_default_size (GTK_WINDOW (login_window), geometry.width, geometry.height);

    gtk_widget_show (login_window);
    gtk_entry_grab_focus_without_selecting (prompt_entry);


    greeter = lightdm_greeter_new ();

    // connect lightdm signals
    g_signal_connect (greeter, "show-prompt", G_CALLBACK (show_prompt_cb), NULL);
    g_signal_connect (greeter, "show-message", G_CALLBACK (show_message_cb), NULL);
    g_signal_connect (greeter, "authentication-complete", G_CALLBACK (authentication_complete_cb), NULL);

    // connect to lightdm daemon
    if (!lightdm_greeter_connect_to_daemon_sync (greeter, NULL))
        return EXIT_FAILURE;

    // start authentication
    lightdm_greeter_authenticate (greeter, NULL, NULL);


    main_loop = g_main_loop_new (NULL, 0);

    // start main loop
    g_main_loop_run (main_loop);


    return EXIT_SUCCESS;

}

