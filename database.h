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

struct past_entry* db_past_get_all();
struct future_entry* db_future_get_all();
char* spending_group_to_string(enum spending_group group);
char* payment_type_to_string(enum payment_type payment);
void db_past_add_new(const char* name, int price, enum spending_group group, enum payment_type payment, int day, int month, int year);
void db_future_add_new(const char* name, int price, enum spending_group group, const char* occasion);
