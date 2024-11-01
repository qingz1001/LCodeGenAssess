#include <vector>
#include <algorithm>

std::vector<int> r;
int k, n;

void init(int k, std::vector<int> r) {
    ::k = k;
    ::r = r;
    n = r.size();
}

int compare_plants(int x, int y) {
    if (x > y) std::swap(x, y);

    int count_x = 0, count_y = 0;

    for (int i = 0; i < k - 1; ++i) {
        int idx = (x + i + 1) % n;
        if (r[idx] > r[x]) count_x++;
    }

    for (int i = 0; i < k - 1; ++i) {
        int idx = (y + i + 1) % n;
        if (r[idx] > r[y]) count_y++;
    }

    if (count_x > count_y) return 1;
    if (count_x < count_y) return -1;
    return 0;
}