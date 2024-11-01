#include <stdio.h>

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    int a[11];
    for (int i = 0; i < k; i++) {
        scanf("%d", &a[i]);
    }
    int time = 0;
    int current_position = 0;
    while (current_position < n) {
        current_position += m;
        time++;
        for (int i = 0; i < k; i++) {
            if (current_position == a[i]) {
                m++;
                break;
            }
        }
    }
    printf("%d\n", time);
    return 0;
}