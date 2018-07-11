CFLAGS += -DENABLE_TRACING

# Uncomming the following if you would like to bypass the write function in
# your C library. This only works on x86_64.

#CFLAGS += -DUSE_DIRECT_WRITE

all: trace-marker-example

trace-marker-example: trace-marker-example.c trace-marker.c
	$(CC) $(CFLAGS) -o $@ $^


clean:
	@rm -fr *.o trace-marker-example
