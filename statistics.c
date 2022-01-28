#include "database.h"
#include <gtk/gtk.h>
#include <string.h>
#include <time.h>

char* day_to_string(int d)
{
    if (d == 1)
        return "Monday";
    if (d == 2)
        return "Tuesday";
    if (d == 3)
        return "Wedensday";
    if (d == 4)
        return "Thursday";
    if (d == 5)
        return "Friday";
    if (d == 6)
        return "Saturday";
    if (d == 7)
        return "Sunday";
}

char* month_to_string(int m)
{
    if (m == 1)
        return "January";
    if (m == 2)
        return "February";
    if (m == 3)
        return "March";
    if (m == 4)
        return "April";
    if (m == 5)
        return "March";
    if (m == 6)
        return "June";
    if (m == 7)
        return "July";
    if (m == 8)
        return "August";
    if (m == 9)
        return "September";
    if (m == 10)
        return "October";
    if (m == 11)
        return "November";
    if (m == 12)
        return "December";
}

void statistics_main(GtkBuilder* ui)
{
    time_t now;
    time(&now);
    struct tm* local = localtime(&now);
    int currentday = local->tm_mday;
    int currentdweek = local->tm_wday;
    int currentmonth = local->tm_mon + 1;
    int currentyear = local->tm_year + 1900;

    GtkLabel* label = GTK_LABEL(gtk_builder_get_object(ui, "statistics_label"));
    GString* str = g_string_new("");
    g_string_append_printf(str, "Today's date: %s, %02d.%02d.%d\n\n", day_to_string(currentdweek), currentday, currentmonth, currentyear);

    struct db_entry* entries = db_get_all();
    long long past_sum = 0;
    long long future_sum = 0;
    for (int i = 0; entries[i].name[0] != '\0'; i++) {
        if (entries[i].month == currentmonth && entries[i].year == currentyear && entries[i].day <= currentday)
            past_sum += entries[i].price;
        if (entries[i].month == currentmonth && entries[i].year == currentyear && entries[i].day > currentday)
            future_sum += entries[i].price;
    }
    g_string_append_printf(str, "Spent until now this month: %lld\n", past_sum);

    g_string_append_printf(str, "Sum of planned future spendings this month: %lld\n", future_sum);

    g_string_append_printf(str, "Total sum of money planned to be spent this month : %lld\n", future_sum + past_sum);

    gtk_label_set_text(label, str->str);
}