/* privilieges.c - contains definitions
 *                 for privileged and unprivileged
 *                 operations.
 */

#include <stdio.h>

#include "privileges.h"

void (*priv)(void)   = &privileged_operation;
void (*nopriv)(void) = &unprivileged_operation;

void privileged_operation(void) {
        puts("Performing PRIVILEGED operation.");
}

void unprivileged_operation(void) {
        puts("Performing UNPRIVILEGED operation.");
}
