#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int operations = 0;
    int current_height = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] > current_height) {
            operations += (a[i] - current_height);
            current_height = a[i];
        } else if (a[i] < current_height) {
            current_height = a[i];
        }
    }

    printf("%d\n", operations);
    return 0;
}