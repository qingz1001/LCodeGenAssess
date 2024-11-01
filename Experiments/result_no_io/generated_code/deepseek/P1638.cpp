#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 1000000
#define MAXM 2000

int paintings[MAXN];
int count[MAXM + 1];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &paintings[i]);
    }

    int left = 0, right = 0;
    int unique_count = 0;
    int min_length = n + 1;
    int best_left = 0, best_right = 0;

    while (right < n) {
        if (count[paintings[right]] == 0) {
            unique_count++;
        }
        count[paintings[right]]++;
        right++;

        while (unique_count == m) {
            if (right - left < min_length) {
                min_length = right - left;
                best_left = left;
                best_right = right - 1;
            }
            count[paintings[left]]--;
            if (count[paintings[left]] == 0) {
                unique_count--;
            }
            left++;
        }
    }

    printf("%d %d\n", best_left + 1, best_right + 1);

    return 0;
}