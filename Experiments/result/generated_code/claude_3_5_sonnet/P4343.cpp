#include <stdio.h>
#include <stdlib.h>

#define MAX_L 100000

int main() {
    int l, k;
    scanf("%d %d", &l, &k);

    long long code_lines = 0;
    int submissions = 0;
    long long min_n = 1, max_n = 1000000000;

    for (int i = 0; i < l; i++) {
        int x;
        scanf("%d", &x);

        if (x >= 0) {
            code_lines += x;
        } else {
            code_lines = (code_lines + x > 0) ? code_lines + x : 0;
        }

        if (code_lines >= min_n) {
            submissions++;
            if (submissions > k) {
                min_n = code_lines + 1;
            }
            code_lines = 0;
        }

        if (code_lines >= max_n) {
            submissions++;
            code_lines = 0;
        }
    }

    if (submissions < k) {
        max_n = code_lines;
    }

    if (min_n > max_n || submissions > k) {
        printf("-1\n");
    } else {
        printf("%lld %lld\n", min_n, max_n);
    }

    return 0;
}