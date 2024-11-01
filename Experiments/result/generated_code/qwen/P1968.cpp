#include <stdio.h>

int main() {
    int N;
    double money = 100.0;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        double rate;
        scanf("%lf", &rate);
        if (rate > 1.0) {
            money /= rate;
        } else {
            money *= rate;
        }
    }

    printf("%.2f\n", money);
    return 0;
}