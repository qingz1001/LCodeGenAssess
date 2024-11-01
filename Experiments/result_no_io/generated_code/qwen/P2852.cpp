#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20005
#define MAX_K 20005

int n, k;
int milk[MAX_N];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &milk[i]);
    }

    int max_length = 0;

    for (int len = 1; len <= n / k; len++) {
        int count[MAX_N][MAX_N] = {0};
        int found = 0;
        for (int start = 0; start + len - 1 < n; start++) {
            if (++count[milk[start]][milk[start + len - 1]] == k) {
                found = 1;
                break;
            }
        }
        if (found) {
            max_length = len;
        } else {
            break;
        }
    }

    printf("%d\n", max_length);

    return 0;
}