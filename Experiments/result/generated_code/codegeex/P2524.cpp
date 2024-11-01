#include <stdio.h>
#include <string.h>

int main() {
    int n, x;
    scanf("%d %d", &n, &x);

    int count = 0;
    int perm[10];
    int used[10] = {0};

    // 生成全排列
    for (int i = 1; i <= n; i++) {
        perm[i] = i;
    }

    do {
        int current = 0;
        for (int i = 1; i <= n; i++) {
            if (perm[i] != x % 10) {
                current++;
            } else {
                break;
            }
        }
        if (current == n) {
            count++;
        }
    } while (next_permutation(perm + 1, perm + n + 1));

    printf("%d\n", count + 1);

    return 0;
}