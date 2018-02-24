/** lpcfi.c - implementation of interface in lpcfi.h. */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "fptable.h"

#define ACTIV 0xac

static fptable table;
static fptable activated_addresses;
static int picfi = 0;

/** Print "Crashing..." and exits with exit code code. */
static void crash(int code) {
        puts("Crashing...");
        exit(code);
}

void lpcfi_init(int picfi_mode) {
        table = ft_init(10);
        activated_addresses = ft_init(20);

        if (table == NULL || activated_addresses == NULL) {
                puts("Could not initialise.");
                crash(1);
        }

        picfi = picfi_mode;
}

void lpcfi_destroy(void) {
        free(table);
}

void lpcfi_assign_const(char **fp, char *func) {
        ft_set(activated_addresses, (char **)func, (char *)ACTIV);
        ft_set(table, fp, func);
}

void lpcfi_assign_copy(char **fp, char **fq) {
        char *fq_val = NULL;
        int ret = 0;

        /* Retrieve what fq should be. */
        ret = ft_lookup(table, fq, &fq_val);
        if (!ret) {
                printf("lpcfi_assign_copy: Bad call - {%p} (fq) not "
                       "in table\n", fq);
                crash(3);
        }

        /* Set fp to that value. */
        ft_set(table, fp, fq_val);
}

void lpcfi_assign_load(char **fp, char *s) {
        char *dummy = NULL;

        /* Make sure val has been activated. */
        if (!ft_lookup(activated_addresses, (char **)s, &dummy)) {
                printf("lpcfi_assign_load: {%p} (s) not "
                       "activated\n", s);
                crash(3);
        }

        /* Set fp to s. */
        ft_set(table, fp, s);
}

void lpcfi_assign_store(char *r, char **fp) {
        char *fp_val = NULL;
        int ret = 0;

        /* Retrieve what fp should be. */
        ret = ft_lookup(table, fp, &fp_val);
        if (!ret) {
                printf("lpcfi_assign_store: Bad call - {%p} (fp) not "
                       "in table\n", fp);
                crash(3);
        }

        /* Set r to the retrieved value. */
        ft_set(table, &r, fp_val);
}

void lpcfi_remove(char **ptr) {
        ft_remove(table, ptr);
}

void lpcfi_check(char **ptr) {
        char *val = NULL;
        int ret = 0;

        if (picfi) {
                /* We ONLY check that the address has been activated. */
                if (!ft_lookup(activated_addresses, (char **)*ptr, &val)) {
                        printf("lpcfi_check in PICFI mode: {%p} not "
                               "activated\n", *ptr);
                        crash(4);
                }

                /* All good. */
                return;
        }

        ret = ft_lookup(table, ptr, &val);
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

