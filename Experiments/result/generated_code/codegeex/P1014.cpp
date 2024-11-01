#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int a = 1, b = 1, c = 1;
    while (c < N) {
        if (a == b) {
            b++;
        } else {
            a++;
        }
        c++;
    }

    if (a == b) {
        printf("%d/%d\n", b, a);
    } else {
        printf("%d/%d\n", a, b);
    }

    return 0;
}