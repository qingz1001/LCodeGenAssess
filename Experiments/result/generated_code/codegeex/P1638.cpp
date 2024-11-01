#include <stdio.h>
#include <string.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int start = 0, end = 0;
    bool found = false;
    while (end < n) {
        int unique_painters = 0;
        int count[2001] = {0};
        int max_count = 0;
        int max_index = 0;

        while (end < n && unique_painters < m) {
            int painter = a[end];
            count[painter]++;
            if (count[painter] == 1) {
                unique_painters++;
            }
            if (count[painter] > max_count) {
                max_count = count[painter];
                max_index = painter;
            }
            end++;
        }

        if (unique_painters == m) {
            start = end - max_count;
            found = true;
        } else {
            end--;
        }
    }

    printf("%d %d\n", start + 1, end);
    return 0;
}