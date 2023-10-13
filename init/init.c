#include <stdio.h>
#include <unistd.h>

int main(int argc, char**argv) {

#ifndef PLEASE_PANIC
	while(1)
#endif
	{
		for(int i=0; i<10; i++){
			printf("Hello, World! - %d\n", i);
		}

#ifndef PLEASE_PANIC
		printf("...and again!\n");
		sleep(3);
#endif
	}

	return 0;
}
