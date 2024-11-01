pp
#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 1e5 + 5;

vector<set<int>> rooms(MAXN);
vector<int> location(MAXN);
vector<set<int>> experimented(MAXN);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    // 初始时所有人都在1号房间
    for (int i = 1; i <= n; ++i) {
        rooms[1].insert(i);
        location[i] = 1;
    }

    while (q--) {
        char op;
        cin >> op;

        if (op == 'C') {
            int i, j;
            cin >> i >> j;
            rooms[location[i]].erase(i);
            rooms[j].insert(i);
            location[i] = j;
        } else if (op == 'W') {
            int l, r;
            cin >> l >> r;
            int points = 0;
            for (int room = l; room <= r; ++room) {
                set<int> new_people;
                for (int person : rooms[room]) {
                    if (experimented[room].find(person) == experimented[room].end()) {
                        new_people.insert(person);
                    }
                }
                points += new_people.size();
                experimented[room].insert(new_people.begin(), new_people.end());
            }
            cout << points << '\n';
        }
    }

    return 0;
}