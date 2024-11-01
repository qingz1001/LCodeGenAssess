#include <stdio.h>

int main() {
    int n, v, m, a;
    scanf("%d %d %d %d", &n, &v, &m, &a);

    int total_fee = 0;
    int current_students = 0;

    while (current_students < n) {
        total_fee += v;
        current_students++;
        if (current_students % m == 0) {
            v += a;
        }
    }

    printf("%d\n", total_fee);
    return 0;
}