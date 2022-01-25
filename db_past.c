#include <stdlib.h>
#include <string.h>

struct past_entry {
    char* name;
    int price;
};

struct past_entry* db_past_get_all() {
    struct past_entry* ret = malloc(1000 * sizeof(struct past_entry));

    ret[0].name = strdup("Test 1");
    ret[0].price = 100;

    ret[1].name = strdup("Test 2");
    ret[1].price = 200;

    ret[2].name = NULL;

    return ret;
}
