# MMM_C (Miniature Matrix Math Library in C)

## Description

Just like the name implies, this project is a miniature matrix math library
that's designed for a very small size.

It focuses on minimal external dependencies and being thoroughly tested and
can be used for embedded applications as well as more powerful systems.

### What it isn't

This isn't a highly platform specific optimized library. It also isn't designed
to be used on GPU or multi core systems.

### What it is

- It's a good example of how matrix operations can be done in C code.
- A very well tested library.
- Decently space efficient.
- Reasonably performant.

## Memory Model

For the dynamic memory of the matrices instead of using arrays of pointers
the matrix cells are contiguous chunks of memory that is allocated in a
single step.

This avoids dealing with having multiple allocation function calls for arrays.
Another benefit is it simplifies freeing the memory after use.

## Applicaitons

**TODO:** Add list of project links where used.

## Instructions



## Tests

**How To run Tests:**

```sh
echo "1" | ./otto.sh
```


## Roadmap

- [ ] Add dynamic matrix types.
- [ ] Add static matrix types.
- [ ] Add module for loading matx format files.
- [ ] Add matrix file format to load matricies.

## License

