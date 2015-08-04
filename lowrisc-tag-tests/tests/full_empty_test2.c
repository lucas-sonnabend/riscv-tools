#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int main(int argc, char** argv) {

	int shared_mem_length = 4;
	int i, childID;
	int *shared_mem = (int *) malloc(shared_mem_length * sizeof(int));
	if(!shared_mem) {
		fprintf(stderr, "Could not allocate enough memory. Terminate.");
		return -1;
	}


	

	// print shared memory
	printf("Result: [");
	for (i=0 ; i< shared_mem_length;i++) {
		printf("%d, ", &(shared_mem+i));
	}
	printf("]\n");
	

}
