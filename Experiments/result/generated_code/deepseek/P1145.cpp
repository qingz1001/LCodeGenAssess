#include <stdio.h>

int josephus(int k) {
    int m = 1;
    while (1) {
        int pos = 0;
        int killed_bad_guys = 0;
        for (int i = 2 * k; i > k; i--) {
            pos = (pos + m - 1) % i;
            if (pos < k) {
                break;
            }
            killed_bad_guys++;
        }
        if (killed_bad_guys == k) {
            return m;
        }
        m++;
    }
}

int main() {
    int k;
    scanf("%d", &k);
    printf("%d\n", josephus(k));
    return 0;
}