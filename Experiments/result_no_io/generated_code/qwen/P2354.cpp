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
    
    vector<int> T(N * M);
    for (int i = 0; i < N * M; ++i) {
        T[i] = (a * x0 * x0 + b * x0 + c) % d;
        x0 = T[i];
    }
    
    for (int i = 0; i < Q; ++i) {
        int u, v;
        cin >> u >> v;
        swap(T[u - 1], T[v - 1]);
    }
    
    vector<vector<int>> board(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            board[i][j] = T[(i - 1) * M + j];
        }
    }
    
    vector<int> path;
    int x = 0, y = 0;
    while (x != N - 1 || y != M - 1) {
        if (y == M - 1 || (x < N - 1 && board[x + 1][y] < board[x][y + 1])) {
            path.push_back(board[x][y]);
            ++x;
        } else {
            path.push_back(board[x][y]);
            ++y;
        }
    }
    path.push_back(board[N - 1][M - 1]);
    
    sort(path.begin(), path.end());
    
    for (int num : path) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}