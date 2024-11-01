#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void pour_beer(int a, int b, int *Pa, int *Pb) {
    int bucket = 0, cup_a = 0, cup_b = 0;
    int steps = 0;

    while (cup_a > 0 || bucket > 0) {
        if (cup_a == 0 && bucket > 0) {
            cup_a = a;
            bucket -= a;
            (*Pa)++;
            steps++;
        } else if (cup_b == 0 && cup_a > 0) {
            cup_b = b;
            cup_a -= b;
            (*Pb)++;
            steps++;
        } else if (cup_a > 0 && cup_b > 0) {
            int transfer = (b - cup_b <= cup_a) ? (b - cup_b) : cup_a;
            cup_a -= transfer;
            cup_b += transfer;
            steps++;
        }
    }

    printf("%d\n%d %d\n", steps, *Pa, *Pb);
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    int Pa = 0, Pb = 0;
    pour_beer(a, b, &Pa, &Pb);

    return 0;
}