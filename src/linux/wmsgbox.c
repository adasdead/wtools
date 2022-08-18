#include "wtools/wmsgbox.h"

#include <gtk/gtk.h>

struct w_prompt_data
{
    w_astr_2_t buttons;
    char text[W_MSGBOX_TEXT_SIZE];
    char title[W_MSGBOX_TITLE_SIZE];
    char def[W_MSGBOX_INPUT_SIZE];

    char output[W_MSGBOX_INPUT_SIZE];

    GtkWidget *window, *fixed;
    GtkWidget *button1, *button2;
    GtkWidget *entry, *label;
};

static void w_on_button1(GtkWidget *widget, gpointer _data)
{
    struct w_prompt_data *data = (struct w_prompt_data*) _data;
    w_castr_t text = gtk_entry_get_text(GTK_ENTRY(data->entry));
    strncpy(data->output, text, W_MSGBOX_INPUT_SIZE);
    gtk_widget_destroy(data->window);
}

static void w_on_button2(GtkWidget *widget, gpointer _data)
{
    struct w_prompt_data *data = (struct w_prompt_data*) _data;
    gtk_widget_destroy(data->window);
}

static void w_prompt_activate(GtkApplication *application,
                              gpointer user_data)
{
    struct w_prompt_data *data = (struct w_prompt_data*) user_data;

    data->fixed = gtk_fixed_new();

    data->window = gtk_application_window_new(application);
    gtk_window_set_title(GTK_WINDOW(data->window), data->title);
    gtk_window_set_default_size(GTK_WINDOW(data->window), 355, 150);
    gtk_container_add(GTK_CONTAINER(data->window), data->fixed);
    gtk_window_set_resizable(data->window, 0);

    data->button1 = gtk_button_new_with_label(data->buttons[0]);
    gtk_widget_set_size_request(data->button1, 75, 25);
    gtk_fixed_put(GTK_FIXED(data->fixed), data->button1, 270, 10);
    g_signal_connect(data->button1, "clicked", G_CALLBACK(w_on_button1),
                     data);

    data->button2 = gtk_button_new_with_label(data->buttons[1]);
    gtk_widget_set_size_request(data->button2, 75, 25);
    gtk_fixed_put(GTK_FIXED(data->fixed), data->button2, 270, 50);
    g_signal_connect(data->button2, "clicked", G_CALLBACK(w_on_button2),
                     data);

    data->entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(data->entry), data->def);
    gtk_widget_set_size_request(data->entry, 335, 20);
    gtk_fixed_put(GTK_FIXED(data->fixed), data->entry, 10, 100);
    gtk_entry_set_max_length(GTK_ENTRY(data->entry),
                             W_MSGBOX_INPUT_SIZE);

    data->label = gtk_label_new(data->text);
    gtk_label_set_xalign(GTK_LABEL(data->label), 0.0);
    gtk_label_set_line_wrap(GTK_LABEL(data->label), 1);
    gtk_label_set_line_wrap_mode(GTK_LABEL(data->label), PANGO_WRAP_CHAR);
    gtk_widget_set_size_request(data->label, 250, 20);
    gtk_fixed_put(GTK_FIXED(data->fixed), data->label, 10, 10);

    gtk_widget_show_all(data->fixed);
    
    gtk_window_present(GTK_WINDOW(data->window));
}

static w_clicked_t w_gtk_msgbox(w_castr_t text, w_castr_t title,
                                w_castr_t btn1, w_castr_t btn2)
{
    gtk_init(NULL, NULL);

    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL, 0, GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_NONE, text);

    gtk_dialog_add_button(GTK_DIALOG(dialog), btn1, 0);

    if (btn2)
        gtk_dialog_add_button(GTK_DIALOG(dialog), btn2, 1);

    gtk_window_set_title(GTK_WINDOW(dialog), title);

    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    
    gtk_widget_destroy(GTK_WIDGET(dialog));

    return result;
}

void w_msgbox_alert(w_castr_t text, w_castr_t title,
                    w_castr_t button)
{
    w_gtk_msgbox(text, title, button, NULL);
}

w_clicked_t w_msgbox_confirm(w_castr_t text, w_castr_t title,
                             w_castr_2_t btns)
{
    return w_gtk_msgbox(text, title, btns[0], btns[1]);
}

void w_msgbox_prompt(w_castr_t text, w_castr_t title,
                     w_astr_t out, size_t size)
{
    w_castr_2_t buttons = {"OK", "Cancel"};
    w_msgbox_prompt_ex(text, title, "", buttons, out, size);
}

void w_msgbox_prompt_ex(w_castr_t text, w_castr_t title,
                        w_castr_t def, w_castr_2_t btns,
                        w_astr_t out, size_t size)
{
    GtkApplication *application;
    application = gtk_application_new(W_APPLICATION_ID,
                                      G_APPLICATION_FLAGS_NONE);

    struct w_prompt_data data = {0};
    memcpy(data.buttons, btns, sizeof(data.buttons));
    strncpy(data.title, title, sizeof(data.title));
    strncpy(data.text, text, sizeof(data.text));
    strncpy(data.def, def, sizeof(data.def));
    
    g_signal_connect(application, "activate",
                     G_CALLBACK(w_prompt_activate), &data);
    
    g_application_run(G_APPLICATION(application), 0, NULL);
    
    g_object_unref(application);

    strncpy(out, data.output, size);
}