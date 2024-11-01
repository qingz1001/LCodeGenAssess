#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 20000
#define INF 1000000001

typedef long long ll;

int N;
ll X[MAX_N], Y[MAX_N];

int check(ll L) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                ll minX = X[i] < X[j] ? (X[i] < X[k] ? X[i] : X[k]) : (X[j] < X[k] ? X[j] : X[k]);
                ll maxX = X[i] > X[j] ? (X[i] > X[k] ? X[i] : X[k]) : (X[j] > X[k] ? X[j] : X[k]);
                ll minY = Y[i] < Y[j] ? (Y[i] < Y[k] ? Y[i] : Y[k]) : (Y[j] < Y[k] ? Y[j] : Y[k]);
                ll maxY = Y[i] > Y[j] ? (Y[i] > Y[k] ? Y[i] : Y[k]) : (Y[j] > Y[k] ? Y[j] : Y[k]);

                if (maxX - minX <= L && maxY - minY <= L) {
                    int covered = 1;
                    for (int m = 0; m < N; m++) {
                        if (X[m] < minX || X[m] > minX + L || Y[m] < minY || Y[m] > minY + L) {
                            covered = 0;
                            break;
                        }
                    }
                    if (covered) return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lld %lld", &X[i], &Y[i]);
    }

    ll left = 0, right = INF, mid;
    while (left < right) {
        mid = left + (right - left) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%lld\n", left);
    return 0;
}