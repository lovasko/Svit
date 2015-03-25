# Svit
C++11 raytracer

## Features
#### Graphical primitives
 * Disc
 * Infinite plane
 * Sphere
 * Triangle

#### Model formats
 * OBJ

#### Output formats
 * PNG
 * PPM
 * RGBE (HDR)

#### Optimizations
 * x86 SIMD support 
 * multi-threaded execution

## Build
### Compilation options
##### USE_SSE
In case this macro is defined, a source code containing the x86
optimization routines will be included during the compilation process.

##### USE_PNG
In case this macro is defined, a source code containing the `libpng` routines
used to store the rendered images to the disk will be included during the
compilation process.

### Ninja build system
```
$ ninja
```

## Directories
##### `bin`
The final raytracer binary `svit` is stored here.

##### `doc`
Documentation in Markdown form is stored here.

##### `img`
Example images accumulated during testing features are stored here.

##### `obj`
Intermediate object files produced during build are stored here.

##### `src`
Source files for the raytracer are stored here.

## Dependencies
#### libpng >= 1.6.16
This depedency can be removed by removing the `-lpng` and `-DUSE_PNG` options
from the compilation variables in the `build.ninja` file.

## Supported operating systems and compilers
 * FreeBSD 10.0 with clang 3.3

It is important to note that other systems are highly likely to work too and
just were not tested. Any porting work is welcome. The source code is written
with portability in mind and majority of the port-related changes should appear
in the build file only.

## License
2-clause BSD, see the [full license](LICENSE.md) for more information.

## Author
Daniel Lovasko lovasko@freebsd.org

