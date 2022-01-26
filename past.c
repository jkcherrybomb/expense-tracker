#include <gtk/gtk.h>

#include "database.h"

void past_new()
{
    GtkBuilder* ui = gtk_builder_new_from_file("past_new.glade");

    GtkListStore* groups = GTK_LIST_STORE(gtk_builder_get_object(ui, "pentry_group"));
    for (enum spending_group i = 0; i < SPENDING_GROUP_LENGTH; i++) {
        GtkTreeIter iter;
        gtk_list_store_append(groups, &iter);
        gtk_list_store_set(groups, &iter,
            0, i,
            1, spending_group_to_string(i),
            -1);
    }

    GtkListStore* payment = GTK_LIST_STORE(gtk_builder_get_object(ui, "pentry_payment"));
    for (enum payment_type i = 0; i < PAYMENT_TYPE_LENGTH; i++) {
        GtkTreeIter iter;
        gtk_list_store_append(payment, &iter);
        gtk_list_store_set(payment, &iter,
            0, i,
            1, payment_type_to_string(i),
            -1);
    }

    GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(ui, "pentry_window"));
    gtk_widget_show_all(GTK_WIDGET(window));
}

void past_main(GtkBuilder* ui)
{
    GtkButton* button = GTK_BUTTON(gtk_builder_get_object(ui, "past_add"));
    g_signal_connect(
        G_OBJECT(button), "clicked", G_CALLBACK(past_new), NULL);

    GtkLabel* label = GTK_LABEL(gtk_builder_get_object(ui, "past_list"));
    struct past_entry* entries = db_past_get_all();

    GString* str = g_string_new("");
    for (int i = 0; entries[i].name[0] != '\0'; i++) {
        g_string_append_printf(str, "%d. %s\n", i + 1, entries[i].name);
        g_string_append_printf(str, "     GROUP: %s\n", spending_group_to_string(entries[i].past_group));
        g_string_append_printf(str, "     SPENT: %d\n", entries[i].price);
        g_string_append_printf(
            str, "     PAYMENT TYPE: %s\n", payment_type_to_string(entries[i].payment));
        g_string_append_printf(str, "     DATE: %d.%d.%d\n\n", entries[i].day, entries[i].month, entries[i].year);
    }
    gtk_label_set_text(label, str->str);
}
