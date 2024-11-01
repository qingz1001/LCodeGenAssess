#include <stdio.h>
#include <string.h>

#define MAX_LEN 101

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int main() {
    char n[MAX_LEN];
    int k;
    scanf("%s %d", n, &k);

    int len = strlen(n);
    int mod = 1;
    for (int i = 0; i < k; i++) {
        mod *= 10;
    }

    int result = 1;
    int is_cyclic = 0;
    
    if (n[len-1] % 2 == 0 || n[len-1] == '5') {
        for (int i = 2; i <= 4; i++) {
            int temp = 1;
            for (int j = 0; j < i; j++) {
                temp = (temp * (n[len-1] - '0')) % mod;
            }
            if (temp == (n[len-1] - '0')) {
                is_cyclic = 1;
                result = i - 1;
                break;
            }
        }
    } else {
        int phi = mod;
        for (int i = 2; i * i <= mod; i++) {
            if (mod % i == 0) {
                phi = phi / i * (i - 1);
                while (mod % i == 0) {
                    mod /= i;
                }
            }
        }
        if (mod > 1) {
            phi = phi / mod * (mod - 1);
        }

        int temp = 1;
        for (int i = 0; i < phi; i++) {
            temp = (temp * (n[len-1] - '0')) % (1 << k);
        }
        if (temp == 1) {
            is_cyclic = 1;
            result = phi;
            for (int i = 1; i * i <= phi; i++) {
                if (phi % i == 0) {
                    temp = 1;
                    for (int j = 0; j < i; j++) {
                        temp = (temp * (n[len-1] - '0')) % (1 << k);
                    }
                    if (temp == 1) {
                        result = i;
                        break;
                    }
                    if (i * i != phi) {
                        temp = 1;
                        for (int j = 0; j < phi / i; j++) {
                            temp = (temp * (n[len-1] - '0')) % (1 << k);
                        }
                        if (temp == 1) {
                            result = phi / i;
                        }
                    }
                }
            }
        }
    }

    if (is_cyclic) {
        printf("%d\n", result);
    } else {
        printf("-1\n");
    }

    return 0;
}