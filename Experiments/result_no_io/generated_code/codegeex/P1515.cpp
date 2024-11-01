#include <stdio.h>
#include <stdlib.h>

#define MAX_HOTELS 100
#define MAX_DISTANCE 7000

int main() {
    int A, B, N;
    scanf("%d %d %d", &A, &B, &N);

    int hotels[MAX_HOTELS + 1];
    hotels[0] = 0;
    hotels[1] = 990;
    hotels[2] = 1010;
    hotels[3] = 1970;
    hotels[4] = 2030;
    hotels[5] = 2940;
    hotels[6] = 3060;
    hotels[7] = 3930;
    hotels[8] = 4060;
    hotels[9] = 4970;
    hotels[10] = 5030;
    hotels[11] = 5990;
    hotels[12] = 6010;
    hotels[13] = 7000;

    int total_hotels = 14;

    for (int i = 0; i < N; i++) {
        int m;
        scanf("%d", &m);
        hotels[total_hotels++] = m;
    }

    // Sort the hotels array
    for (int i = 0; i < total_hotels - 1; i++) {
        for (int j = 0; j < total_hotels - i - 1; j++) {
            if (hotels[j] > hotels[j + 1]) {
                int temp = hotels[j];
                hotels[j] = hotels[j + 1];
                hotels[j + 1] = temp;
            }
        }
    }

    // Dynamic programming to count the number of ways
    long long ways[MAX_HOTELS + 1][MAX_DISTANCE + 1];
    for (int i = 0; i <= total_hotels; i++) {
        for (int j = 0; j <= MAX_DISTANCE; j++) {
            ways[i][j] = 0;
        }
    }

    ways[0][0] = 1;

    for (int i = 1; i <= total_hotels; i++) {
        for (int j = 0; j <= MAX_DISTANCE; j++) {
            for (int k = 0; k < i; k++) {
                if (hotels[i] - hotels[k] >= A && hotels[i] - hotels[k] <= B) {
                    ways[i][hotels[i]] += ways[k][j];
                }
            }
        }
    }

    long long total_ways = 0;
    for (int i = 0; i <= total_hotels; i++) {
        total_ways += ways[i][MAX_DISTANCE];
    }

    printf("%lld\n", total_ways);

    return 0;
}