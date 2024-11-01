#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

void solve(int n, int arr[]) {
    int x = 0, y = 0;
    int max_x = 0;
    int current_x = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            current_x++;
            if (current_x > max_x) {
                max_x = current_x;
            }
        } else {
            if (current_x > 0) {
                y += current_x - 1;
                current_x = 0;
            }
        }
    }

    if (current_x > 0) {
        y += current_x - 1;
    }

    x = max_x;
    printf("%d\n", x - y);

    int modified = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0 && modified < y) {
            arr[i] = 1;
            modified++;
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        int arr[MAXN];
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        solve(n, arr);
    }
    return 0;
}