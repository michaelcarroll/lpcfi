/** lpcfi.h - interface to LPCFI.
 *
 *  Safe memory is not implemented but is referred to. The pointer-value
 *  table is assumed to be safe in this prototype.
 */

#ifndef LPCFI_H
#define LPCFI_H

/** This implementation is an ADO, call at the start of main. */
void lpcfi_init(void);

/** Frees resources used by LPCFI. */
void lpcfi_destroy(void);

/** Sets a function address to activated - that it's address has been taken. */
void lpcfi_activate(char *ptr);

/** Set ptr within safe memory to constant value val. */
void lpcfi_set_const(char **ptr, char *val);

/** Set ptr within safe memory to point to the same value that
 *  deref_ptr does in safe memory.
 */
void lpcfi_set_dyn_safe(char **ptr, char **deref_ptr);

/** Set ptr within safe memory to point to the actual value val. */
void lpcfi_set_dyn(char **ptr, char *val);

/** Removes ptr from the safe memory table. */
void lpcfi_remove(char **ptr);

/** Check that ptr is set to the value saved in safe memory. Returns
 *  so, otherwise crashes.
 */
void lpcfi_check_ptr(char **ptr);

/** Check that the current value of ptr is within the specified pointer set.
 *  n_ptrs is the size of the pointer set ptr will be checked against, and all
 *  remaining arguments represent that pointer set.
 *
 *  Returns if ptr is contained within that pointer set,
 *  otherwise crashes.
 */
void lpcfi_within(char *ptr, unsigned int n_ptrs, ...);

#endif  /* LPCFI_H */

