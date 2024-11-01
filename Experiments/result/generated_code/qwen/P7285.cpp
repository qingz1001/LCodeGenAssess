#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

void process(int n, int *arr) {
    int x = 0, y = 0;
    int current_x = 0, current_y = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            current_x++;
            current_y = 0;
        } else {
            if (current_x > x) {
                x = current_x;
                y = current_y;
            }
            current_x = 0;
            current_y++;
        }
    }

    if (current_x > x) {
        x = current_x;
        y = current_y;
    }

    int max_diff = x - y;
    printf("%d\n", max_diff);

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
        process(n, arr);
    }
    return 0;
}