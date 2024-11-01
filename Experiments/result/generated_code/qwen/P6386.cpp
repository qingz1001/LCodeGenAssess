#include <stdio.h>

int main() {
    int a, b, c, d;
    int p, m, g;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    scanf("%d %d %d", &p, &m, &g);

    int result_p = (p % (a + b) < a) ? 1 : 0;
    int result_m = (m % (c + d) < c) ? 1 : 0;
    int result_g = (g % (a + b) < a) ? 1 : 0;

    if (result_p == 2 && result_m == 2 && result_g == 2) printf("both\n");
    else if ((result_p == 2 || result_m == 2 || result_g == 2)) printf("one\n");
    else printf("none\n");

    return 0;
}