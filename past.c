#include <gtk/gtk.h>

#include "database.h"

void past_main(GtkBuilder* ui)
{
    GtkButton* button = GTK_BUTTON(gtk_builder_get_object(ui, "past_add"));
    g_signal_connect(
        G_OBJECT(button), "clicked", G_CALLBACK(gtk_main_quit), NULL);

    GtkLabel* label = GTK_LABEL(gtk_builder_get_object(ui, "past_list"));
    struct past_entry* entries = db_past_get_all();

    GString* str = g_string_new("");
    for (int i = 0; entries[i].name[0] != '\0'; i++) {
        g_string_append_printf(str, "%d. %s\n", i + 1, entries[i].name);
        g_string_append_printf(str, "     GROUP: %d\n", entries[i].past_group);
        g_string_append_printf(str, "     SPENT: %d\n", entries[i].price);
        g_string_append_printf(
            str, "     PAYMENT TYPE: %d\n\n", entries[i].payment);
    }
    gtk_label_set_text(label, str->str);
}
