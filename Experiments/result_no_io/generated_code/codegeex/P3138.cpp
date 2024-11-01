#include <stdio.h>
#include <stdlib.h>

#define MAX_COORD 1000000

int main() {
    int N;
    scanf("%d", &N);

    int cow_count[MAX_COORD + 1][MAX_COORD + 1] = {0};

    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        cow_count[x][y]++;
    }

    int max_cows = 0;

    for (int a = 1; a <= MAX_COORD; a += 2) {
        for (int b = 1; b <= MAX_COORD; b += 2) {
            int top_left = 0, top_right = 0, bottom_left = 0, bottom_right = 0;

            for (int x = 1; x <= a; x += 2) {
                for (int y = 1; y <= b; y += 2) {
                    top_left += cow_count[x][y];
                }
            }

            for (int x = a + 2; x <= MAX_COORD; x += 2) {
                for (int y = 1; y <= b; y += 2) {
                    top_right += cow_count[x][y];
                }
            }

            for (int x = 1; x <= a; x += 2) {
                for (int y = b + 2; y <= MAX_COORD; y += 2) {
                    bottom_left += cow_count[x][y];
                }
            }

            for (int x = a + 2; x <= MAX_COORD; x += 2) {
                for (int y = b + 2; y <= MAX_COORD; y += 2) {
                    bottom_right += cow_count[x][y];
                }
            }

            int max_region = 0;
            max_region = (top_left > max_region) ? top_left : max_region;
            max_region = (top_right > max_region) ? top_right : max_region;
            max_region = (bottom_left > max_region) ? bottom_left : max_region;
            max_region = (bottom_right > max_region) ? bottom_right : max_region;

            if (max_cows < max_region) {
                max_cows = max_region;
            }
        }
    }

    printf("%d\n", max_cows);

    return 0;
}