#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100
#define MAXM 20
#define MAXMC 100

int n, m, mc;
int a[MAXN], w[MAXN];
int C[MAXM];

bool canDefeat(int Ck) {
    int current_confidence = mc;
    int L = 0, F = 1;
    int max_attacks = 2;

    for (int i = 0; i < n; i++) {
        if (current_confidence < 0) return false;

        if (current_confidence >= a[i]) {
            current_confidence -= a[i];
        } else {
            return false;
        }

        if (current_confidence >= 0) {
            // Option 1: Reduce Ck by 1
            if (Ck > 0) {
                Ck--;
            }

            // Option 2: Increase current confidence
            int new_confidence = current_confidence + w[i];
            if (new_confidence > mc) new_confidence = mc;
            current_confidence = new_confidence;

            // Option 3: Increase level L
            L++;

            // Option 4: Multiply F by L
            F *= L;

            // Option 5: Attack with F
            if (max_attacks > 0 && F <= Ck) {
                Ck -= F;
                F = 1;
                L = 0;
                max_attacks--;
            }
        }
    }

    return Ck == 0;
}

int main() {
    scanf("%d %d %d", &n, &m, &mc);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &C[i]);
    }

    for (int i = 0; i < m; i++) {
        if (canDefeat(C[i])) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }

    return 0;
}