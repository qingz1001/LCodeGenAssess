#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    int row = 1;
    while (N > row) {
        N -= row;
        row++;
    }
    
    int numerator, denominator;
    if (row % 2 == 0) {
        numerator = N;
        denominator = row - N + 1;
    } else {
        numerator = row - N + 1;
        denominator = N;
    }
    
    printf("%d/%d\n", numerator, denominator);
    
    return 0;
}