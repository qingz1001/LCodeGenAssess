#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 100005;

vector<int> graph[MAXN];
int in_degree[MAXN];
queue<int> zero_in_degree;

void topological_sort(int n) {
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            zero_in_degree.push(i);
        }
    }

    int count = 0;
    while (!zero_in_degree.empty()) {
        int u = zero_in_degree.front();
        zero_in_degree.pop();
        count++;

        for (int v : graph[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                zero_in_degree.push(v);
            }
        }
    }

    if (count < n) {
        printf("IMPOSSIBLE\n");
    } else {
        printf("%d\n", count);
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int b, e;
        scanf("%d %d", &b, &e);
        graph[b].push_back(e);
        in_degree[e]++;
    }

    topological_sort(n);

    return 0;
}