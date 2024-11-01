#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> room(n + 1, 1); // 1-indexed room assignments
    unordered_map<int, unordered_set<int>> experiments; // room -> set of groups

    while (q--) {
        string op;
        cin >> op;
        if (op == "C") {
            int i, j;
            cin >> i >> j;
            room[i] = j;
        } else if (op == "W") {
            int l, r;
            cin >> l >> r;
            int points = 0;
            for (int k = l; k <= r; ++k) {
                unordered_set<int> current_group;
                for (int person : experiments[k]) {
                    current_group.insert(room[person]);
                }
                for (int person : current_group) {
                    if (experiments[k].find(person) == experiments[k].end()) {
                        points += current_group.size();
                        experiments[k].insert(person);
                    }
                }
            }
            cout << points << endl;
        }
    }

    return 0;
}