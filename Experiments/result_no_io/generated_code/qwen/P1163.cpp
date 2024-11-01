#include <stdio.h>

int main() {
    int w0, w, m;
    scanf("%d %d %d", &w0, &w, &m);

    double rate = ((double)(w * m - w0)) / (w0 * m) * 100;

    printf("%.1f\n", rate);

    return 0;
}