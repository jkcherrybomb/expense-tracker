#include <gtk/gtk.h>

#include "database.h"

void future_new()
{
    GtkBuilder* ui = gtk_builder_new_from_file("future_new.glade");

    GtkListStore* groups = GTK_LIST_STORE(gtk_builder_get_object(ui, "fentry_group"));
    for (enum spending_group i = 0; i < SPENDING_GROUP_LENGTH; i++) {
        GtkTreeIter iter;
        gtk_list_store_append(groups, &iter);
        gtk_list_store_set(groups, &iter,
            0, i,
            1, spending_group_to_string(i),
            -1);
    }

    GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(ui, "fentry_window"));
    gtk_widget_show_all(GTK_WIDGET(window));
}

void future_main(GtkBuilder* ui)
{
    GtkButton* button = GTK_BUTTON(gtk_builder_get_object(ui, "future_add"));
    g_signal_connect(
        G_OBJECT(button), "clicked", G_CALLBACK(future_new), NULL);

    GtkLabel* label = GTK_LABEL(gtk_builder_get_object(ui, "future_list"));
    struct future_entry* entries = db_future_get_all();

    GString* str = g_string_new("");
    for (int i = 0; entries[i].name[0] != '\0'; i++) {
        g_string_append_printf(str, "%d. %s\n", i + 1, entries[i].name);
        g_string_append_printf(str, "     GROUP: %s\n", spending_group_to_string(entries[i].future_group));
        g_string_append_printf(str, "     SPENT: %d\n", entries[i].price);
        g_string_append_printf(str, "     OCCASION: %s\n\n", entries[i].occasion);
    }
    gtk_label_set_text(label, str->str);
}
