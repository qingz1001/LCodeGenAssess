#include <stdio.h>
#include <stdlib.h>

// 定义节点结构体
typedef struct Node {
    int a, b, c;
} Node;

// 比较函数，用于qsort排序
int cmp(const void *a, const void *b) {
    Node *nodeA = (Node *)a;
    Node *nodeB = (Node *)b;
    if (nodeA->a == nodeB->a) {
        if (nodeA->b == nodeB->b) {
            return nodeA->c - nodeB->c;
        } else {
            return nodeA->b - nodeB->b;
        }
    } else {
        return nodeA->a - nodeB->a;
    }
}

// 判断是否可以通过跳动从start跳到end
int canReach(Node start, Node end) {
    if (start.a < start.b && start.b < start.c) {
        if (end.a < end.b && end.b < end.c) {
            if (start.b - start.a == end.b - end.a && start.c - start.b == end.c - end.b) {
                return 1;
            }
        }
    }
    return 0;
}

// 广度优先搜索
int bfs(Node start, Node end) {
    Node queue[1000000];
    int front = 0, rear = 0;
    queue[rear++] = start;
    int visited[1000000] = {0};
    int step = 0;
    while (front < rear) {
        int size = rear - front;
        for (int i = 0; i < size; i++) {
            Node current = queue[front++];
            if (canReach(current, end)) {
                return step;
            }
            // 尝试跳过a
            if (current.b - current.a == current.c - current.b) {
                Node next = current;
                next.a = current.b;
                next.b = current.c;
                if (!visited[next.a * 1000000 + next.b * 1000 + next.c]) {
                    visited[next.a * 1000000 + next.b * 1000 + next.c] = 1;
                    queue[rear++] = next;
                }
            }
            // 尝试跳过b
            if (current.a - current.b == current.c - current.b) {
                Node next = current;
                next.b = current.a;
                next.a = current.c;
                if (!visited[next.a * 1000000 + next.b * 1000 + next.c]) {
                    visited[next.a * 1000000 + next.b * 1000 + next.c] = 1;
                    queue[rear++] = next;
                }
            }
            // 尝试跳过c
            if (current.a - current.b == current.b - current.c) {
                Node next = current;
                next.c = current.b;
                next.b = current.a;
                if (!visited[next.a * 1000000 + next.b * 1000 + next.c]) {
                    visited[next.a * 1000000 + next.b * 1000 + next.c] = 1;
                    queue[rear++] = next;
                }
            }
        }
        step++;
    }
    return -1;
}

int main() {
    Node start, end;
    scanf("%d%d%d", &start.a, &start.b, &start.c);
    scanf("%d%d%d", &end.a, &end.b, &end.c);
    qsort(&start, 1, 1, cmp);
    qsort(&end, 1, 1, cmp);
    if (canReach(start, end)) {
        printf("YES\n%d\n", bfs(start, end));
    } else {
        printf("NO\n");
    }
    return 0;
}