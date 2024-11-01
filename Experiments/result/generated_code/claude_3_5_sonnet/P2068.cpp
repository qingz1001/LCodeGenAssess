#include <stdio.h>
#include <string.h>

#define MAX_N 100000

long long tree[MAX_N + 1];
int n;

void update(int i, int val) {
    while (i <= n) {
        tree[i] += val;
        i += i & (-i);
    }
}

long long query(int i) {
    long long sum = 0;
    while (i > 0) {
        sum += tree[i];
        i -= i & (-i);
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
            printf("%lld\n", query(b) - query(a - 1));
        }
    }
    
    return 0;
}