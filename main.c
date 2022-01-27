#include <gtk/gtk.h>

#include "database.h"
#include "future.h"
#include "home.h"
#include "past.h"

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);
    GtkBuilder* ui = gtk_builder_new_from_file("main.glade");
    GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(ui, "window"));
    g_signal_connect(
        G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    home_main(ui);
    past_main(ui);
    future_main(ui);

    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();
    g_object_unref(ui);
}