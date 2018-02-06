/** lpcfi.h - interface to LPCFI.
 *
 *  Safe memory is not implemented but is referred to. The pointer-value
 *  table is assumed to be safe in this prototype.
 */

#ifndef LPCFI_H
#define LPCFI_H

/** This implementation is an ADO, call at the start of main. picfi_mode
  * limits checks to ensuring that the address to be checked is merely
  * activated (more coarse than PICFI, but sufficient for our demo).
  */
void lpcfi_init(int picfi_mode);

/** Frees resources used by LPCFI. Not particularly necessary since it'd
  * usually only be called just before main returns.
  */
void lpcfi_destroy(void);

/** Set fp within the fp-table to point to function func exclusively,
  * and regard func as activated.
  */
void lpcfi_assign_const(char **fp, char *func);

/** Sets fp in the fp-table to exclusively point to whatever fq does (from
  * the fp-table).
  */
void lpcfi_assign_copy(char **fp, char **fq);

/** Set fp within the fp-table to point to the actual (runtime) value s. */
void lpcfi_assign_load(char **ptr, char *s);

/** Set the actual (runtime) value r in the fp-table to exclusively point
  * to whatever fp does (in the fp-table).
  */
void lpcfi_assign_store(char *r, char **fp);

/** Removes fp from the fp-table. */
void lpcfi_remove(char **fp);

/** Checks that fp is set to the value saved in the fp-table. Returns if
 *  so, otherwise crashes.
 */
void lpcfi_check(char **fp);

#endif  /* LPCFI_H */

