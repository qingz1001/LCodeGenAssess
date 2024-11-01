#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1000005

typedef struct {
    int parent;
    long long a, b;
    int child_count;
    int children[MAXN];
} Node;

Node nodes[MAXN];
int n;
long long activation_cost = 0;

void read_input() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &nodes[i].parent);
        nodes[nodes[i].parent].children[nodes[nodes[i].parent].child_count++] = i;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &nodes[i].a);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &nodes[i].b);
    }
}

long long calculate_r(int node) {
    long long a_sum = nodes[node].a;
    long long b_sum = nodes[node].b;
    for (int i = 0; i < nodes[node].child_count; i++) {
        int child = nodes[node].children[i];
        a_sum += nodes[child].a;
        b_sum += nodes[child].b;
    }
    return a_sum / b_sum;
}

void process_node(int node, int depth) {
    long long r = calculate_r(node);
    activation_cost += depth * (long long)ceil(r);
    for (int i = 0; i < nodes[node].child_count; i++) {
        int child = nodes[node].children[i];
        nodes[child].a += (long long)ceil(r);
        process_node(child, depth + 1);
    }
}

int main() {
    read_input();
    process_node(1, 1);
    printf("%lld\n", activation_cost);
    return 0;
}