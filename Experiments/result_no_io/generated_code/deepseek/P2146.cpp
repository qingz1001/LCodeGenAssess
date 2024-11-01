#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

typedef struct Node {
    int parent;
    int child_count;
    int children[MAXN];
    int installed;
} Node;

Node nodes[MAXN];
int n, q;

void init() {
    for (int i = 0; i < n; i++) {
        nodes[i].parent = -1;
        nodes[i].child_count = 0;
        nodes[i].installed = 0;
    }
}

void add_dependency(int child, int parent) {
    nodes[child].parent = parent;
    nodes[parent].children[nodes[parent].child_count++] = child;
}

int install(int x) {
    if (nodes[x].installed) return 0;
    int count = 0;
    for (int i = x; i != -1; i = nodes[i].parent) {
        if (!nodes[i].installed) {
            nodes[i].installed = 1;
            count++;
        }
    }
    return count;
}

int uninstall(int x) {
    if (!nodes[x].installed) return 0;
    int count = 0;
    int queue[MAXN], front = 0, rear = 0;
    queue[rear++] = x;
    while (front < rear) {
        int node = queue[front++];
        if (nodes[node].installed) {
            nodes[node].installed = 0;
            count++;
            for (int i = 0; i < nodes[node].child_count; i++) {
                queue[rear++] = nodes[node].children[i];
            }
        }
    }
    return count;
}

int main() {
    scanf("%d", &n);
    init();
    for (int i = 1; i < n; i++) {
        int parent;
        scanf("%d", &parent);
        add_dependency(i, parent);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        char operation[10];
        int x;
        scanf("%s %d", operation, &x);
        if (strcmp(operation, "install") == 0) {
            printf("%d\n", install(x));
        } else if (strcmp(operation, "uninstall") == 0) {
            printf("%d\n", uninstall(x));
        }
    }
    return 0;
}