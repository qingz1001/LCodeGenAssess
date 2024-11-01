#include <stdio.h>

int main() {
    long long n;
    scanf("%lld", &n);

    long long count = 0;

    for (long long jin = 0; jin * 6 <= n; jin++) {
        for (long long mu = 0; mu <= 9 && jin * 6 + mu <= n; mu++) {
            for (long long shui = 0; shui <= 5 && jin * 6 + mu + shui <= n; shui++) {
                for (long long huo = 0; huo * 4 <= n - jin * 6 - mu - shui; huo++) {
                    long long tu = n - jin * 6 - mu - shui - huo * 4;
                    if (tu <= 7) {
                        count++;
                    }
                }
            }
        }
    }

    printf("%lld\n", count);

    return 0;
}