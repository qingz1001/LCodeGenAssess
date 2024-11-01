#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HOTELS 35
#define TRAVEL_DISTANCE 7000

int hotels[MAX_HOTELS];
int num_hotels = 14;
int A, B;
long long dp[MAX_HOTELS];

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

long long count_plans() {
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int i = 1; i < num_hotels; i++) {
        for (int j = 0; j < i; j++) {
            int distance = hotels[i] - hotels[j];
            if (distance >= A && distance <= B) {
                dp[i] += dp[j];
            }
        }
    }

    return dp[num_hotels - 1];
}

int main() {
    int initial_hotels[] = {0, 990, 1010, 1970, 2030, 2940, 3060, 3930, 4060, 4970, 5030, 5990, 6010, 7000};
    memcpy(hotels, initial_hotels, sizeof(initial_hotels));

    scanf("%d", &A);
    scanf("%d", &B);

    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &hotels[num_hotels]);
        num_hotels++;
    }

    qsort(hotels, num_hotels, sizeof(int), compare);

    long long result = count_plans();
    printf("%lld\n", result);

    return 0;
}