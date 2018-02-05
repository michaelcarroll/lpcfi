/** lpcfi.c - implementation of interface in lpcfi.h. */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "hashtable.h"

#define ACTIV 0xac

static hashtable table;
static hashtable activated_addresses;
static int picfi = 0;

/** Print "Crashing..." and exits with exit code code. */
static void crash(int code) {
        puts("Crashing...");
        exit(code);
}

void lpcfi_init(int picfi_mode) {
        table = ht_init(10);
        activated_addresses = ht_init(20);

        if (table == NULL || activated_addresses == NULL) {
                puts("Could not initialise.");
                crash(1);
        }

        picfi = picfi_mode;
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
                printf("lpcfi_handle_copy: Bad call - {%p} (fq) not "
                       "in table\n", fq);
                crash(3);
        }

        /* Set fp to that value. */
        ht_set(table, fp, fq_val);
}

void lpcfi_handle_load(char **fp, char *s) {
        char *dummy = NULL;

        /* Make sure val has been activated. */
        if (!ht_lookup(activated_addresses, (char **)s, &dummy)) {
                printf("lpcfi_handle_load: {%p} (s) not "
                       "activated\n", s);
                crash(3);
        }

        /* Set fp to s. */
        ht_set(table, fp, s);
}

void lpcfi_handle_store(char *r, char **fp) {
        char *fp_val = NULL;
        int ret = 0;

        /* Retrieve what fp should be. */
        ret = ht_lookup(table, fp, &fp_val);
        if (!ret) {
                printf("lpcfi_handle_store: Bad call - {%p} (fp) not "
                       "in table\n", fp);
                crash(3);
        }

        /* Set r to the retrieved value. */
        ht_set(table, &r, fp_val);
}

void lpcfi_remove(char **ptr) {
        ht_remove(table, ptr);
}

void lpcfi_check(char **ptr) {
        char *val = NULL, *dummy = NULL;
        int ret = 0;

        if (picfi) {
                /* We ONLY check that the address has been activated. */
                if (!ht_lookup(activated_addresses, (char **)*ptr, &dummy)) {
                        printf("lpcfi_check in PICFI mode: {%p} not "
                               "activated\n", *ptr);
                        crash(4);
                }

                /* All good. */
                return;
        }

        ret = ht_lookup(table, ptr, &val);
        if (ret && *ptr != val) {
                printf("lpcfi_check: Expected [%p] at {%p} but was [%p]\n",
                       val, ptr, *ptr);
                crash(2);
        } else if (!ret) {
                printf("lpcfi_check: Bad call - {%p} not in table\n", ptr);
                crash(3);
        }

        /* Otherwise it's all good. */
}

