/** hashtable.h - interface to a hash table with pointer keys (address
 *                of function pointers) and pointer values.
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct hashtable *hashtable;

/** Returns a malloc'd hash table with an initial size of size. */
hashtable ht_init(size_t size);

/** Deallocates the hash table at ht. */
void ht_destroy(hashtable ht);

/** Looks up the value associated with key in ht. If there is a
 *  value associated with key, returns a true value, and sets *val
 *  to that value. Otherwise, returns 0 and leaves val untouched.
 */
int ht_lookup(hashtable ht, char **key, char **val);

/** Sets key to val in ht. */
void ht_set(hashtable ht, char **key, char *val);

/** Removes entry associated with key in ht. */
void ht_remove(hashtable ht, char **key);

#endif  /* HASHTABLE_H */

