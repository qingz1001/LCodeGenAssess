#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);
    double money = 100.0;
    for (int i = 0; i < N; i++) {
        int rate;
        scanf("%d", &rate);
        if (money >= 100) {
            money /= rate;
        } else {
            money *= rate;
        }
    }
    printf("%.2f\n", money);
    return 0;
}