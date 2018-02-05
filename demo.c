
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

#include "lpcfi.h"

void g(void) { puts("Called g!"); }
void h(void) { puts("Called h!"); }

void (*fp)(void);
void foo(int n) {
        if (n) {
                lpcfi_handle_const((char **)&fp, (char *)&g);
                fp = &g;
        } else {
                lpcfi_handle_const((char **)&fp, (char *)&h);
                fp = &h;
        }

        read(STDIN_FILENO, (void *)&fp, sizeof(&fp));

        lpcfi_check((char **)&fp);
        fp();
}

int main(void) {
        lpcfi_init(0);

        printf("g at [%p]\n", &g);
        printf("h at [%p]\n", &h);

        foo(1);
        foo(0);

        lpcfi_destroy();

        return 0;
}

