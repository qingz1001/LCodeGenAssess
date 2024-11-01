#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    double exchangeRates[N];
    for (int i = 0; i < N; i++) {
        scanf("%lf", &exchangeRates[i]);
    }

    double dollars = 100.0;
    double mark = 100.0 / exchangeRates[0];

    for (int i = 1; i < N; i++) {
        if (exchangeRates[i] > exchangeRates[i - 1]) {
            dollars = mark * exchangeRates[i];
            mark = dollars / exchangeRates[i];
        } else {
            mark = dollars * exchangeRates[i];
            dollars = mark / exchangeRates[i];
        }
    }

    printf("%.2lf\n", dollars);
    return 0;
}