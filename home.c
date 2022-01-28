#include <gtk/gtk.h>

#include "database.h"

void delete_spending(GtkWidget* _this, void* data)
{
    GtkBuilder* ui = data;

    GtkEntry* id_entry = GTK_ENTRY(gtk_builder_get_object(ui, "delete_id"));
    unsigned int id;
    sscanf(gtk_entry_get_text(id_entry), "%u", &id);

    db_delete(id);
    gtk_main_quit();
}

void delete_window()
{
    GtkBuilder* ui = gtk_builder_new_from_file("delete.glade");

    GtkButton* button = GTK_BUTTON(gtk_builder_get_object(ui, "delete_btn"));
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(delete_spending), ui);

    GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(ui, "delete"));
    gtk_widget_show_all(GTK_WIDGET(window));
}

void home_main(GtkBuilder* ui)
{
    GtkButton* delete = GTK_BUTTON(gtk_builder_get_object(ui, "delete_spending"));
    g_signal_connect(delete, "clicked", G_CALLBACK(delete_window), NULL);

    time_t now;
    time(&now);
    struct tm* local = localtime(&now);
    int currentday = local->tm_mday;
    int currentdweek = local->tm_wday;
    int currentmonth = local->tm_mon + 1;
    int currentyear = local->tm_year + 1900;

    GtkLabel* label = GTK_LABEL(gtk_builder_get_object(ui, "home_past"));
    GtkLabel* label2 = GTK_LABEL(gtk_builder_get_object(ui, "home_future"));
    struct db_entry* entries = db_get_all();

    GString* str = g_string_new("");
    g_string_append_printf(str, "Resent past spendings\n\n");
    for (int i = 0; entries[i].name[0] != '\0'; i++) {
        if (entries[i].year > currentyear)
            continue;
        if (entries[i].year == currentyear && entries[i].month > currentmonth)
            continue;
        if (entries[i].year == currentyear && entries[i].month == currentmonth && entries[i].day > currentday)
            continue;
        g_string_append_printf(str, "[%s]", spending_group_to_string(entries[i].past_group));
        g_string_append_printf(str, " %s, ", entries[i].name);
        g_string_append_printf(str, "%.2f\n", entries[i].price);
        if (i == 9)
            break;
    }

    GString* str2 = g_string_new("");
    g_string_append_printf(str2, "Incoming future spendings\n\n");
    for (int i = 0; entries[i].name[0] != '\0'; i++) {
        if (entries[i].year < currentyear)
            continue;
        if (entries[i].year == currentyear && entries[i].month < currentmonth)
            continue;
        if (entries[i].year == currentyear && entries[i].month == currentmonth && entries[i].day < currentday)
            continue;
        g_string_append_printf(str2, "[%s]", spending_group_to_string(entries[i].past_group));
        g_string_append_printf(str2, " %s, ", entries[i].name);
        g_string_append_printf(str2, "%.2f\n", entries[i].price);
        if (i == 9)
            break;
    }

    gtk_label_set_text(label, str->str);
    gtk_label_set_text(label2, str2->str);

    free(entries);
}