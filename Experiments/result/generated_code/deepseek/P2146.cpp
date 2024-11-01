#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

typedef struct Node {
    int parent;
    int installed;
    struct Node* children[MAXN];
    int child_count;
} Node;

Node nodes[MAXN];
int n, q;

void init_nodes() {
    for (int i = 0; i < n; i++) {
        nodes[i].parent = -1;
        nodes[i].installed = 0;
        nodes[i].child_count = 0;
    }
}

void add_dependency(int child, int parent) {
    nodes[child].parent = parent;
    nodes[parent].children[nodes[parent].child_count++] = &nodes[child];
}

int install_package(int x) {
    if (nodes[x].installed) return 0;
    int count = 0;
    int current = x;
    while (current != -1 && !nodes[current].installed) {
        nodes[current].installed = 1;
        count++;
        current = nodes[current].parent;
    }
    return count;
}

int uninstall_package(int x) {
    if (!nodes[x].installed) return 0;
    int count = 0;
    int stack[MAXN], top = 0;
    stack[top++] = x;
    while (top > 0) {
        int current = stack[--top];
        if (nodes[current].installed) {
            nodes[current].installed = 0;
            count++;
            for (int i = 0; i < nodes[current].child_count; i++) {
                stack[top++] = nodes[current].children[i] - nodes;
            }
        }
    }
    return count;
}

int main() {
    scanf("%d", &n);
    init_nodes();
    for (int i = 1; i < n; i++) {
        int parent;
        scanf("%d", &parent);
        add_dependency(i, parent);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        char operation[10];
        int package;
        scanf("%s %d", operation, &package);
        if (strcmp(operation, "install") == 0) {
            printf("%d\n", install_package(package));
        } else if (strcmp(operation, "uninstall") == 0) {
            printf("%d\n", uninstall_package(package));
        }
    }
    return 0;
}