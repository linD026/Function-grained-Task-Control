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
	- The flags pass to the `CC` compiler.

Finally, it will create the file, `set_ftc_source_code`. You can pass the **absolute path** of the source code you want to execute. For example:

```bash
echo "/path/to/src_code" > set_ftc_source_code
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
