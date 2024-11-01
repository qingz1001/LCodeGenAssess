#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    double expected_value = (double)n / 2;
    printf("%.8f\n", expected_value);
    return 0;
}