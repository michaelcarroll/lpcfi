
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
        #ifdef PICFI
                lpcfi_init(1);
        #else
                lpcfi_init(0);
        #endif

        printf("g    at [%p]\n", &g);
        printf("h    at [%p]\n", &h);
        printf("foo  at [%p]\n", &foo);
        printf("main at [%p]\n", &main);

        foo(1);
        foo(0);

        lpcfi_destroy();

        return 0;
}

