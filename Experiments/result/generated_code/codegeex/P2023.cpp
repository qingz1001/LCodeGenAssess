#include <stdio.h>

#define MAXN 100001

typedef long long ll;

struct Operation {
    int type;
    int t;
    int g;
    int c;
};

ll a[MAXN];
Operation operations[MAXN];

void update_mul(int t, int g, int c, ll *a, int n) {
    for (int i = t; i <= g; i++) {
        a[i] *= c;
    }
}

void update_add(int t, int g, int c, ll *a, int n) {
    for (int i = t; i <= g; i++) {
        a[i] += c;
    }
}

ll query_sum(int t, int g, ll *a, int n) {
    ll sum = 0;
    for (int i = t; i <= g; i++) {
        sum += a[i];
    }
    return sum;
}

int main() {
    int n, p, m;
    scanf("%d %d", &n, &p);
    
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    
    scanf("%d", &m);
    
    for (int i = 0; i < m; i++) {
        scanf("%d", &operations[i].type);
        scanf("%d %d", &operations[i].t, &operations[i].g);
        if (operations[i].type == 1 || operations[i].type == 2) {
            scanf("%d", &operations[i].c);
        }
    }
    
    for (int i = 0; i < m; i++) {
        if (operations[i].type == 1) {
            update_mul(operations[i].t, operations[i].g, operations[i].c, a, n);
        } else if (operations[i].type == 2) {
            update_add(operations[i].t, operations[i].g, operations[i].c, a, n);
        } else if (operations[i].type == 3) {
            ll result = query_sum(operations[i].t, operations[i].g, a, n);
            printf("%lld\n", result % p);
        }
    }
    
    return 0;
}