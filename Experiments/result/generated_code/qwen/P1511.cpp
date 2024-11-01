#include <stdio.h>
#include <string.h>

#define MAX_LEN 201

int main() {
    char A[MAX_LEN];
    scanf("%s", A);
    int len_A = strlen(A);

    long long S = 0;
    int k = 0;

    while (1) {
        S *= 10;
        for (int i = 1; i <= 10; i++) {
            S += i;
            if (strlen(A) == k + i && strncmp(&A[k], &S - i * 10 + i, i) == 0) {
                printf("%d\n", S - i * 10 + i);
                return 0;
            }
        }
        k++;
    }

    return 0;
}