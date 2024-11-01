#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_CITIES 220
#define MAX_EDGES 600

typedef struct {
    int to;
    int cost;
} Edge;

Edge graph[MAX_CITIES][MAX_EDGES];
int graphSize[MAX_CITIES];
int D, P, C, F, S;

void addEdge(int from, int to, int cost) {
    graph[from][graphSize[from]].to = to;
    graph[from][graphSize[from]].cost = cost;
    graphSize[from]++;
}

int canReach(int start, int end) {
    int visited[MAX_CITIES] = {0};
    int queue[MAX_CITIES];
    int front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear) {
        int current = queue[front++];
        for (int i = 0; i < graphSize[current]; i++) {
            int next = graph[current][i].to;
            if (next == end) return 1;
            if (!visited[next]) {
                visited[next] = 1;
                queue[rear++] = next;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d%d%d%d%d", &D, &P, &C, &F, &S);

    for (int i = 0; i < P; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        addEdge(a, b, 0);
    }

    for (int i = 0; i < F; i++) {
        int j, k, t;
        scanf("%d%d%d", &j, &k, &t);
        addEdge(j, k, t);
    }

    int maxMoney = 0;
    for (int i = 1; i <= C; i++) {
        if (canReach(S, i)) {
            int money = D * (i - 1);
            if (money > maxMoney) maxMoney = money;
        }
    }

    printf("%d\n", maxMoney);
    return 0;
}