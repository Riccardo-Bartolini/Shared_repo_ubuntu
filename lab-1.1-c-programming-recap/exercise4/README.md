# Exercise 4 — Advanced Argument Passing with Pointers (out-params, ptr-to-ptr)**

## Goal: 

Practice ownership transfer, T** patterns, and API design.

### _Task A — strsplit_

Implement a splitter that allocates tokens and returns them via triple-pointer:

Split `s` on delimiter `delim`. On success:

- *out_tokens points to a newly allocated array of char* (N tokens)
- each token is a newly allocated NULL-terminated string
- *out_count is set to N

Caller must free each token and then the array.

Returns 0 on success, nonzero on failure.

```
int strsplit(const char* s, char delim, char*** out_tokens, size_t* out_count);
```

**Expected Behavior**

* Consecutive delimiters produce empty tokens (e.g., "a,,b" → "a", "", "b").
* Handles leading/trailing delimiters.
* s == NULL ⇒ error.

### _Task B — Singly Linked List Insertion

Let's consider a linked list composed of elements of this type.

```
typedef struct node {
    int value;
    struct node* next;
} node;
```

Implement the following functions:

Insert a new element in the list: 

```
void list_push_front(node** head, int value);
```

Removes the first occurrence of `value`. Returns true if removed.

```
bool list_remove_first(node** head, int value);
```

Free the entire list; sets *head to NULL.

```
void list_free(node** head);
```

## Constraints

* Absolutely no memory leaks.
* Functions must be total: accept head == NULL gracefully where sensible.

## Quick Tests

* strsplit("::a::", ':') → tokens: "", "", "a", "", "" (count 5).
* Build a list, remove the middle element, verify head updates.

