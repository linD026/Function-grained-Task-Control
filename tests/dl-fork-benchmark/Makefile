FILE=log-dl-fork-$(shell date +"%Y-%m-%d")
LOG_FILE=logs/$(FILE)

all:
	touch $(LOG_FILE)
	gcc -o dl dl.c -D'CURR_DIR="$(shell pwd)"' -Wall -O2 -Wno-unused-result
	gcc -o fork fork.c -D'CURR_DIR="$(shell pwd)"' -Wall -O2 -Wno-unused-result
	./dl >> $(LOG_FILE)
	./fork >> $(LOG_FILE)
	cat $(LOG_FILE)
	rm -f dl fork fork-user libuser.so

clean:
	rm -f dl fork fork-user libuser.so
