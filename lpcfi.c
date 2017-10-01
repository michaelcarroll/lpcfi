/** lpcfi.c - implementation of interface in lpcfi.h. */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "hashtable.h"

#define ACTIV 0xac

static hashtable table;
static hashtable activated_addresses;

/** Print "Crashing..." and exits with exit code code. */
static void crash(int code) {
        puts("Crashing...");
        exit(code);
}

void lpcfi_init(void) {
        table = ht_init(10);
        activated_addresses = ht_init(20);

        if (table == NULL || activated_addresses == NULL) {
                puts("Could not initialise.");
                crash(1);
        }
}

void lpcfi_destroy(void) {
        free(table);
}

void lpcfi_set_const(char **ptr, char *val) {
        ht_set(table, ptr, val);
        /* Activate val - it's address has been taken. */
        //ht_set(activated_addresses, (char **)val, ACTIV);
}

void lpcfi_set_dyn(char **ptr, char **deref_ptr) {
        char *deref_val = NULL;
        int ret = 0;

        /* Retrieve what deref_ptr should be. */
        ret = ht_lookup(table, deref_ptr, &deref_val);
        if (!ret) {
                printf("lpcfi_set_dyn: Bad call - {%p} (deref_ptr) not "
                       "in table\n", deref_ptr);
                crash(3);
        }

        /* Set ptr to that value. */
        ht_set(table, ptr, deref_val);
}

void lpcfi_check_ptr(char **ptr) {
        char *val = NULL;
        int ret = 0;

        ret = ht_lookup(table, ptr, &val);
        if (ret && *ptr != val) {
                printf("lpcfi_check_ptr: Expected [%p] at {%p} but was [%p]\n",
                       val, ptr, *ptr);
                crash(2);
        } else if (!ret) {
                printf("lpcfi_check_ptr: Bad call - {%p} not in table\n", ptr);
                crash(3);
        }

        /* Otherwise it's all good. */
}

void lpcfi_within(char *ptr, unsigned int n_ptrs, ...) {
        va_list ptrs;

        va_start(ptrs, n_ptrs);
        for (size_t i = 0; i < n_ptrs; ++i) {
                if (ptr == va_arg(ptrs, char *)) {
                        va_end(ptrs);
                        return;
                }
        }

        va_end(ptrs);
        printf("lpcfi_within: {%p} (value) not in specified set\n", ptr);
        crash(4);
}

