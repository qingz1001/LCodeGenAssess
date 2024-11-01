#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005

typedef struct {
    int parent;
    long long a;
    long long b;
} Node;

Node nodes[MAXN];
int n;

long long gcd(long long a, long long b) {
    return b ? gcd(b, a % b) : a;
}

void process(int root) {
    long long sum_a = nodes[root].a;
    long long sum_b = nodes[root].b;
    int q[] = {root};
    int front = 0, rear = 1;
    
    while (front < rear) {
        int j = q[front++];
        for (int k = 1; k <= n; ++k) {
            if (nodes[k].parent == j && !nodes[k].visited) {
                nodes[k].visited = 1;
                sum_a += nodes[k].a;
                sum_b += nodes[k].b;
                q[rear++] = k;
            }
        }
    }
    
    long long r = (sum_a * nodes[root].b) / (sum_b * nodes[root].a);
    long long ceil_r = (r + nodes[root].a - 1) / nodes[root].a;
    nodes[root].result = ceil_r;
}

long long solve() {
    for (int i = 1; i <= n; ++i) {
        nodes[i].visited = 0;
    }
    
    for (int i = 1; i <= n; ++i) {
        if (!nodes[i].visited) {
            process(i);
        }
    }
    
    long long W = 0;
    for (int i = 1; i <= n; ++i) {
        W += nodes[i].result * nodes[i].result;
    }
    
    return W;
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) {
        scanf("%d", &nodes[i].parent);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%lld %lld", &nodes[i].a, &nodes[i].b);
        nodes[i].parent = 0;
        nodes[i].visited = 0;
        nodes[i].result = 0;
    }
    
    printf("%lld\n", solve());
    
    return 0;
}