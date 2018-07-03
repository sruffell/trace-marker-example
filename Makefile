CFLAGS += -DENABLE_TRACING

all: trace-marker-example

trace-marker-example: trace-marker-example.c trace-marker.c
	$(CC) $(CFLAGS) -o $@ $^


clean:
	@rm -fr *.o trace-marker-example
