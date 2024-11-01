pp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int x0, a, b, c, d;
    cin >> x0 >> a >> b >> c >> d;
    int N, M, Q;
    cin >> N >> M >> Q;
    
    vector<int> xi(N * M);
    for (int i = 0; i < N * M; ++i) {
        xi[i] = ((long long)a * x0 * x0 + (long long)b * x0 + c) % d;
        x0 = xi[i];
    }
    
    vector<int> T(N * M);
    iota(T.begin(), T.end(), 1);
    
    for (int i = 0; i < N * M; ++i) {
        swap(T[i], T[(xi[i] % (i + 1))]);
    }
    
    for (int i = 0; i < Q; ++i) {
        int u, v;
        cin >> u >> v;
        swap(T[u - 1], T[v - 1]);
    }
    
    vector<int> path;
    int x = 0, y = 0;
    while (x != N - 1 || y != M - 1) {
        if (y == M - 1 || (x < N - 1 && T[x * M + y] > T[(x + 1) * M + y])) {
            path.push_back(T[x * M + y]);
            x++;
        } else {
            path.push_back(T[x * M + y]);
            y++;
        }
    }
    path.push_back(T[N * M - 1]);
    
    sort(path.begin(), path.end());
    
    for (int i = 0; i < N + M - 1; ++i) {
        cout << path[i] << " ";
    }
    cout << endl;
    
    return 0;
}