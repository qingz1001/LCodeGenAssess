#include <stdio.h>
#include <string.h>

#define MAXN 100005

long long tree[MAXN];
int n;

void update(int x, int val) {
    while (x <= n) {
        tree[x] += val;
        x += x & (-x);
    }
}

long long query(int x) {
    long long sum = 0;
    while (x > 0) {
        sum += tree[x];
        x -= x & (-x);
    }
    return sum;
}

int main() {
    int w, a, b;
    char op;
    
    scanf("%d", &n);
    scanf("%d", &w);
    
    memset(tree, 0, sizeof(tree));
    
    while (w--) {
        scanf(" %c %d %d", &op, &a, &b);
        
        if (op == 'x') {
            update(a, b);
        } else if (op == 'y') {
            printf("%lld\n", query(b) - query(a-1));
        }
    }
    
    return 0;
}