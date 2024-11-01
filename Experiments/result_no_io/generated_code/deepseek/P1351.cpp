#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define MOD 10007

typedef struct {
    int v;
    struct Node* next;
} Node;

Node* adj[MAXN];
int weight[MAXN];
int n;

void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->v = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &weight[i]);
    }

    int max_joint_weight = 0;
    int sum_joint_weight = 0;

    for (int u = 1; u <= n; u++) {
        int max1 = 0, max2 = 0;
        int sum = 0;
        Node* cur = adj[u];
        while (cur) {
            int v = cur->v;
            if (weight[v] > max1) {
                max2 = max1;
                max1 = weight[v];
            } else if (weight[v] > max2) {
                max2 = weight[v];
            }
            sum = (sum + weight[v]) % MOD;
            cur = cur->next;
        }
        if (max1 * max2 > max_joint_weight) {
            max_joint_weight = max1 * max2;
        }
        sum = (sum * sum - sum + MOD) % MOD;
        sum_joint_weight = (sum_joint_weight + sum) % MOD;
    }

    printf("%d %d\n", max_joint_weight, sum_joint_weight);

    for (int i = 1; i <= n; i++) {
        Node* cur = adj[i];
        while (cur) {
            Node* next = cur->next;
            free(cur);
            cur = next;
        }
    }

    return 0;
}