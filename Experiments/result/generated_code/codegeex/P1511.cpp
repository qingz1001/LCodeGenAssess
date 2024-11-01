#include <stdio.h>
#include <string.h>

int main() {
    char A[201];
    scanf("%s", A);
    int lenA = strlen(A);

    int k = 1; // Start searching from the first position in the sequence S
    int i = 0; // Index for the current digit in the sequence A

    while (i < lenA) {
        if (k % 10 == A[i] - '0') {
            k++; // Move to the next digit in the sequence S
            i++; // Move to the next digit in the sequence A
        } else {
            k++; // Move to the next digit in the sequence S
        }
    }

    printf("%d\n", k - lenA); // The position where the sequence A first appears in S

    return 0;
}