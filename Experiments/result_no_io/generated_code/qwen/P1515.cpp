#include <stdio.h>
#include <stdlib.h>

#define MAX_DISTANCE 7000
#define MAX_HOTELS 20

int main() {
    int A, B;
    scanf("%d %d", &A, &B);
    int N;
    scanf("%d", &N);

    int hotels[MAX_HOTELS + 1];
    hotels[0] = 0;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &hotels[i]);
    }

    int dp[MAX_DISTANCE + 1][MAX_DISTANCE + 1];
    for (int i = 0; i <= MAX_DISTANCE; i++) {
        for (int j = 0; j <= MAX_DISTANCE; j++) {
            dp[i][j] = 0;
        }
    }

    dp[0][0] = 1;

    for (int i = 1; i <= N + 1; i++) {
        for (int j = 0; j <= MAX_DISTANCE; j++) {
            for (int k = 0; k <= MAX_DISTANCE; k++) {
                if (k >= hotels[i - 1] && k - hotels[i - 1] >= A && k - hotels[i - 1] <= B) {
                    dp[j][k] += dp[j][hote