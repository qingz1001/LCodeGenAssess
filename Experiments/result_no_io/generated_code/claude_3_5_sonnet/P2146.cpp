#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 100005

int n, q;
int depend[MAXN];
bool installed[MAXN];
int children[MAXN];

int dfs(int x) {
    if (children[x] != -1) return children[x];
    children[x] = 1;
    for (int i = 1; i < n; i++) {
        if (depend[i] == x) {
            children[x] += dfs(i);
        }
    }
    return children[x];
}

int install(int x) {
    if (installed[x]) return 0;
    int count = 1;
    installed[x] = true;
    if (x != 0) {
        count += install(depend[x]);
    }
    return count;
}

int uninstall(int x) {
    if (!installed[x]) return 0;
    int count = children[x];
    installed[x] = false;
    for (int i = 1; i < n; i++) {
        if (depend[i] == x) {
            installed[i] = false;
        }
    }
    return count;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d", &depend[i]);
    }
    
    memset(children, -1, sizeof(children));
    dfs(0);
    
    scanf("%d", &q);
    char op[10];
    int x;
    while (q--) {
        scanf("%s %d", op, &x);
        if (strcmp(op, "install") == 0) {
            printf("%d\n", install(x));
        } else {
            printf("%d\n", uninstall(x));
        }
    }
    
    return 0;
}