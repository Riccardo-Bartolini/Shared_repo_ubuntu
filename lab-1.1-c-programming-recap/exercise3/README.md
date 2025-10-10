# Exercise 3 — Function Pointers & Pipelines

## Goal 

Design a mini “processing pipeline” using arrays of function pointers with consistent signatures.

## Task 

Build a pipeline that applies N transforms in sequence, defined using function pointers.

The pipeline is executed with the following function. 

```
typedef bool (*stage_fn)(int32_t* x, void* user);
bool run_pipeline(int32_t* x, stage_fn const* stages, void* const* users, size_t n_stages);
```

It runs a pipeline of `n_stages` on input `*x`. 
Each stage may modify `*x` based on the function contained in `stages`. 
Any stage function receives as an argument two pointers: one to `x` and one to a generic user-defined value `user` you can use to pass additional arguments to the stage.
If any stage returns false, stop and return false.

Example stages to implement:

1. **add_k:** *x += k
2. **clamp:** if *x < lo -> *x = lo; if *x > hi -> *x = hi. lo and hi must be passed to the stage.
3. **map_if:** if predicate(*x) true, then *x = f(*x). Predicate and f are two functions passed to the stage through function pointers. Write two small predicates and two maps, wire up a 3-stage pipeline, and test.
```


## Constraints

* run_pipeline must not assume specific stage types; only the signature.
* users[i] may be NULL if a stage needs no config; handle gracefully.

## Quick Tests

* Start x=5, pipeline: add +7 → clamp [0,10] → if even, map x/2.
* Verify early stop logic by creating a stage that returns false on some condition.

