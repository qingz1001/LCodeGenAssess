#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100005
#define MIN(a, b) ((a) < (b) ? (a) : (b))

char lights[MAX_N];
int n, k;

int check(int mid) {
    int changes = 0;
    int continuous = 0;
    int total = 0;

    for (int i = 0; i < n; i++) {
        if (continuous == mid) {
            changes += continuous / 2;
            total += continuous % 2;
            continuous = 0;
        }
        
        if ((i == 0 || lights[i] != lights[i-1]) && continuous > 0) {
            changes += continuous / 2;
            total += continuous % 2;
            continuous = 0;
        }
        
        continuous++;
    }

    if (continuous > 0) {
        changes += continuous / 2;
        total += continuous % 2;
    }

    return changes <= k && total <= k - changes;
}

int binary_search() {
    int left = 1, right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &n, &k);
    scanf("%s", lights);

    int result = binary_search();
    printf("%d\n", result);

    return 0;
}