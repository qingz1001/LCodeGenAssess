#include <stdio.h>
#include <math.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }

    int k = b - a;
    double golden_ratio = (1 + sqrt(5)) / 2;
    int predicted_a = (int)(k * golden_ratio);

    if (a == predicted_a) {
        printf("0\n");
    } else {
        printf("1\n");
    }

    return 0;
}