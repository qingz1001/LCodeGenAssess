#include <stdio.h>
#include <string.h>

#define MAX_LEN 10001
#define MAX_SUBSTRINGS 5

int T;
char A[MAX_LEN];
int N;
char substrings[MAX_SUBSTRINGS][MAX_LEN];
int maxans, minans;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%s", A);
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%s", substrings[i]);
        }

        // Initialize minans and maxans
        minans = strlen(A);
        maxans = 0;

        // Calculate the minimum and maximum coverage
        // Here you would implement the logic to calculate minans and maxans
        // This part is left as an exercise

        printf("%d %d\n", minans, maxans);
    }
    return 0;
}