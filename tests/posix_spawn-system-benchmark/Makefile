FILE=log-posix_spawn-system-$(shell date +"%Y-%m-%d")
LOG_FILE=logs/$(FILE)

all:
	touch $(LOG_FILE)
	gcc -o compile_benchmark compile_benchmark.c -Wall -O2
	./compile_benchmark >> $(LOG_FILE)
	cat $(LOG_FILE)
	rm -f compile_benchmark test

clean:
	rm -f compile_benchmark test
