#include <stdio.h>
#include <string.h>

#define MAX_N 100005

char a[MAX_N], b[MAX_N], c[MAX_N], d[MAX_N];
char result_a[MAX_N], result_b[MAX_N];

void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s%s%s%s", a, b, c, d);

    for (int i = 0; i < n; i++) {
        if (a[i] < c[i]) {
            result_a[i] = a[i];
            result_b[i] = b[i];
        } else if (a[i] > c[i]) {
            result_a[i] = c[i];
            result_b[i] = d[i];
        } else {
            if (b[i] < d[i]) {
                result_a[i] = a[i];
                result_b[i] = b[i];
            } else {
                result_a[i] = c[i];
                result_b[i] = d[i];
            }
        }
    }
    result_a[n] = result_b[n] = '\0';

    printf("%s\n", result_b);

    return 0;
}