#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HOTELS 40
#define MAX_DISTANCE 7000

int hotels[MAX_HOTELS];
int hotel_count;
int A, B;
long long dp[MAX_HOTELS];

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

long long count_travel_plans() {
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int i = 1; i < hotel_count; i++) {
        for (int j = 0; j < i; j++) {
            int distance = hotels[i] - hotels[j];
            if (distance >= A && distance <= B) {
                dp[i] += dp[j];
            }
        }
    }

    return dp[hotel_count - 1];
}

int main() {
    scanf("%d", &A);
    scanf("%d", &B);

    int N;
    scanf("%d", &N);

    int default_hotels[] = {0, 990, 1010, 1970, 2030, 2940, 3060, 3930, 4060, 4970, 5030, 5990, 6010, 7000};
    hotel_count = sizeof(default_hotels) / sizeof(default_hotels[0]);

    for (int i = 0; i < hotel_count; i++) {
        hotels[i] = default_hotels[i];
    }

    for (int i = 0; i < N; i++) {
        scanf("%d", &hotels[hotel_count]);
        hotel_count++;
    }

    qsort(hotels, hotel_count, sizeof(int), compare);

    long long result = count_travel_plans();
    printf("%lld\n", result);

    return 0;
}