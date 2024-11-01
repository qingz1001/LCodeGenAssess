#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int id, rank;
} Island;

typedef struct {
    int parent, size;
} DSU;

typedef struct {
    int id, rank;
} Node;

Island islands[MAXN];
DSU dsu[MAXN];
Node heap[MAXN];
int heapSize;

int compareIslands(const void *a, const void *b) {
    return ((Island *)a)->rank - ((Island *)b)->rank;
}

int find(int x) {
    if (dsu[x].parent != x)
        dsu[x].parent = find(dsu[x].parent);
    return dsu[x].parent;
}

void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (dsu[rootX].size < dsu[rootY].size) {
            dsu[rootX].parent = rootY;
            dsu[rootY].size += dsu[rootX].size;
        } else {
            dsu[rootY].parent = rootX;
            dsu[rootX].size += dsu[rootY].size;
        }
    }
}

void heapInsert(int id, int rank) {
    heap[heapSize].id = id;
    heap[heapSize].rank = rank;
    int current = heapSize;
    while (current > 0 && heap[current].rank < heap[(current - 1) / 2].rank) {
        Node temp = heap[current];
        heap[current] = heap[(current - 1) / 2];
        heap[(current - 1) / 2] = temp;
        current = (current - 1) / 2;
    }
    heapSize++;
}

Node heapExtractMin() {
    Node minNode = heap[0];
    heap[0] = heap[--heapSize];
    int current = 0;
    while (1) {
        int left = 2 * current + 1;
        int right = 2 * current + 2;
        int smallest = current;
        if (left < heapSize && heap[left].rank < heap[smallest].rank)
            smallest = left;
        if (right < heapSize && heap[right].rank < heap[smallest].rank)
            smallest = right;
        if (smallest != current) {
            Node temp = heap[current];
            heap[current] = heap[smallest];
            heap[smallest] = temp;
            current = smallest;
        } else {
            break;
        }
    }
    return minNode;
}

int main() {
    int n, m, q;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &islands[i].rank);
        islands[i].id = i;
        dsu[i].parent = i;
        dsu[i].size = 1;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unionSets(u, v);
    }
    scanf("%d", &q);
    while (q--) {
        char op;
        int x, y;
        scanf(" %c %d %d", &op, &x, &y);
        if (op == 'B') {
            unionSets(x, y);
        } else if (op == 'Q') {
            int rootX = find(x);
            heapSize = 0;
            for (int i = 1; i <= n; i++) {
                if (find(i) == rootX) {
                    heapInsert(islands[i].id, islands[i].rank);
                }
            }
            if (y > heapSize) {
                printf("-1\n");
            } else {
                for (int i = 1; i < y; i++) {
                    heapExtractMin();
                }
                printf("%d\n", heapExtractMin().id);
            }
        }
    }
    return 0;
}