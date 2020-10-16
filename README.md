# casm-utilities-template
This is a small example of how you can write a plugin that will get tacked onto the build of [`casm-utilities`](https://github.com/goirijo/casm-utilities).
Only one file in here really matters: `Makesocket.am`.
This is the the segment that will connect with the rest of the build.
You can link against `libcasmutils.la` for all the `casm-utilities` functions and classes, and use `libgtests` for your tests.

## Automake directives
The plugin will be compiled as if it was part of the `casm-utilities` repository, which allows you to link against anything defined in that repository.
This also means that all the paths you use need to be relative to that repository.
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
_casmutils_hello_LDADD = libcasmutils.la
```
