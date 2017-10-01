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

        ht->table = calloc(size, sizeof(struct hashnode *));
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
        size_t index = 0;
        struct hashnode *curr = NULL, *new = NULL;

        if (ht == NULL) return;
        if (ht->table == NULL) return;

        index = hash(key, ht->max_size);
        /* First check that the key is not in the table already. */
        for (curr = ht->table[index]; curr != NULL; curr = curr->next) {
                if (curr->key == key) {
                        /* Key is already in the table. */
                        curr->val = val;
                        return;
                }
        }

        /* Need a new node - key is not in the table. */
        new = malloc(sizeof(struct hashnode));
        if (new == NULL) return;
        new->key = key;
        new->val = val;
        new->next = ht->table[index] == NULL ? NULL : ht->table[index]->next;

        ht->table[index] = new;
}

void ht_remove(hashtable ht, char **key) {
        if (ht == NULL) return;
        if (ht->table == NULL) return;

        size_t index = 0;
        struct hashnode *curr = NULL, *prev= NULL;

        index = hash(key, ht->max_size);
        curr = ht->table[index];
        if (curr == NULL) return;

        for (; curr != NULL; prev = curr, curr = curr->next) {
                if (curr->key == key) {
                        if (prev == NULL) ht->table[index] = curr->next;
                        else prev->next = curr->next;

                        free(curr);
                        return;
                }
        }
}

