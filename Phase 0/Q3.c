#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define THREAD_NUMBER 5

void *stupid(void *ptr);
char *id_to_string(int thread_number);
main()
{
	pthread_t p[THREAD_NUMBER];
	char *argument;
	int i = 0;
	for(i = 0; i < THREAD_NUMBER; i++)
    {
		argument = id_to_string(i+1);
		pthread_create( &p[i], NULL, stupid, (void *)argument);
		clock_t begin = clock();
		//while(((long int)(clock() - begin) / CLOCKS_PER_SEC) < 2){;}
	}
	printf("End Process\n");
	exit(0);
}
char* id_to_string(int thread_id)
{
	static char temp_str[1000];
	snprintf(temp_str, 1000, "(%d)", thread_id);
	return temp_str;
}
void *stupid(void *message)
{
	printf("Start Job: %s %ld\n", (char *)message, pthread_self());
	clock_t begin = clock();
	//while( (long int)(clock() - begin) / CLOCKS_PER_SEC < 1){;}
	printf("End Job: %s %ld\n", (char *)message, pthread_self());
}
