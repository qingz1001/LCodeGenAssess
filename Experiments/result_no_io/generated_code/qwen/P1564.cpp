#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int count[3] = {0};
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        count[x]++;
    }

    int max_count = 0;
    for (int i = 1; i <= 2; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
        }
    }

    int result = 1;
    for (int i = 1; i <= 2; i++) {
        if (count[i] != max_count) {
            if (max_count - count[i] <= m) {
                continue;
            } else {
                result++;
            }
        }
    }

    printf("%d\n", result);

    return 0;
}