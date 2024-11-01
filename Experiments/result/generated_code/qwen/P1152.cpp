#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int *visited = (int *)calloc(n - 1, sizeof(int));
    for (int i = 1; i < n; i++) {
        int diff = abs(arr[i] - arr[i - 1]);
        if (diff >= 1 && diff <= n - 1) {
            visited[diff - 1] = 1;
        }
    }

    int all_visited = 1;
    for (int i = 0; i < n - 1; i++) {
        if (!visited[i]) {
            all_visited = 0;
            break;
        }
    }

    if (all_visited) {
        printf("Jolly\n");
    } else {
        printf("Not jolly\n");
    }

    free(arr);
    free(visited);
    return 0;
}