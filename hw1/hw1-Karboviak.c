/*
 * File:   hw1-Karboviak.c
 * Author: Kelton Karboviak
 */

#include <stdio.h>


// Calculates and returns a single month's interest using the formulas provided
double calculateInterest(double r, double B, double P, double balance) {
	double interest;
	interest = (r / 12) * balance;

	return interest;
}


// Takes all of the variables to create the output table
void outputToTable(double rate, double borrowed, double payment) {
	printf("\nr = %.2lf\nB = %.2lf\nP = %.2lf \n\n", rate, borrowed, payment); // Prints original info.

	double balance = borrowed;
	double interest = 0, totalI = 0;
	int month = 1;
	while (balance > 0) {
		interest = calculateInterest(rate, borrowed, payment, balance);
		totalI += interest;
		printf("%d %.2lf %.2lf\n", month, interest, balance);
		balance = (balance - payment) + interest;
		month++;

		if (balance <= 0) { // Prints pay-off point
			interest = calculateInterest(rate, borrowed, payment, balance);
			printf("%d %.2lf %.2lf\n", month, interest, balance);
		}
	}

	printf("\ntotal interest paid: $%.2lf\n\n", totalI);
}


int main(void) {
	double rate = .25, borrowed = 2000.0, payment;

	printf("\nEnter your monthly payment: ");
	scanf("%lf", &payment);
	outputToTable(rate, borrowed, payment);

 	return 0;
 }