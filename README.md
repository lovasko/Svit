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
In case this macro is defined, a source code containing the x86
optimization routines will be included during the compilation process.

##### USE_PNG
In case this macro is defined, a source code containing the `libpng` routines
used to store the rendered images to the disk will be included during the
compilation process.

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
#### libpng >= 1.6.16
This depedency can be removed by removing the `-lpng` and `-DUSE_PNG` options
from the compilation variables in the `build.ninja` file.

## Author
Daniel Lovasko lovasko@freebsd.org

