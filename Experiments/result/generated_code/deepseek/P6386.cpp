#include <stdio.h>

int is_dog_angry(int time, int a, int b) {
    int cycle = a + b;
    int remainder = time % cycle;
    return remainder > 0 && remainder <= a;
}

void check_arrival(int time, int a, int b, int c, int d) {
    int dog1 = is_dog_angry(time, a, b);
    int dog2 = is_dog_angry(time, c, d);

    if (dog1 && dog2) {
        printf("both\n");
    } else if (dog1 || dog2) {
        printf("one\n");
    } else {
        printf("none\n");
    }
}

int main() {
    int a, b, c, d, p, m, g;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    scanf("%d %d %d", &p, &m, &g);

    check_arrival(p, a, b, c, d);
    check_arrival(m, a, b, c, d);
    check_arrival(g, a, b, c, d);

    return 0;
}