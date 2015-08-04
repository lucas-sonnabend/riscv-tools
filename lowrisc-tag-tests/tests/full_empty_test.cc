#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *multbytwo(int* location) {
	int value = *location;
	*location = 2 * value;
	return NULL;
}

int main(int argc, char** argv) {

	int shared_mem_length = 4;
	int i;
	pthread_t double_thread;
	int *shared_mem = (int *) malloc(shared_mem_length * sizeof(int));
	if(!shared_mem) {
		fprintf(stderr, "Could not allocate enough memory. Terminate.");
		return -1;
	}
	if(pthread_create(&double_thread, NULL, multbytwo, shared_mem)) {
		fprintf(stderr, "Could not create thread\n");
		return -2;
	}

	// print shared memory
	printf("Result: [");
	for (i=0 ; i< shared_mem_length;i++) {
		printf("%d, ", &(shared_mem+i));
	}
	printf("]\n");
	

}
