#include <stdio.h>
#include <set>
#include <map>
#include <vector>
#include <string>
using namespace std;

const int N = 100005;

int n, m, q;
map<int, set<int>> room;
map<pair<int, int>, int> experiment;

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= q; ++i) {
        char op;
        int x, y;
        scanf(" %c%d%d", &op, &x, &y);
        if (op == 'C') {
            // 让第 x 个人去房间 y
            room[y].insert(x);
        } else if (op == 'W') {
            // 让区间 [l, r] 的房间做实验
            int points = 0;
            for (int j = x; j <= y; ++j) {
                points += room[j].size() - experiment[make_pair(x, j)];
                experiment[make_pair(x, j)] = room[j].size();
            }
            printf("%d\n", points);
        }
    }
    return 0;
}