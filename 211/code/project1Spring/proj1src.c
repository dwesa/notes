// This program aims to comply with the parameters set by the following pdf
// http://www.cs.uic.edu/pub/CS211/ProjectsS15/proj1s15.pdf
// More specifically this is to sarisfy the requirements of project 1
// for the class CS211 at UIC for the spring semester of 2015

// Dale Wesa
// UIN: 676019303
// CS211 spring 2015

#include <stdio.h>
#include <stdlib.h>

//             ARRAY UTILS                 
int* copyArray (int size, int* originalArray) {
	int* newArray = calloc(size, sizeof(int));

	for ( int i=0; i<size; i++ ) {
		newArray[i] = originalArray[i];
	} 
	return newArray;
}

void printArr (int size, int* arr){

	for( int i=0; i<size; i++)
		printf("%d\n", arr[i]);
}
/////////////////////////////////////////////

// needed for use with qsort
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

// a linear search function. returns a pointer to an array whos first int is either the slot it found the searched for 
// number, or -1 if it was never found, and the second integer is the number of comparasins made
int* linSearch (int* arr, int size, int searchingFor) {
	int found = 0;
	int* retVals = calloc(2, sizeof(int));
	int i = 0;
	int comparasins = 0;

	while( i<size ) {
		
		if(arr[i] == searchingFor) {
			comparasins++;
			retVals[0] = i;
			retVals[1] = comparasins;
			found = 1;
			return retVals;
		}
		else {
			comparasins++;
			i++;
		}
	}
	retVals[0] = -1;
	retVals[1] = comparasins;

	return retVals;
}


// binary search alg
int* binSearch(int* array, int size, int searchValue) {
	int comparasins = 0;
	int low = 0;
    int high = size - 1;
 	int* retVals = calloc(2, sizeof(int));
    int mid;
 
    while (low <= high)
    {	comparasins++;
        mid = (low + high) / 2;
 
        if(searchValue == array[mid])
        {	comparasins++;
        	retVals[0] = mid;
        	retVals[1] = comparasins;
            return retVals;
        }
        else if (searchValue > array[mid])
        {	comparasins++;
            low = mid + 1;
        }
        else
        {	comparasins++;
            high = mid - 1;
        }
    }

    // at this point, nothing has been found so we should return a -1 value
	retVals[0] = -1;
	retVals[1] = comparasins;
    return retVals;
}

 



// reads in values to a dynamic array, whether it be for sorting, or a list of values to search for
int* read(int* array, int* size) {
 	 int val;
	 int index = 0;

	 scanf("%d", &val);
     while( val != -999)
     {       
        // resize the array with realloc for one more int
        // note that on the first pass, it will reallocate to the same size (1)
		(*size)++;
    	array = realloc(array, (*size) * sizeof(int));	 
    	// store the value in the last (new) spot we made
		array[index] = val;	
		index++;	 
		// read in another integer
		scanf("%d", &val);
     }
	return array;
}


int main() {
	// initialize our variables, including a pointer to the beginning of
	// the array of input integers. 
	// note its size will change as we input more and more numbers

	// we allocate one space for the first integer to be entered into
	int* arr = calloc(1, sizeof(int));
	int* arrCopy;
	int size = 0;
	int searchValsSize = 0;
	int* searchVals = calloc(1, sizeof(int));

	printf("enter numbers to fill an array, entering -999 when finished \n");
	arr = read(arr, &size);
	

	arrCopy = copyArray(size, arr);

	qsort(arrCopy, size, sizeof(int), cmpfunc);

	printf("\nYour array: \n");
	printArr(size, arr);
	printf("\nYour array sorted: \n");
	printArr(size, arrCopy);

	printf("\nEnter a value to search for\n");
	searchVals = read(searchVals, &searchValsSize); 
		


	// for each search value, we pass the value to the search function and report how long it took and where it was
	printf("\nLinear Search Results: \n");
	for(int i =0; i<searchValsSize; i++){

		int* found = linSearch(arr, size, searchVals[i]);

		if(found[0] != -1)
			printf("found %d at position %d by making %d comparasins\n", searchVals[i], found[0], found[1]);
		else
			printf("Did not find %d by making %d comparasins\n", searchVals[i], found[1]);
	}		

	// same thing as before, only now we use the sorted array to search through each time
	printf("\nBinary Search Results: \n");
	for(int i =0; i<searchValsSize; i++){
 
                 int* found = binSearch(arrCopy, size, searchVals[i]);
 
                 if(found[0] != -1)
                         printf("found %d at position %d by making %d comparasins\n", searchVals[i], found[0], found[1]);
                 else
                         printf("Did not find %d by making %d comparasins\n", searchVals[i], found[1]);
         }


	
        return 0;
}
