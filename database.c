#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
    OTHERS
};

enum payment_type {
    CASH,
    CREDIT_CARD,
    DEBIT_CARD
};

struct past_entry {
    char name[200];
    int price;
    enum spending_group past_group;
    enum payment_type payment;
};

struct future_entry {
    char name[200];
    int price;
    enum spending_group future_group;
    char occasion[200];
};

struct past_entry* db_past_get_all() {
    FILE *file = fopen("past_sample.txt", "r");
    int num_lines;
    fscanf(file, "%d\n", &num_lines);
    struct past_entry* pas = malloc((num_lines + 1) * sizeof(struct past_entry));
    for(int i = 0; i < num_lines; i++) {
        fscanf(file, "%s %d %u %u\n", pas[i].name, &pas[i].price, &pas[i].past_group, &pas[i].payment);
    }
    pas[num_lines].name[0] = '\0';
    return pas;
}

struct future_entry* db_future_get_all() {
    FILE *file = fopen("future_sample.txt", "r");
    int num_lines;
    fscanf(file, "%d\n", &num_lines);
    struct future_entry* fut = malloc((num_lines + 1) * sizeof(struct future_entry));
    for(int i = 0; i < num_lines; i++) {
        fscanf(file, "%s %d %u %s\n", fut[i].name, &fut[i].price, &fut[i].future_group, fut[i].occasion);
    }
    fut[num_lines].name[0] = '\0';
    return fut;
}