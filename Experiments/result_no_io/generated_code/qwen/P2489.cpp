#include <stdio.h>
#include <stdlib.h>

#define MAXM 30
#define MAXN 29
#define MAXK 5
#define EPSILON 1e-9

int m, n, k, H;
char grid[MAXM][MAXN];
double p[1 << MAXK];

typedef struct {
    int x, y;
    double prob;
} State;

State states[2 * MAXM * MAXN];
int state_count;

void read_input() {
    scanf("%d %d %d %d", &m, &n, &k, &H);
    for (int i = 0; i < m; ++i) {
        scanf("%s", grid[i]);
    }
    for (int i = 0; i < (1 << k); ++i) {
        scanf("%lf", &p[i]);
    }
}

int get_state_index(int x, int y) {
    return x * n + y;
}

double get_probability(int state_index) {
    return states[state_index].prob;
}

void set_probability(int state_index, double prob) {
    states[state_index].prob = prob;
}

void add_state(int x, int y, double prob) {
    states[state_count++] = (State){x, y, prob};
}

int is_valid(int x, int y) {
    return x >= 0 && x < m && y >= 0 && y < n && grid[x][y] != '#';
}

double calculate_probability(int x, int y, int trap_mask) {
    if (!is_valid(x, y)) return 0.0;
    if (grid[x][y] == '$') return 1.0;
    if (grid[x][y] == '@') return 1.0;
    if (grid[x][y] == '.') return 1.0;

    int trap_type = grid[x][y] - 'A';
    int current_mask = (trap_mask >> trap_type) & 1;
    double probability = p[current_mask];

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    double total_prob = 0.0;
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int new_trap_mask = trap_mask ^ (1 << trap_type);
        total_prob += probability * calculate_probability(nx, ny, new_trap_mask);
    }

    return total_prob;
}

double solve() {
    add_state(0, 0, 1.0);

    while (state_count > 0) {
        State current = states[--state_count];
        int x = current.x, y = current.y;
        double prob = current.prob;

        if (grid[x][y] == '$' || grid[x][y] == '@' || grid[x][y] == '.') {
            continue;
        }

        int trap_type = grid[x][y] - 'A';
        int current_mask = (current.prob >> trap_type) & 1;
        double probability = p[current_mask];

        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int new_trap_mask = current_mask ^ (1 << trap_type);
            double new_prob = prob * probability;
            if (new_prob > EPSILON) {
                add_state(nx, ny, new_prob);
            }
        }
    }

    double result = 0.0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '@') {
                result += calculate_probability(i, j, 0);
            }
        }
    }

    return result;
}

int main() {
    read_input();
    printf("%.3f\n", solve());
    return 0;
}