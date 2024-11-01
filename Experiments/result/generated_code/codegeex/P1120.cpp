#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int n;
int len[70];
int sum;
int max;

bool used[70];
int target;
int count;

bool cmp(const void *a, const void *b) {
    return *(int*)a > *(int*)b;
}

bool dfs(int pos, int rest) {
    if (rest == 0) {
        return true;
    }
    if (pos == n) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (!used[i] && len[i] <= rest) {
            used[i] = true;
            if (dfs(pos + 1, rest - len[i])) {
                return true;
            }
            used[i] = false;
            if (rest == target) {
                break;
            }
        }
    }
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &len[i]);
        sum += len[i];
        if (len[i] > max) {
            max = len[i];
        }
    }
    qsort(len, n, sizeof(int), cmp);
    for (target = max; target <= sum; target++) {
        if (sum % target == 0) {
            count = sum / target;
            memset(used, 0, sizeof(used));
            if (dfs(0, target)) {
                printf("%d\n", target);
                return 0;
            }
        }
    }
    printf("%d\n", sum);
    return 0;
}