#include <stdio.h>
#include <stdlib.h>
#include <time.h> // time
#define EMPTY_FRAME -1
//stack

int* generate_ref_arr(size_t sz, size_t page_max);
int lru(int* ref_arr, size_t ref_arr_sz, size_t frame_sz, int page_max);

int _contains(int* arr, size_t sz, int target);
int _findlru(int* frames, size_t sz, int num, int* stack, int page_max);
void _stack( int* stack, int page_max, int num );

// Driver code
//  Usage: ./program {ref_arr_size} {page_max} {frame_size}
int main(/*int argc, char** argv*/) {
    //if (argc < 4) return -1;
    
    //int ref_arr_sz = atoi(argv[1]);
    //int page_max = atoi(argv[2]);
    //int frame_sz = atoi(argv[3]);
	

    //int* ref = generate_ref_arr(ref_arr_sz, page_max);
	int ref[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
	int ref_arr_sz = sizeof(ref) / sizeof(int);
	int page_max=8;
	int frame_sz=4;
	
    int page_faults = lru(ref, ref_arr_sz, frame_sz, page_max);
    printf("%d\n", page_faults);
   // free(ref);

    return 0;
}

int* generate_ref_arr(size_t sz, size_t page_max) {
    int* ref_arr = (int*) malloc(sizeof(int) * sz);
	
	// TODO :: Generate Random Refernece String
	srand( time(NULL));
    
	for(int i=0; i<sz; i++)
	{
		ref_arr[i]=rand() % (page_max);
	}

    return ref_arr;
}

int lru(int* ref_arr, size_t ref_arr_sz, size_t frame_sz, int page_max) {
    int i, j;
    int page_faults = 0;
	int is_fault, target;
    
    // Initializing frames
    int* frames = (int*) malloc(sizeof(int) * frame_sz);
    for (i=0; i<frame_sz; i++) frames[i] = -1;
	//Initializing stack
	int* stack = (int*) malloc(sizeof(int)*page_max);
	for (i=0; i<page_max; i++) stack[i] = -1;
	
    // TODO
	
	 // Iterating reference string
	 for (i=0; i<ref_arr_sz; i++) {
        is_fault = _contains(frames, frame_sz, ref_arr[i]);

        // Miss (page fault occurred)
        if (is_fault == -1) {
			target=_contains(frames, frame_sz, -1);
			if (target!=-1) // there is an empty frame
				frames[target]=ref_arr[i];
			else//there is no empty frame
			{
				target = _contains(frames, frame_sz,_findlru(frames, frame_sz, ref_arr[i], stack, page_max));
				frames[target]=ref_arr[i];
			}
			page_faults++;
        }
		_stack(stack, page_max, ref_arr[i]);

        // Printing current states of frames
        printf("%d | ", ref_arr[i]);
        for(j=0; j<frame_sz; j++) {
            if (frames[j] == EMPTY_FRAME) printf(". ");
            else printf("%d ", frames[j]);
        }
		
		//stack 출력
		for(int u=0;u<page_max;u++)
		{
			if (stack[u]!=-1)
				printf("%d",stack[u]);
			else
				printf("n");//n means null
		}
		printf(" ");
		
        if (is_fault == -1) printf("(fault)");
        printf("\n");
    }
	
	free(frames);
	free(stack);

    return page_faults;
}

int _contains(int* arr, size_t sz, int target) {
    int i = 0;
    for (i=0; i<sz; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

int _findlru(int* frames, size_t sz, int num, int* stack, int page_max)
{
	int result;
	int i = page_max-1;
	while(result == -1 ){
		result=stack[i];
		i--;
		
	}
	while (_contains(frames, sz, result) ==-1)
	{
		result=stack[i];
		i--;
	}
			
	return result;
}


void _stack( int* stack, int page_max, int num ) { 
	
	
	//stack 수정
	int j = _contains(stack, page_max, num);
	if ( j == -1)
		j=page_max-1;
	memmove(stack+1, stack, j*sizeof(int));
	stack[0]=num;
	
}
