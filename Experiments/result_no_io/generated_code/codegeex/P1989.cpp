#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
const int MAXM = 200005;

vector<int> adj[MAXN];
int n, m;

void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int count_triangles() {
    int ans = 0;
    for (int u = 1; u <= n; ++u) {
        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            for (int j = i + 1; j < adj[u].size(); ++j) {
                int w = adj[u][j];
                if (find(adj[v].begin(), adj[v].end(), w) != adj[v].end()) {
                    ans++;
                }
            }
        }
    }
    return ans / 3;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }
    printf("%d\n", count_triangles());
    return 0;
}