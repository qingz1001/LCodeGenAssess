#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200000
#define MAX_M 100000

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int *photos = (int *)malloc((M + 1) * sizeof(int));
    for (int i = 1; i <= M; i++) {
        scanf("%d %d", &photos[2 * i - 1], &photos[2 * i]);
    }

    // Find the minimum and maximum positions covered by any photo
    int min_pos = photos[1];
    int max_pos = photos[2];
    for (int i = 2; i <= M; i++) {
        if (photos[2 * i - 1] < min_pos) min_pos = photos[2 * i - 1];
        if (photos[2 * i] > max_pos) max_pos = photos[2 * i];
    }

    // If the total length covered by all photos is less than N, it's impossible
    if (max_pos - min_pos + 1 < N) {
        printf("-1\n");
        free(photos);
        return 0;
    }

    // Calculate the maximum number of spotted cows
    int max_spotted_cows = 0;
    for (int i = 1; i <= M; i++) {
        int start = photos[2 * i - 1];
        int end = photos[2 * i];
        int length = end - start + 1;

        // Each photo must contain exactly one spotted cow
        if (length == 1) {
            max_spotted_cows++;
        } else {
            // For each photo with more than one cow, we can place a spotted cow at either end
            max_spotted_cows += 2;
        }
    }

    // Since each spotted cow can be shared between multiple photos,
    // we need to ensure that we don't double-count
    max_spotted_cows = (max_spotted_cows + 1) / 2;

    printf("%d\n", max_spotted_cows);

    free(photos);
    return 0;
}