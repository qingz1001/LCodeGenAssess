#include <stdio.h>

int main() {
    int n, v, m, a;
    scanf("%d%d%d%d", &n, &v, &m, &a);

    int total = 0;
    int current_students = 0;
    int current_price = v;

    while (current_students < n) {
        total += current_price;
        current_students++;
        if (current_students % m == 0) {
            current_price += a;
        }
    }

    printf("%d\n", total);
    return 0;
}