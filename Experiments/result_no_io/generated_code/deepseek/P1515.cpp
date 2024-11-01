#include <stdio.h>
#include <stdlib.h>

#define MAX_MOTELS 34

int motels[MAX_MOTELS] = {0, 990, 1010, 1970, 2030, 2940, 3060, 3930, 4060, 4970, 5030, 5990, 6010, 7000};
int num_motels = 14;

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int count_ways(int A, int B) {
    int dp[MAX_MOTELS] = {0};
    dp[0] = 1;

    for (int i = 1; i < num_motels; i++) {
        for (int j = 0; j < i; j++) {
            if (motels[i] - motels[j] >= A && motels[i] - motels[j] <= B) {
                dp[i] += dp[j];
            }
        }
    }

    return dp[num_motels - 1];
}

int main() {
    int A, B, N;
    scanf("%d", &A);
    scanf("%d", &B);
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int new_motel;
        scanf("%d", &new_motel);
        motels[num_motels++] = new_motel;
    }

    qsort(motels, num_motels, sizeof(int), compare);

    int result = count_ways(A, B);
    printf("%d\n", result);

    return 0;
}