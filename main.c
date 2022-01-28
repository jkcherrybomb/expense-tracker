#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>

#include "database.h"
#include "future.h"
#include "home.h"
#include "past.h"
#include "statistics.h"

bool quit = false;

void quit_program()
{
    quit = true;
    gtk_main_quit();
}

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);
    GtkBuilder* ui = gtk_builder_new_from_file("main.glade");
    GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(ui, "window"));
    g_signal_connect(
        G_OBJECT(window), "destroy", G_CALLBACK(quit_program), NULL);

    db_create_if_missing();
    home_main(ui);
    past_main(ui);
    future_main(ui);
    statistics_main(ui);

    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();
    g_object_unref(ui);

    if (!quit) {
        char* const args[] = { "/proc/self/exe", 0 };
        execv(args[0], args);
    }
}