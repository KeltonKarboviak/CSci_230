#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int randomNum = rand() % 100;
    printf("%d\n", randomNum);

    return 0;
}