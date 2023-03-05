# Function Task Control

## Benchmark

Comparing two methods, dynamic library and creating new process, to run the new function task.
The dynamic library method is a little bit faster. Here is the numbers:
> The programs are located at `tests/benchmark`. Run `make` to get the number.

```
# log-dl-fork-2023-03-05
dl: 0.031179 seconds
Fork: 0.036710 seconds
```

## For MacOS

```
DYLD_LIBRARY_PATH=./lib ./ftc
```
