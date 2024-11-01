pp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<vector<char>> marble(N, vector<char>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> marble[i][j];
        }
    }

    int max_score = -1;

    for (int top_row = 0; top_row < N; ++top_row) {
        for (int bottom_row = top_row + 1; bottom_row < N; ++bottom_row) {
            if (marble[top_row][0] == '*' || marble[bottom_row][0] == '*') continue;

            int top_area = 0, bottom_area = 0;
            bool valid_top = false, valid_bottom = false;

            for (int col = 0; col < N; ++col) {
                if (marble[top_row][col] == '.') {
                    if (!valid_top) {
                        top_area += 1;
                        valid_top = true;
                    }
                } else {
                    valid_top = false;
                }

                if (marble[bottom_row][col] == '.') {
                    if (!valid_bottom) {
                        bottom_area += 1;
                        valid_bottom = true;
                    }
                } else {
                    valid_bottom = false;
                }
            }

            if (valid_top && valid_bottom && top_area > 0 && bottom_area > 0) {
                max_score = max(max_score, top_area * bottom_area);
            }
        }
    }

    cout << max_score << endl;

    return 0;
}