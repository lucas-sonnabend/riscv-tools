#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <env/full_empty.h>

void *double_value(void *slot) {
	//int value = *(int *)slot;
	long value = load_when_full(slot);
	long *next_slot = ((long *)slot) + 1;
	
	//*next_slot = value*2;
	store_and_set_full((void *)next_slot, value*2);
	printf("slot 1: %lx, slot 2: %lx\n", slot, next_slot);
}

main()
{
	pthread_t thread1, thread2;
	int  iret1, iret2;
	long result, pipelineSize = 3;
	long *pipeline = (long *)malloc(sizeof(long) * pipelineSize);
	if(pipeline == NULL) {
		 fprintf(stderr, "Error - could not allocate enough memory");
	}

	setup_exceptions();
 	//pipeline[0] = 1;
	store_and_set_full(pipeline, 1);
	printf("pipeline initialised with %d at 0x%lx\n", pipeline[0], pipeline);

	iret1 = pthread_create( &thread1, NULL, double_value, (void *)pipeline);
	if(iret1) {
	     fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
	     exit(EXIT_FAILURE);
	}
	//pthread_join(thread1, NULL);

	iret2 = pthread_create( &thread2, NULL, double_value, (void*) (pipeline+1));
	if(iret2) {
	    fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
	    exit(EXIT_FAILURE);
	}
	
	//pthread_join( thread1, NULL);
	//pthread_join( thread2, NULL);
	//result = pipeline[pipelineSize-1];
	result = load_when_full((void *) (pipeline+pipelineSize-1));
	printf("result: %d at last pipeline slot 0x%lx\n", result, pipeline+(pipelineSize-1));

	exit(EXIT_SUCCESS);
}
