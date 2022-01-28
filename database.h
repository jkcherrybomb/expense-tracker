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
    int price;
    enum spending_group past_group;
    int day;
    int month;
    int year;
};

struct db_entry* db_get_all();
char* spending_group_to_string(enum spending_group group);
void db_add_new(const char* name, int price, enum spending_group group, int day, int month, int year);
