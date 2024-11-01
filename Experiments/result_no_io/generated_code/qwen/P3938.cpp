#include <stdio.h>

int findLCA(int a, int b) {
    if (a > b) return findLCA(b, a);
    while (b % a != 0) {
        int temp = b;
        b = a;
        a = temp % a;
    }
    return a;
}

int main() {
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", findLCA(a, b));
    }
    return 0;
}