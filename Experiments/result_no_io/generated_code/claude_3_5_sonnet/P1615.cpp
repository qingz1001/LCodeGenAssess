#include <stdio.h>

int main() {
    int h1, m1, s1, h2, m2, s2, n;
    scanf("%d:%d:%d", &h1, &m1, &s1);
    scanf("%d:%d:%d", &h2, &m2, &s2);
    scanf("%d", &n);

    int time1 = h1 * 3600 + m1 * 60 + s1;
    int time2 = h2 * 3600 + m2 * 60 + s2;
    int diff = time2 - time1;

    long long result = (long long)diff * n;
    printf("%lld\n", result);

    return 0;
}