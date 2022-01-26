#include <gtk/gtk.h>

#include "database.h"

void future_save(GtkWidget* _this, void* data)
{
    GtkBuilder* ui = data;

    GtkEntry* name_entry = GTK_ENTRY(gtk_builder_get_object(ui, "fentry_name"));
    const char* name = gtk_entry_get_text(name_entry);

    GtkEntry* price_entry = GTK_ENTRY(gtk_builder_get_object(ui, "fentry_price"));
    int price;
    sscanf(gtk_entry_get_text(price_entry), "%d", &price);

    GtkComboBox* group_combo = GTK_COMBO_BOX(gtk_builder_get_object(ui, "fentry_combo"));
    GtkTreeIter group_iter;
    gtk_combo_box_get_active_iter(group_combo, &group_iter);
    GtkTreeModel* group_model = gtk_combo_box_get_model(group_combo);
    enum spending_group group;
    gtk_tree_model_get(group_model, &group_iter, 0, &group, -1);

    GtkEntry* occasion_entry = GTK_ENTRY(gtk_builder_get_object(ui, "fentry_occasion"));
    const char* occasion = gtk_entry_get_text(occasion_entry);

    db_future_add_new(name, price, group, occasion);
    gtk_main_quit();
}

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

    GtkButton* button_add = GTK_BUTTON(gtk_builder_get_object(ui, "fentry_button"));
    g_signal_connect(
        G_OBJECT(button_add), "clicked", G_CALLBACK(future_save), ui);
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
