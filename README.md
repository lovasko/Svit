# Svit
C++11 raytracer

## Features
 * OBJ file loading
 * x86 SIMD optimizations
 * multi-threaded execution
 * PNG output

## Build
### Compilation options
##### USE_SSE
##### USE_PNG

### Ninja
```
$ ninja
```

## Directories
### `bin`
The final raytracer binary `svit` is stored here.

### `doc`
Documentation in Markdown form is stored here.

### `img`
Example images accumulated during testing features are stored here.

### `obj`
Intermediate object files produced during build are stored here.

### `src`
Source files for the raytracer are stored here.

## Dependencies
### libpng

## Author
Daniel Lovasko lovasko@freebsd.org

