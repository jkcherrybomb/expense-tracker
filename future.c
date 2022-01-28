#include <gtk/gtk.h>

#include "database.h"

void future_save(GtkWidget* _this, void* data)
{
    GtkBuilder* ui = data;

    GtkEntry* name_entry = GTK_ENTRY(gtk_builder_get_object(ui, "fentry_name"));
    const char* name = gtk_entry_get_text(name_entry);

    GtkEntry* price_entry = GTK_ENTRY(gtk_builder_get_object(ui, "fentry_price"));
    float price;
    sscanf(gtk_entry_get_text(price_entry), "%f", &price);

    GtkComboBox* group_combo = GTK_COMBO_BOX(gtk_builder_get_object(ui, "fentry_combo"));
    GtkTreeIter group_iter;
    gtk_combo_box_get_active_iter(group_combo, &group_iter);
    GtkTreeModel* group_model = gtk_combo_box_get_model(group_combo);
    enum spending_group group;
    gtk_tree_model_get(group_model, &group_iter, 0, &group, -1);

    GtkComboBox* day_combo = GTK_COMBO_BOX(gtk_builder_get_object(ui, "fentry_cday"));
    GtkTreeIter day_iter;
    gtk_combo_box_get_active_iter(day_combo, &day_iter);
    GtkTreeModel* day_model = gtk_combo_box_get_model(day_combo);
    unsigned int day;
    gtk_tree_model_get(day_model, &day_iter, 0, &day, -1);

    GtkComboBox* month_combo = GTK_COMBO_BOX(gtk_builder_get_object(ui, "fentry_cmonth"));
    GtkTreeIter month_iter;
    gtk_combo_box_get_active_iter(month_combo, &month_iter);
    GtkTreeModel* month_model = gtk_combo_box_get_model(month_combo);
    unsigned int month;
    gtk_tree_model_get(month_model, &month_iter, 0, &month, -1);

    GtkComboBox* year_combo = GTK_COMBO_BOX(gtk_builder_get_object(ui, "fentry_cyear"));
    GtkTreeIter year_iter;
    gtk_combo_box_get_active_iter(year_combo, &year_iter);
    GtkTreeModel* year_model = gtk_combo_box_get_model(year_combo);
    unsigned int year;
    gtk_tree_model_get(year_model, &year_iter, 0, &year, -1);

    db_add_new(name, price, group, day, month, year);
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

    GtkListStore* day = GTK_LIST_STORE(gtk_builder_get_object(ui, "fentry_day"));
    for (unsigned int i = 1; i < 32; i++) {
        GtkTreeIter iter;
        gtk_list_store_append(day, &iter);
        gtk_list_store_set(day, &iter,
            0, i,
            -1);
    }

    GtkListStore* month = GTK_LIST_STORE(gtk_builder_get_object(ui, "fentry_month"));
    for (unsigned int i = 1; i < 13; i++) {
        GtkTreeIter iter;
        gtk_list_store_append(month, &iter);
        gtk_list_store_set(month, &iter,
            0, i,
            -1);
    }
    GtkListStore* year = GTK_LIST_STORE(gtk_builder_get_object(ui, "fentry_year"));
    for (unsigned int i = 2022; i < 2025; i++) {
        GtkTreeIter iter;
        gtk_list_store_append(year, &iter);
        gtk_list_store_set(year, &iter,
            0, i,
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
    time_t now;
    time(&now);
    struct tm* local = localtime(&now);
    int currentday = local->tm_mday;
    int currentdweek = local->tm_wday;
    int currentmonth = local->tm_mon + 1;
    int currentyear = local->tm_year + 1900;
    GtkButton* button = GTK_BUTTON(gtk_builder_get_object(ui, "future_add"));
    g_signal_connect(
        G_OBJECT(button), "clicked", G_CALLBACK(future_new), NULL);

    GtkLabel* label = GTK_LABEL(gtk_builder_get_object(ui, "future_list"));
    struct db_entry* entries = db_get_all();

    GString* str = g_string_new("");
    g_string_append_printf(str, "Current list of future spendings\n\n");
    for (int i = 0; entries[i].name[0] != '\0'; i++) {
        if (entries[i].year < currentyear)
            continue;
        if (entries[i].year == currentyear && entries[i].month < currentmonth)
            continue;
        if (entries[i].year == currentyear && entries[i].month == currentmonth && entries[i].day < currentday)
            continue;
        g_string_append_printf(str, "%d. %s\n", i + 1, entries[i].name);
        g_string_append_printf(str, "     GROUP: %s\n", spending_group_to_string(entries[i].past_group));
        g_string_append_printf(str, "     SPENT: %.2f\n", entries[i].price);
        g_string_append_printf(str, "     DATE: %u.%u.%u\n\n", entries[i].day, entries[i].month, entries[i].year);
    }
    gtk_label_set_text(label, str->str);
}
