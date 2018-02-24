/* extended_demo.c - another instance where PICFI
 *                   leaves some attack surface.
 *                   Showcase lpcfi_assign_copy.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../lpcfi.h"
#include "privileges.h"

int main(void) {
        #ifdef PICFI
                lpcfi_init(1);
        #else
                lpcfi_init(0);
        #endif

        /* Assignments made globally need to be accounted for. */
        lpcfi_assign_const((char **)&priv, (char *)priv);
        lpcfi_assign_const((char **)&nopriv, (char *)nopriv);

        /* Addresses of relevant functions to overcome ASLR. */
        printf("priv   points to [%p]\n", priv);
        printf("nopriv points to [%p]\n", nopriv);
        printf("main   at        [%p]\n", &main);

        void (*op)(void);
        char password[7];

        while (1) {
                printf("\nEnter password: ");
                fflush(stdout);
                read(STDIN_FILENO, password, sizeof(password));
                password[6] = '\0';

                if (strcmp(password, "finish") == 0) {
                        /* End the demo. */
                        break;
                } else if (strcmp(password, "secret") == 0) {
                        puts("Password entered CORRECTLY");
                        lpcfi_assign_copy((char **)&op, (char **)&priv);
                        op = priv;
                } else {
                        puts("Password entered INCORRECTLY");
                        lpcfi_assign_copy((char **)&op, (char **)&nopriv);
                        op = nopriv;
                }

                /* VULNERABILITY: op is overwritten from stdin. */
                read(STDIN_FILENO, (void *)&op, sizeof(&op));

                lpcfi_check((char **)&op);
                op();
        }

        puts("\n--FINISHED--");

        lpcfi_destroy();

        return 0;
}

