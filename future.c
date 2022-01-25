#include <gtk/gtk.h>

#include "database.h"

void future_main(GtkBuilder* ui)
{
    GtkButton* button = GTK_BUTTON(gtk_builder_get_object(ui, "future_add"));
    g_signal_connect(
        G_OBJECT(button), "clicked", G_CALLBACK(gtk_main_quit), NULL);

    GtkLabel* label = GTK_LABEL(gtk_builder_get_object(ui, "future_list"));
    struct future_entry* entries = db_future_get_all();

    GString* str = g_string_new("");
    for (int i = 0; entries[i].name[0] != '\0'; i++) {
        g_string_append_printf(str, "%d. %s\n", i + 1, entries[i].name);
        g_string_append_printf(str, "     GROUP: %d\n", entries[i].future_group);
        g_string_append_printf(str, "     SPENT: %d\n", entries[i].price);
        g_string_append_printf(str, "     OCCASION: %s\n\n", entries[i].occasion);
    }
    gtk_label_set_text(label, str->str);
}
