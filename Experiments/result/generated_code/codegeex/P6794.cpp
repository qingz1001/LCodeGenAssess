#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200001

struct Operation {
    int type;
    int i;
    int x;
    int h;
};

int n, q;
int h[MAXN];
struct Operation operations[MAXN];

void readInput() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i < n; i++) {
        scanf("%d", &h[i]);
    }
    for (int i = 0; i < q; i++) {
        scanf("%d %d %d", &operations[i].type, &operations[i].i, &operations[i].x);
        if (operations[i].type == 0 || operations[i].type == 2) {
            scanf("%d", &operations[i].h);
        }
    }
}

void executeOperations() {
    for (int i = 0; i < q; i++) {
        int type = operations[i].type;
        int x = operations[i].x;
        if (type == 0) {
            // 灌水操作
            int h = operations[i].h;
            // 执行灌水逻辑
        } else if (type == 1) {
            // 排水操作
            // 执行排水逻辑
        } else if (type == 2) {
            // 调整挡板高度
            int h = operations[i].h;
            // 执行调整挡板逻辑
        } else if (type == 3) {
            // 查询水面高度
            // 执行查询逻辑
        }
    }
}

int main() {
    readInput();
    executeOperations();
    return 0;
}