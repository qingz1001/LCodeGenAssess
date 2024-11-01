#include <stdio.h>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 100005;
vector<int> graph[MAXN];
int in_degree[MAXN];
int out_degree[MAXN];
int visited[MAXN];

void bfs(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = 1;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    memset(in_degree, 0, sizeof(in_degree));
    memset(out_degree, 0, sizeof(out_degree));
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < m; i++) {
        int b, e;
        scanf("%d %d", &b, &e);
        graph[b].push_back(e);
        in_degree[e]++;
        out_degree[b]++;
    }

    int source_count = 0;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            bfs(i);
            source_count++;
        }
    }

    int sink_count = 0;
    for (int i = 1; i <= n; i++) {
        if (out_degree[i] == 0) {
            sink_count++;
        }
    }

    printf("%d\n", max(source_count, sink_count));

    return 0;
}