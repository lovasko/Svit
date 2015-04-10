# Svit
Svit is an open-source CPU renderer that embraces modularity and distributivity
whilst supporting as many architectures and platforms as possible.

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

#### Acceleration structures
 * BVH (with tree cutting optimization)
 * kD-tree

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
Some of these directories do not exist in the repository but are created during
compilation or runtime.

##### `bin`
The final raytracer binary `svit` is stored here.

##### `doc`
Documentation in Markdown format.

##### `img`
Example images accumulated during testing features.

##### `mdl`
3D models for the test scenes.

##### `obj`
Intermediate object files produced during build.

##### `src`
Source code of the raytracer.

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

## Contributors
* Jakub Stasta

