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

struct db_entry {
    char name[200];
    float price;
    enum spending_group past_group;
    int day;
    int month;
    int year;
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

void db_create_if_missing()
{
    FILE* file = fopen("database.txt", "r");
    if (file == NULL) {
        file = fopen("database.txt", "w");
        fprintf(file, "0\n");
    }
    fclose(file);
}

struct db_entry*
db_get_all()
{
    FILE* file = fopen("database.txt", "r");
    unsigned int num_lines;
    fscanf(file, "%u\n", &num_lines);
    struct db_entry* pas = malloc((num_lines + 1) * sizeof(struct db_entry));
    for (unsigned int i = 0; i < num_lines; i++) {
        fscanf(file,
            "%s %f %u %u %u %u\n",
            pas[i].name,
            &pas[i].price,
            &pas[i].past_group,
            &pas[i].day,
            &pas[i].month,
            &pas[i].year);
    }
    fclose(file);
    pas[num_lines].name[0] = '\0';
    return pas;
}

void db_add_new(const char* name, float price, enum spending_group group, int day, int month, int year)
{
    FILE* file = fopen("database.txt", "r");
    unsigned int num_lines;
    fscanf(file, "%u\n", &num_lines);

    FILE* file2 = fopen("database.txt", "w");
    fprintf(file2, "%u\n", num_lines + 1);
    fprintf(file2,
        "%s %f %u %u %u %u\n",
        name,
        price,
        group,
        day,
        month,
        year);

    char buf[4096];
    while (fgets(buf, 4096, file) != NULL)
        fputs(buf, file2);

    fclose(file);
    fclose(file2);
}

void db_delete(unsigned int id)
{
    FILE* file = fopen("database.txt", "r");
    unsigned int num_lines;
    fscanf(file, "%u\n", &num_lines);

    FILE* file2 = fopen("database.txt", "w");
    fprintf(file2, "%u\n", num_lines - 1);
    for (unsigned int i = 0; i < num_lines; i++) {
        char name[200];
        float price;
        enum spending_group past_group;
        int day, month, year;
        fscanf(file,
            "%s %f %u %u %u %u\n",
            name,
            &price,
            &past_group,
            &day,
            &month,
            &year);
        if (i + 1 != id) {
            fprintf(file2,
                "%s %f %u %u %u %u\n",
                name,
                price,
                past_group,
                day,
                month,
                year);
        }
    }

    fclose(file);
    fclose(file2);
}