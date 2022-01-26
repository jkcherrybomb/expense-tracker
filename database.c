#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum spending_group {
    FOOD,
    RENT,
    MEDIA,
    TRANSPORT,
    TRAIN_HOME,
    MEDS,
    HEALTHCARE,
    HYGIENE,
    COSMETICS,
    CLOTHING,
    FOOD_OUT,
    OUTINGS,
    PARTIES,
    PRESENTS,
    BOOKS,
    SPORT,
    TRIPS,
    HOME_APPLIANCES,
    TECHNOLOGY,
    OTHERS,
    SPENDING_GROUP_LENGTH
};

enum payment_type {
    CASH,
    CREDIT_CARD,
    DEBIT_CARD,
    PAYMENT_TYPE_LENGTH
};

struct past_entry {
    char name[200];
    int price;
    enum spending_group past_group;
    enum payment_type payment;
    int day;
    int month;
    int year;
};

struct future_entry {
    char name[200];
    int price;
    enum spending_group future_group;
    char occasion[200];
};

char* spending_group_to_string(enum spending_group group)
{
    if (group == FOOD)
        return "food";
    if (group == RENT)
        return "rent";
    if (group == MEDIA)
        return "media";
    if (group == TRANSPORT)
        return "transport";
    if (group == TRAIN_HOME)
        return "train home";
    if (group == MEDS)
        return "meds";
    if (group == HEALTHCARE)
        return "healthcare";
    if (group == HYGIENE)
        return "hygiene";
    if (group == COSMETICS)
        return "cosmetics";
    if (group == CLOTHING)
        return "clothing";
    if (group == FOOD_OUT)
        return "food out";
    if (group == OUTINGS)
        return "outings";
    if (group == PARTIES)
        return "parties";
    if (group == PRESENTS)
        return "presents";
    if (group == BOOKS)
        return "books";
    if (group == SPORT)
        return "sport";
    if (group == TRIPS)
        return "trips";
    if (group == HOME_APPLIANCES)
        return "home appliances";
    if (group == TECHNOLOGY)
        return "technology";
    if (group == OTHERS)
        return "others";
    return "";
}

char* payment_type_to_string(enum payment_type payment)
{
    if (payment == CASH)
        return "cash";
    if (payment == CREDIT_CARD)
        return "credit card";
    if (payment == DEBIT_CARD)
        return "debit card";
}

struct past_entry*
db_past_get_all()
{
    FILE* file = fopen("past_sample.txt", "r");
    int num_lines;
    fscanf(file, "%d\n", &num_lines);
    struct past_entry* pas = malloc((num_lines + 1) * sizeof(struct past_entry));
    for (int i = 0; i < num_lines; i++) {
        fscanf(file,
            "%s %d %u %u %u %u %u\n",
            pas[i].name,
            &pas[i].price,
            &pas[i].past_group,
            &pas[i].payment,
            &pas[i].day,
            &pas[i].month,
            &pas[i].year);
    }
    fclose(file);
    pas[num_lines].name[0] = '\0';
    return pas;
}

void db_past_add_new(const char* name, int price, enum spending_group group, enum payment_type payment, int day, int month, int year)
{
    FILE* file = fopen("past_sample.txt", "r");
    int num_lines;
    fscanf(file, "%d\n", &num_lines);

    FILE* file2 = fopen("past_sample.txt", "w");
    fprintf(file2, "%d\n", num_lines + 1);
    fprintf(file2,
        "%s %d %u %u %u %u %u\n",
        name,
        price,
        group,
        payment,
        day,
        month,
        year);

    char buf[4096];
    while (fgets(buf, 4096, file) != NULL)
        fputs(buf, file2);

    fclose(file);
    fclose(file2);
}

struct future_entry*
db_future_get_all()
{
    FILE* file = fopen("future_sample.txt", "r");
    int num_lines;
    fscanf(file, "%d\n", &num_lines);
    struct future_entry* fut = malloc((num_lines + 1) * sizeof(struct future_entry));
    for (int i = 0; i < num_lines; i++) {
        fscanf(file,
            "%s %d %u %s\n",
            fut[i].name,
            &fut[i].price,
            &fut[i].future_group,
            fut[i].occasion);
    }
    fclose(file);
    fut[num_lines].name[0] = '\0';
    return fut;
}

void db_future_add_new(const char* name, int price, enum spending_group group, const char* occasion)
{
    FILE* file = fopen("future_sample.txt", "r");
    int num_lines;
    fscanf(file, "%d\n", &num_lines);

    FILE* file2 = fopen("future_sample.txt", "w");
    fprintf(file2, "%d\n", num_lines + 1);
    fprintf(file2,
        "%s %d %u %s\n",
        name,
        price,
        group,
        occasion);

    char buf[4096];
    while (fgets(buf, 4096, file) != NULL)
        fputs(buf, file2);

    fclose(file);
    fclose(file2);
}