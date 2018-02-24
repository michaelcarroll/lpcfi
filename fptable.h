/** fptable.h - interface to a hash table with pointer keys (address
 *                of function pointers) and pointer values.
 */

#ifndef FPTABLE_H
#define FPTABLE_H

typedef struct fptable *fptable;

/** Returns a malloc'd hash table with an initial size of size. */
fptable ft_init(size_t size);

/** Deallocates the hash table at ft. */
void ft_destroy(fptable ft);

/** Looks up the value associated with key in ft. If there is a
 *  value associated with key, returns a true value, and sets *val
 *  to that value. Otherwise, returns 0 and leaves val untouched.
 */
int ft_lookup(fptable ft, char **key, char **val);

/** Sets key to val in ft. */
void ft_set(fptable ft, char **key, char *val);

/** Removes entry associated with key in ft. */
void ft_remove(fptable ft, char **key);

#endif  /* FPTABLE_H */

