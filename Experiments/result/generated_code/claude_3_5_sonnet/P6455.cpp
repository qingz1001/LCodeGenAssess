#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100005
#define PI 3.14159265358979323846

typedef long long ll;
typedef double db;

int n, k, r, L;
int p[MAX_N];
db f[MAX_N];
int pre[MAX_N];

db calc(int i, int j) {
    db dist = (p[j] - p[i] + L) % L;
    if (dist > 2 * r) return 2 * PI * r * r;
    db theta = 2 * acos(dist / (2 * r));
    return 2 * PI * r * r - r * r * (theta - sin(theta));
}

int main() {
    scanf("%d %d %d %d", &n, &k, &r, &L);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i]);
    }
    
    for (int i = 1; i <= n; i++) {
        f[i] = calc(i, i);
        pre[i] = i;
        for (int j = 1; j < i; j++) {
            db tmp = f[j] + calc(j + 1, i);
            if (tmp > f[i]) {
                f[i] = tmp;
                pre[i] = j;
            }
        }
    }
    
    int pos = n;
    for (int i = 1; i <= n; i++) {
        if (f[i] > f[pos]) pos = i;
    }
    
    int ans[MAX_N], cnt = 0;
    while (pos > 0) {
        for (int i = pre[pos] + 1; i <= pos; i++) {
            ans[++cnt] = i;
        }
        pos = pre[pos];
    }
    
    for (int i = k; i > 0; i--) {
        printf("%d ", ans[i]);
    }
    
    return 0;
}