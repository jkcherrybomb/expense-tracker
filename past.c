#include <gtk/gtk.h>
#include "db_past.h"

void past_main(GtkBuilder* ui) {
    GtkButton *button = GTK_BUTTON(gtk_builder_get_object(ui, "past_add"));
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(gtk_main_quit), NULL);

    GtkLabel* label = GTK_LABEL(gtk_builder_get_object(ui, "past_list"));
    struct past_entry* entries = db_past_get_all();

    GString *str = g_string_new("");
    for (int i = 0; entries[i].name != NULL; i++) {
        g_string_append_printf(str, "%d. %s (%d)\n", i + 1, entries[i].name, entries[i].price);
    }
    gtk_label_set_text(label, str->str);
}
