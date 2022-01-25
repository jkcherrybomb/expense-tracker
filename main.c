#include <gtk/gtk.h>

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);

    GtkBuilder *ui = gtk_builder_new_from_file("main.glade");

    GtkWindow *window = GTK_WINDOW(gtk_builder_get_object(ui, "window"));
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    GtkButton *button = GTK_BUTTON(gtk_builder_get_object(ui, "button"));
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(GTK_WIDGET(window));
    
    gtk_main();
}