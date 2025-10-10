# Exercise 2 — void* for Type-Generic Utilities

## Goal

Build type-generic primitives with `void* ` and element size.

## Task

### Function 1

Implement a generic swap function that swaps the content of two objects of `size` bytes may overlap.

```
void vswap(void* a, void* b, size_t size);
```

### Function 2


Implement a function that copies `count` elements from `src` to `dst`, each of size `elem_size`.
The two regions may overlap. 

```
void vcopy_n(void* dst, const void* src, size_t count, size_t elem_size);
```

### Function 3

Write a function that computes min and max of an array using a comparator function:`comparator(a, b)` that returns <0 if `*a < *b`, 0 if equal, >0 if `*a > *b`. The comparator funcion is passed as a parameter to the min

On success, provide pointers to the first min and first max elements.

```
bool vminmax(const void* base, size_t count, size_t elem_size,
             int (*comparator)(const void*, const void*),
             const void** out_min, const void** out_max);
```

Provide two comparators for tests:

```
int cmp_int32(const void* a, const void* b);
int cmp_double(const void* a, const void* b);
```

## Constraints

* No type punning; treat memory as unsigned char* when moving bytes.
* Handle `count == 0` robustly.

## Tests

* vswap on two doubles.
* vcopy_n moving overlapping regions within an int32_t array.
* vminmax on int32_t and double arrays.




