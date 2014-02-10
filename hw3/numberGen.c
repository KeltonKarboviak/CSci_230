#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int rand_lim(int min, int max) {
/* return a random number between 0 and limit inclusive.
 */
	int number;
    number = ( rand() / ((double)RAND_MAX+1)) * (max-min+1) + min;
    return number;
}


int main(void) {
	FILE *outFile;

	srand(time(NULL));
	int i, k, nums;
	int number, total = 0, size = 0;
	for (i = 0; i < 3; i++) {
		if (i == 0) {
			outFile = fopen("list0.txt", "w");
			nums = 1000;
		} else if (i == 1) {
			outFile = fopen("list1.txt", "w");
			nums = 1000;
		} else {
			outFile = fopen("list2.txt", "w");
			nums = 1000;
		}


		for (k = 0; k < nums; k++) {
			number = rand_lim(1,1000);
			total += number;
			size++;
			fprintf(outFile, "%d\n", number);
		}

		fclose(outFile);
	}

	printf("Average: %d\n", total/size);


	return 0;
}