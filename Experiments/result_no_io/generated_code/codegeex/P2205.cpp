#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000001

typedef struct {
    int pos;
    int val;
} Node;

int cmp(const void *a, const void *b) {
    Node *nodeA = (Node *)a;
    Node *nodeB = (Node *)b;
    return nodeA->pos - nodeB->pos;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    Node *nodes = (Node *)malloc(sizeof(Node) * (2 * n + 1));
    memset(nodes, 0, sizeof(Node) * (2 * n + 1));
    
    char move[MAX];
    int count = 0;
    for (int i = 0; i < n; i++) {
        scanf("%s", move);
        int len = strlen(move);
        int num = 0;
        for (int j = 0; j < len - 1; j++) {
            num = num * 10 + (move[j] - '0');
        }
        if (move[len - 1] == 'L') {
            nodes[count].pos = -num;
        } else {
            nodes[count].pos = num;
        }
        nodes[count].val = 1;
        count++;
        nodes[count].pos = nodes[count - 1].pos;
        nodes[count].val = -1;
        count++;
    }
    
    qsort(nodes, count, sizeof(Node), cmp);
    
    int res = 0;
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += nodes[i].val;
        if (sum >= k) {
            res += nodes[i + 1].pos - nodes[i].pos;
        }
    }
    
    printf("%d\n", res);
    free(nodes);
    return 0;
}