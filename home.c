#include <gtk/gtk.h>

#include "database.h"

void home_main(GtkBuilder* ui)
{
    GtkLabel* label = GTK_LABEL(gtk_builder_get_object(ui, "home_past"));
    struct past_entry* entries = db_past_get_all();

    GString* str = g_string_new("");
    g_string_append_printf(str, "Resent past spendings\n\n");
    for (int i = 0; entries[i].name[0] != '\0'; i++) {
        g_string_append_printf(str, "%d. [%s]", i + 1, spending_group_to_string(entries[i].past_group));
        g_string_append_printf(str, " %s, ", entries[i].name);
        g_string_append_printf(str, "%d\n", entries[i].price);
    }
    gtk_label_set_text(label, str->str);

    GtkLabel* label2 = GTK_LABEL(gtk_builder_get_object(ui, "home_future"));
    struct future_entry* entries2 = db_future_get_all();

    GString* str2 = g_string_new("");
    g_string_append_printf(str2, "Incoming future spendings\n\n");
    for (int i = 0; entries2[i].name[0] != '\0'; i++) {
        g_string_append_printf(str2, "%d. [%s]", i + 1, entries2[i].occasion);
        g_string_append_printf(str2, " %s, ", entries2[i].name);
        g_string_append_printf(str2, "%d\n", entries2[i].price);
    }
    gtk_label_set_text(label2, str2->str);
}