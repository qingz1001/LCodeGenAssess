#include <stdio.h>

int main() {
    int n, T;
    scanf("%d %d", &n, &T);

    int v[100005], t[100005];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &v[i], &t[i]);
    }

    int max_height = 0;
    int min_index = n;

    for (int i = 0; i < n; i++) {
        int current_height = v[i] * (T - t[i]);
        if (current_height > max_height) {
            max_height = current_height;
            min_index = i;
        } else if (current_height == max_height) {
            if (i < min_index) {
                min_index = i;
            }
        }
    }

    printf("%d\n", min_index + 1);

    return 0;
}