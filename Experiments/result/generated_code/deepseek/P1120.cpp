#include <stdio.h>
#include <stdlib.h>

#define MAX_N 65
#define MAX_LENGTH 50

int n;
int sticks[MAX_N];
int used[MAX_N];
int target_length;

int compare(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

int dfs(int current_length, int remaining_sticks, int start) {
    if (remaining_sticks == 0) return 1;
    if (current_length == target_length) return dfs(0, remaining_sticks, 0);

    for (int i = start; i < n; i++) {
        if (!used[i] && current_length + sticks[i] <= target_length) {
            used[i] = 1;
            if (dfs(current_length + sticks[i], remaining_sticks - 1, i + 1)) return 1;
            used[i] = 0;
            if (current_length == 0 || current_length + sticks[i] == target_length) break;
        }
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    int total_length = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &sticks[i]);
        total_length += sticks[i];
    }

    qsort(sticks, n, sizeof(int), compare);

    for (target_length = sticks[0]; target_length <= total_length; target_length++) {
        if (total_length % target_length == 0) {
            for (int i = 0; i < n; i++) used[i] = 0;
            if (dfs(0, n, 0)) {
                printf("%d\n", target_length);
                break;
            }
        }
    }

    return 0;
}