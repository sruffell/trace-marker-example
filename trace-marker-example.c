#include <stdio.h>
#include <string.h>

#include "trace-marker.h"

static int test_function(int count)
{
	trace_printk("%s: Entering with count %d\n", __func__, count);
	
	trace_puts("Test\n");

	trace_printk("%s: Leaving\n", __func__);
}

int main(int argc, char *argv[])
{
	int i;
	int rc;

	rc = trace_marker_init();
	if (rc != 0) {
		fprintf(stderr, "Failed to open trace marker file: %s\n",
			strerror(rc));
	}

	for (i = 0; i < 10; ++i) {
		test_function(i);
	}

	printf("Hello World!\n");
}
