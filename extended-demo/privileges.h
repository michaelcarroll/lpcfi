/* privileges.h - contains definitions
 *                 for priv and nopriv.
 */

#ifndef PRIVILEGES_H
#define PRIVILEGES_H

void privileged_operation(void);
void unprivileged_operation(void);

extern void (*priv)(void);
extern void (*nopriv)(void);

#endif  /* PRIVILEGES_H */

