# casm-utilities-template
This is a small example of how you can write a plugin that will get tacked onto the build of [`casm-utilities`](https://github.com/goirijo/casm-utilities).
Only one file in here really matters: `Makesocket.am`.
This is the the segment that will connect with the rest of the build.
You can link against `libcasmutils.la` for all the `casm-utilities` functions and classes, and use `libgtests` for your tests.

## Automake directives
The plugin will be compiled as if it was part of the `casm-utilities` repository, which allows you to link against anything defined in that repository.
This also means that all the paths you use need to be relative to that repository.
You can extend the compilation with basically any automake feature, including binaries, scripts, headers and libraries.

## Basic binary script (c++)
This section will cover the minimum amount of entries you'll need to make a binary compile as a plugin.

### bin_PROGRAMS
This specifies the name of your binary once it gets installed on your system.
You can call your binary anything you want, but if you want it to be detected by `casmutils`, you must follow a particular format.
`casmutils` scans your `PATH` to detect which plugins have been installed.
The way it does this is by searching for the pattern `_casmutils-*`.
For the example in this repo, we've set

```
bin_PROGRAMS += _casmutils-hello
```

This will result in a binary called `_casmutils-hello` to be installed, which you can call directly, or by calling `casmutils hello`.

### *_SOURCES
Use this to specify what the necessary source files for your program are.
The complete name is determined by the value you gave to `bin_PROGRAMS`.
Simply prepend the name of your program to `_SOURCES`, and give it a list of source files.
If the name in your program has dash characters (`-`), replace them with underscores (`_`):

```
bin_PROGRAMS += _casmutils-hello
_casmutils_hello_SOURCES = plugins/casm-utilities-plugin/src/hello.cpp
```
Note that the path is relative to the root of the `casm-utilities` repository.
You can specify multiple files separated by spaces, or on several lines, escaping with `\`.

### *_LDADD
This will specify which libraries your program needs to link against.
If you're using features in `casm-utilities`, you'll need to link it against `libcasmutils.la`.
For more complicated programs you might be writing, you can create your own libraries to link against as well.
As before, prepend with the name of your program for the full variable name.

```
bin_PROGRAMS += _casmutils-hello
_casmutils_hello_SOURCES = plugins/casm-utilities-plugin/src/hello.cpp
_casmutils_hello_LDADD = libcasmutils.la
```

## Installing additional header files
If your plugin is expanding on the `casmutils` library, you may have some headers you'd like to be installed alongside the parent repository.

### *_includedir
First you must decide where the path where your headers should go.
This will define what the `#include` directive will look like for the user.
Suppose you've created a new symmetry related header called `extension.hpp`, which should be included via `#include <casmutils/sym/extension.hpp>`.
The `*_includedir` value is `$(includedir)/casmutils/sym`.

Create a descriptive variable name, and add it to your `Makesocket.am` file:
```
casmutils_plugin_includedir=$(includedir)/casmutils/sym
```
It's very important to choose a name that won't collide with other plugins, so definitely *don't* steal this variable name.
Come up with one that makes sense for your repository name.

### *include_HEADERS
Now you're ready to specify which headers should be installed.
As we said before, we have a header called `extension.hpp`, we specify that we want that installed now:
```
casmutils_plugin_includedir=$(includedir)/casmutils/sym
casmutils_plugin_include_HEADERS = plugins/casm-utilities-plugin/include/casmutils/sym/extension.hpp
```

Note that the variable names of `*includedir` and `*include_HEADERS` must have the same prefix.
You should always store your headers in an `include` directory which mirrors the final post installation layout.

### CASMUTILS_LIBRARY
The parent `casm-utilities` library has a switch for disabling header installation, which you should follow as well.
Wrap the segment we just wrote in the `CASMUTILS_LIBRARY` conditional:
```
if CASMUTILS_LIBRARY
casmutils_plugin_includedir=$(includedir)/casmutils/sym
casmutils_plugin_include_HEADERS = plugins/casm-utilities-plugin/include/casmutils/sym/extension.hpp
endif
```
Do not indent the `if` statement.

## Extending libcasmutils
Unless your library module is header only, you will also have sources that you need to compile, and should be linked together with the resto of `libcasmutils`.
This example will cover how to compile `extension.cxx`, which relies on the `extension.hpp` header.
Paths to these files relative to the plugin root are as follows:

### libcasmutils_la_SOURCES
You can simply tack on the `extensions.cxx` file as an additional source file in your `Makesocket.am`:
```
libcasmutils_la_SOURCES +=\
                              plugins/casm-utilities-plugin/include/casmutils/sym/extension.hpp\
                              plugins/casm-utilities-plugin/lib/extension.cxx
```
You shoud include both the source and header file.

### AM_CPPFLAGS
An issue you might encounter is how to specify the location of `extension.hpp` within the `extension.cxx` file.
The simplest approach is to just use the relative path:
```
#include "../include/casmutils/sym/extension.hpp"
```

If you have a nicely organized `include` directory (you should), you can make use `AM_CPPFLAGS` to make the directive more general:
```
#include <casmutils/sym/extension.hpp>
```
This is especially desirable for cases where you intend to distribute the headers.

In order for this to work, specify the path to your `include` directory as an additional place to search:
```
AM_CPPFLAGS += -I$(srcdir)/plugins/casm-utilities-plugin/include
```
