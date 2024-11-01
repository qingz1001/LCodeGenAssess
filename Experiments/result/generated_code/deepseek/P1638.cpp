#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000
#define MAXM 2000

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int paintings[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &paintings[i]);
    }

    int count[MAXM + 1] = {0};
    int unique_count = 0;
    int left = 0, right = 0;
    int min_length = n + 1;
    int best_left = 0, best_right = 0;

    while (right < n) {
        if (count[paintings[right]] == 0) {
            unique_count++;
        }
        count[paintings[right]]++;

        while (unique_count == m) {
            if (right - left + 1 < min_length) {
                min_length = right - left + 1;
                best_left = left;
                best_right = right;
            }
            count[paintings[left]]--;
            if (count[paintings[left]] == 0) {
                unique_count--;
            }
            left++;
        }
        right++;
    }

    printf("%d %d\n", best_left + 1, best_right + 1);

    return 0;
}