#include <stdio.h>

#define MAX_P 100000

int test;
int m;
int p[MAX_P], q[MAX_P];
int phi[MAX_P + 1];
int ans;

void init() {
    phi[1] = 1;
    for (int i = 2; i <= MAX_P; i++) {
        if (phi[i] == 0) {
            for (int j = i; j <= MAX_P; j += i) {
                if (phi[j] == 0) {
                    phi[j] = j;
                }
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
}

int main() {
    scanf("%d", &test);
    init();
    while (test--) {
        scanf("%d", &m);
        ans = 0;
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &p[i], &q[i]);
            ans += p[i] * q[i] - phi[p[i]] * q[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}