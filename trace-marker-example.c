#include <stdio.h>
#include <string.h>

extern void test_function(int);

int main(int argc, char *argv[])
{
	int i;
	int rc;

	for (i = 0; i < 10; ++i) {
		test_function(i);
	}

	printf("Hello World!\n");
}
