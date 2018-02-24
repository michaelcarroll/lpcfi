/** fptable.c - implementation of interface in fptable.h. */

#include <stdlib.h>
#include <stdbool.h>

#include "fptable.h"

struct hashnode {
        char **key;
        char *val;
        struct hashnode *next;
};

struct fptable {
        size_t max_size;  /** Number of slots in the table. */
        // size_t n_keys;    /** Number of keys currently in the table. */
        struct hashnode **table;  /** Array of hashnodes. */
};

fptable ft_init(size_t size) {
        fptable ft = malloc(sizeof(struct fptable));
        if (ft == NULL) return NULL;

        ft->max_size = size;
        ft->table = calloc(size, sizeof(struct hashnode *));
        if (ft->table == NULL) {
                free(ft);
                return NULL;
        }

        return ft;
}

void ft_destroy(fptable ft) {
        if (ft == NULL) return;
        free(ft->table);
        free(ft);
}

static size_t hash(char **key, size_t size) {
        /* Don't need a good hash for this prototype. */
        return (size_t)key % size;
}

int ft_lookup(fptable ft, char **key, char **val) {
        size_t index = 0;
        struct hashnode *curr = NULL;

        if (ft == NULL) return 0;
        if (ft->table == NULL) return 0;

        index = hash(key, ft->max_size);
        for (curr = ft->table[index]; curr != NULL; curr = curr->next) {
                if (curr->key == key) {
                        /* There's a match. */
                        *val = curr->val;
                        return true;
                }
        }

        /* Couldn't find a match. */
        return false;
}

void ft_set(fptable ft, char **key, char *val) {
        size_t index = 0;
        struct hashnode *curr = NULL, *new = NULL;

        if (ft == NULL) return;
        if (ft->table == NULL) return;

        index = hash(key, ft->max_size);
        /* First check that the key is not in the table already. */
        for (curr = ft->table[index]; curr != NULL; curr = curr->next) {
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
        new->next = ft->table[index] == NULL ? NULL : ft->table[index];

        ft->table[index] = new;
}

void ft_remove(fptable ft, char **key) {
        if (ft == NULL) return;
        if (ft->table == NULL) return;

        size_t index = 0;
        struct hashnode *curr = NULL, *prev= NULL;

        index = hash(key, ft->max_size);
        curr = ft->table[index];
        if (curr == NULL) return;

        for (; curr != NULL; prev = curr, curr = curr->next) {
                if (curr->key == key) {
                        if (prev == NULL) ft->table[index] = curr->next;
                        else prev->next = curr->next;

                        free(curr);
                        return;
                }
        }
}

