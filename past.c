#include <gtk/gtk.h>

#include "database.h"

void past_save(GtkWidget* _this, void* data)
{
    GtkBuilder* ui = data;

    GtkEntry* name_entry = GTK_ENTRY(gtk_builder_get_object(ui, "pentry_name"));
    const char* name = gtk_entry_get_text(name_entry);

    GtkEntry* price_entry = GTK_ENTRY(gtk_builder_get_object(ui, "pentry_price"));
    int price;
    sscanf(gtk_entry_get_text(price_entry), "%d", &price);

    GtkComboBox* group_combo = GTK_COMBO_BOX(gtk_builder_get_object(ui, "pentry_combo"));
    GtkTreeIter group_iter;
    gtk_combo_box_get_active_iter(group_combo, &group_iter);
    GtkTreeModel* group_model = gtk_combo_box_get_model(group_combo);
    enum spending_group group;
    gtk_tree_model_get(group_model, &group_iter, 0, &group, -1);

    GtkComboBox* payment_combo = GTK_COMBO_BOX(gtk_builder_get_object(ui, "pentry_combo2"));
    GtkTreeIter payment_iter;
    gtk_combo_box_get_active_iter(payment_combo, &payment_iter);
    GtkTreeModel* payment_model = gtk_combo_box_get_model(payment_combo);
    enum payment_type payment;
    gtk_tree_model_get(payment_model, &payment_iter, 0, &payment, -1);

    GtkEntry* day_entry = GTK_ENTRY(gtk_builder_get_object(ui, "pentry_day"));
    int day;
    sscanf(gtk_entry_get_text(day_entry), "%d", &day);

    GtkEntry* month_entry = GTK_ENTRY(gtk_builder_get_object(ui, "pentry_month"));
    int month;
    sscanf(gtk_entry_get_text(month_entry), "%d", &month);

    GtkEntry* year_entry = GTK_ENTRY(gtk_builder_get_object(ui, "pentry_year"));
    int year;
    sscanf(gtk_entry_get_text(year_entry), "%d", &year);

    db_past_add_new(name, price, group, payment, day, month, year);
    gtk_main_quit();
}

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

    GtkButton* button_add = GTK_BUTTON(gtk_builder_get_object(ui, "pentry_button"));
    g_signal_connect(
        G_OBJECT(button_add), "clicked", G_CALLBACK(past_save), ui);
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
        g_string_append_printf(str, "     DATE: %u.%u.%u\n\n", entries[i].day, entries[i].month, entries[i].year);
    }
    gtk_label_set_text(label, str->str);
}
