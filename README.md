# casm-utilities-template
This is a small example of how you can write a plugin that will get tacked onto the build of [`casm-utilities`](https://github.com/goirijo/casm-utilities).
Only one file in here really matters: `Makesocket.am`.
This is the the segment that will connect with the rest of the build.
You can link against `libcasmutils.la` for all the `casm-utilities` functions and classes, and use `libgtests` for your tests.
