#include <stdio.h>
#include <stdbool.h>

#define MAX_W 100

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

bool canWin(int n, int w, int white[]) {
    int g = 0;
    for (int i = 0; i < w; i++) {
        g = gcd(g, white[i]);
    }
    return g != 1;
}

int main() {
    int n, k, w;
    int white[MAX_W];

    scanf("%d", &n);
    scanf("%d", &k);

    for (int i = 0; i < k; i++) {
        scanf("%d", &w);
        for (int j = 0; j < w; j++) {
            scanf("%d", &white[j]);
        }
        
        if (canWin(n, w, white)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}