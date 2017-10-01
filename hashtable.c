/** hashtable.c - implementation of interface in hashtable.h. */

#include <stdlib.h>

#include "hashtable.h"

struct hashnode {
        char **key;
        char *val;
        struct hashnode *next;
};

struct hashtable {
        size_t max_size;  /** Number of keys the table can take. */
        size_t n_keys;    /** Number of keys currently in the table. */
        struct hashnode **table;  /** Array of hashnodes. */
};

hashtable ht_init(size_t size) {
        hashtable ht = malloc(sizeof(struct hashtable));
        if (ht == NULL) return NULL;

        ht->table = malloc(sizeof(struct hashnode *) * size);
        if (ht->table == NULL) {
                free(ht);
                return NULL;
        }

        return ht;
}

void ht_destroy(hashtable ht) {
        if (ht == NULL) return;
        free(ht->table);
        free(ht);
}

int ht_lookup(hashtable ht, char **key, char **val) {

        return 0;
}

void ht_set(hashtable ht, char **key, char *val) {

}

