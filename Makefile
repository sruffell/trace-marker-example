CFLAGS += -DENABLE_TRACING

all: trace-marker-example

trace-marker-example: trace-marker-example.c libtest-library.so
	$(CC) -o $@ trace-marker-example.c libtest-library.so

libtest-library.so: test-library.c trace-marker.c
	$(CC) -shared $(CFLAGS) -o libtest-library.so test-library.c trace-marker.c

clean:
	@rm -fr *.o trace-marker-example libtest-library.so
