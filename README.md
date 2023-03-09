# Function-grained Task Control

Function-grained Task Control (FTC) is the small FaaS framework. It uses the dynamic library to run the task instead of creating the new process to avoid the overhead.

## How to use

ftc is based on the `mthpc` library. To build the program, first you have to go to the `lib` directory and run:

```bash
bash build-mthpc.sh
```

You can also see the current version of `mthpc` library at `lib/current_mthpc_version`.
After that, in root directory, run the command:

```bash
make
```

Then execute the binary program, `ftc`, with following paramters.

- `CC`:
	- The compiler to compile the function-graned task.
- `CFLAGS`:
	- The flags passed to the `CC` compiler.

Finally, it will create the file, `set_ftc_source_code`. You can pass the **absolute path** of the source code you want to execute. For example:

```bash
echo "/path/to/src_code" > set_ftc_source_code
```

### Function task

To use the FTC API, include the header `include/uapi/ftc.h`.
For client side, the enter point is `FTC_ENTER_POINT(name)` function.
The function protoype type of the enter point is `void name (void)`.
So if you want to execute the function codes by ftc, the enter point would be like:

```cpp
#include "include/uapi/ftc.h"

FTC_ENTER_POINT(name) {
    // Do what you want...
}
```

## Log message

At server side, ftc also provide the log message, here is the example:

```
[1678294046.320238] init: Transfer iniitization
[1678294046.320358] transfer: input file: 
[1678294046.320366] transfer: compiler: gcc
[1678294046.320372] transfer: cflags: -Wall -O2
[1678294077.086624] transfer: file event: set_source_code
[1678294077.086688] transfer: Read set_ftc_source_code: /path/to/src/user.c
[1678294077.086704] transfer: Build: /path/to/src/user.c.so
/path/to/src/user.c.so executed 48.000000 ns
^C[1678294079.851142] signal: Exiting the program...
[1678294079.851173] signal: Cleanup the settings...
```

## Benchmark

Comparing two methods, dynamic library and creating new process, to run the new function task.
The dynamic library method is a little bit faster. Here is the numbers:
> The programs are located at `tests/benchmark`. Run `make` to get the number.

```
# log-dl-fork-2023-03-05
dl: 0.031179 seconds
Fork: 0.036710 seconds
```

## For MacOS (NOT SUPPORT YET)

```
DYLD_LIBRARY_PATH=./lib ./ftc
```
