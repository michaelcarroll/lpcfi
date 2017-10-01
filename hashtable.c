/** hashtable.c - implementation of interface in hashtable.h. */

#include <stdlib.h>
#include <stdbool.h>

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

static size_t hash(char **key, size_t size) {
        /* Don't need a good hash for this prototype. */
        return (size_t)key % size;
}

int ht_lookup(hashtable ht, char **key, char **val) {
        size_t index = 0;
        struct hashnode *curr = NULL;

        if (ht == NULL) return 0;
        if (ht->table == NULL) return 0;

        index = hash(key, ht->max_size);
        for (curr = ht->table[index]; curr != NULL; curr = curr->next) {
                if (curr->key == key) {
                        /* There's a match. */
                        *val = curr->val;
                        return true;
                }
        }

        /* Couldn't find a match. */
        return false;
}

void ht_set(hashtable ht, char **key, char *val) {

}

