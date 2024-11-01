#include <stdio.h>

int is_dog_angry(int time, int a, int b) {
    int cycle = a + b;
    int remainder = time % cycle;
    return remainder > 0 && remainder <= a;
}

int main() {
    int a, b, c, d;
    int p, m, g;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    scanf("%d %d %d", &p, &m, &g);

    int dog1_p = is_dog_angry(p, a, b);
    int dog2_p = is_dog_angry(p, c, d);
    int dog1_m = is_dog_angry(m, a, b);
    int dog2_m = is_dog_angry(m, c, d);
    int dog1_g = is_dog_angry(g, a, b);
    int dog2_g = is_dog_angry(g, c, d);

    if (dog1_p + dog2_p == 0) {
        printf("none\n");
    } else if (dog1_p + dog2_p == 1) {
        printf("one\n");
    } else {
        printf("both\n");
    }

    if (dog1_m + dog2_m == 0) {
        printf("none\n");
    } else if (dog1_m + dog2_m == 1) {
        printf("one\n");
    } else {
        printf("both\n");
    }

    if (dog1_g + dog2_g == 0) {
        printf("none\n");
    } else if (dog1_g + dog2_g == 1) {
        printf("one\n");
    } else {
        printf("both\n");
    }

    return 0;
}