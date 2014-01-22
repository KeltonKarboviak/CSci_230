/*
 * File:   hw1-Karboviak.c
 * Author: Kelton Karboviak
 */

#include <stdio.h>


float calculateInterest(float r, float B, float P, float balance) {
	float interest;
	if (balance == B) {
		interest = (r / 12) * B;
	} else {
		interest = (r / 12) * balance;
	}

	return interest;
}


void outputToTable(float rate, float borrowed, float payment) {
	printf("\nr = %.2f\nB = %.2f\nP = %.2f \n\n", rate, borrowed, payment);

	float balance = borrowed;
	float interest = 0, totalI = 0;
	int month = 1;
	while (balance > 0) {
		interest = calculateInterest(rate, borrowed, payment, balance);
		totalI += interest;
		printf("%d %.2f %.2f\n", month, interest, balance);
		balance = (balance - payment) + interest;
		month++;

		if (balance <= 0) { // Prints pay-off point
			interest = calculateInterest(rate, borrowed, payment, balance);
			printf("%d %.2f %.2f\n", month, interest, balance);
		}
	}

	printf("\ntotal interest paid: %.2f\n", totalI);
}


int main(void) {
	printf("\nEnter your monthly payment: ");

	float rate = .25, borrowed = 2000.0, payment;
	scanf("%f", &payment);
	outputToTable(rate, borrowed, payment);

 	return (0);
 }