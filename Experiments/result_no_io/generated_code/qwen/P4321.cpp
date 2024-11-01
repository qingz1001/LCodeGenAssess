#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

typedef struct {
    int to;
    struct Edge* next;
} Edge;

typedef struct {
    Edge* head;
    int size;
} Graph;

Graph* createGraph(int n) {
    Graph* graph = (Graph*)malloc(n * sizeof(Graph));
    for (int i = 0; i < n; i++) {
        graph[i].head = NULL;
        graph[i].size = 0;
    }
    return graph;
}

void addEdge(Graph* graph, int u, int v) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->to = v;
    newEdge->next = graph[u].head;
    graph[u].head = newEdge;
    graph[v].head = newEdge;
    graph[u].size++;
    graph[v].size++;
}

long long modInverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

long long combination(int n, int k, long long mod) {
    if (k > n) return 0;
    long long numerator = 1, denominator = 1;
    for (int i = 0; i < k; i++) {
        numerator = (numerator * (n - i)) % mod;
        denominator = (denominator * (i + 1)) % mod;
    }
    return (numerator * modInverse(denominator, mod)) % mod;
}

int main() {
    int N, E;
    scanf("%d %d", &N, &E);
    Graph* graph = createGraph(N);

    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u - 1, v - 1);
    }

    int M;
    scanf("%d", &M);

    for (int i = 0; i < M; i++) {
        int n;
        scanf("%d", &n);
        int* cities = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            scanf("%d", &cities[j]);
        }
        int s;
        scanf("%d", &s);

        long long total = 0;
        for (int j = 0; j < n; j++) {
            int city = cities[j] - 1;
            int depth = 0;
            int visited[N];
            for (int k = 0; k < N; k++) {
                visited[k] = 0;
            }
            int queue[100000];
            int front = 0, rear = 0;
            queue[rear++] = city;
            visited[city] = 1;
            while (front != rear) {
                int current = queue[front++];
                for (Edge* e = graph[current].head; e != NULL; e = e->next) {
                    if (!visited[e->to]) {
                        visited[e->to] = 1;
                        queue[rear++] = e->to;
                        depth++;
                    }
                }
            }
            total = (total + power(2, depth, MOD)) % MOD;
        }

        long long invN = modInverse(n, MOD);
        long long expected = (total * invN) % MOD;
        printf("%lld\n", expected);

        free(cities);
    }

    free(graph);
    return 0;
}