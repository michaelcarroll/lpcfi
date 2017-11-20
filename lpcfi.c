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

void lpcfi_handle_const(char **fp, char *fq) {
        ht_set(activated_addresses, (char **)fp, (char *)ACTIV);
        ht_set(table, fp, fq);
}

void lpcfi_handle_copy(char **fp, char **fq) {
        char *fq_val = NULL;
        int ret = 0;

        /* Retrieve what fq should be. */
        ret = ht_lookup(table, fq, &fq_val);
        if (!ret) {
                printf("lpcfi_set_dyn_safe: Bad call - {%p} (fq) not "
                       "in table\n", fq);
                crash(3);
        }

        /* Set fp to that value. */
        ht_set(table, fp, fq_val);
}

void lpcfi_set_dyn(char **fp, char *s) {
        char *dummy = NULL;

        /* Make sure val has been activated. */
        if (!ht_lookup(activated_addresses, (char **)s, &dummy)) {
                printf("lpcfi_set_dyn: {%p} (s) not "
                       "activated\n", s);
                crash(3);
        }

        /* Set fp to s. */
        ht_set(table, fp, s);
}

void lpcfi_remove(char **ptr) {
        ht_remove(table, ptr);
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

