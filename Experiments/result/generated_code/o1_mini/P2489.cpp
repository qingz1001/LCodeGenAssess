#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_M 30
#define MAX_N 30
#define MAX_K 5
#define MAX_H 5
#define MAX_KNOW 243
#define MAX_POW3 243

int m, n, k, H;
char grid[MAX_M][MAX_N + 1];
long long p_vals[32];
double sum_p[243];
double sum_p_safe[243][5];
double sum_p_harmful[243][5];
double memo_table[30][30][6][243];
int start_x, start_y;
int end_positions[MAX_M * MAX_N][2];
int end_count = 0;

// Function to convert knowledge_id to base-3 digits
void knowledge_digits(int knowledge_id, int digits[]) {
    for(int t=0;t<k;t++) {
        digits[t] = knowledge_id % 3;
        knowledge_id /=3;
    }
}

// Function to check if i matches the knowledge state
int matches(int knowledge_id, int i) {
    int digits[MAX_K];
    knowledge_digits(knowledge_id, digits);
    for(int t=0;t<k;t++) {
        if(digits[t]==1 && ((i>>t)&1)) return 0;
        if(digits[t]==2 && !((i>>t)&1)) return 0;
    }
    return 1;
}

// Function to set trap t to status (1: safe, 2: harmful)
int set_knowledge(int knowledge_id, int t, int status) {
    int digits[MAX_K];
    knowledge_digits(knowledge_id, digits);
    digits[t] = status;
    int new_id =0;
    int power =1;
    for(int tt=0; tt<k; tt++) {
        new_id += digits[tt] * power;
        power *=3;
    }
    return new_id;
}

// Recursive function to get probability
double get_prob(int x, int y, int h, int knowledge_id) {
    if(grid[x][y] == '@') return 1.0;
    if(h <=0) return 0.0;
    if(memo_table[x][y][h][knowledge_id] >= -0.5) {
        return memo_table[x][y][h][knowledge_id];
    }
    memo_table[x][y][h][knowledge_id] = 0.0;
    double max_prob =0.0;
    // Directions: up, down, left, right
    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};
    for(int dir=0; dir<4; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if(nx <0 || nx >=m || ny <0 || ny >=n) continue;
        char cell = grid[nx][ny];
        if(cell == '#') continue;
        if(cell == '.' || cell == '@' || cell == '$') {
            double prob = get_prob(nx, ny, h, knowledge_id);
            if(prob > max_prob) max_prob = prob;
            continue;
        }
        // It's a trap
        int t = cell - 'A';
        if(t <0 || t >=k) continue;
        // Determine the state of trap t
        int digits[MAX_K];
        knowledge_digits(knowledge_id, digits);
        if(digits[t]==1 || digits[t]==2) {
            // Known
            if(digits[t]==2) {
                // Harmful
                if(h-1 <=0) {
                    // Dead
                    // prob +=0
                }
                else {
                    double prob = get_prob(nx, ny, h-1, knowledge_id);
                    if(prob > max_prob) max_prob = prob;
                }
            }
            else {
                // Safe
                double prob = get_prob(nx, ny, h, knowledge_id);
                if(prob > max_prob) max_prob = prob;
            }
        }
        else {
            // Unknown
            if(sum_p[knowledge_id] ==0.0) continue;
            double p_harm = sum_p_harmful[knowledge_id][t] / sum_p[knowledge_id];
            double p_safe = sum_p_safe[knowledge_id][t] / sum_p[knowledge_id];
            // If harm
            double prob_harm =0.0;
            if(h-1 >0) {
                int new_id_harm = set_knowledge(knowledge_id, t, 2);
                prob_harm = get_prob(nx, ny, h-1, new_id_harm);
            }
            // If safe
            int new_id_safe = set_knowledge(knowledge_id, t, 1);
            double prob_safe_result = get_prob(nx, ny, h, new_id_safe);
            double total_prob = p_harm * prob_harm + p_safe * prob_safe_result;
            if(total_prob > max_prob) max_prob = total_prob;
        }
    }
    memo_table[x][y][h][knowledge_id] = max_prob;
    return max_prob;
}

int main(){
    memset(memo_table, -1, sizeof(memo_table));
    scanf("%d %d %d %d", &m, &n, &k, &H);
    for(int i=0;i<m;i++) {
        scanf("%s", grid[i]);
        for(int j=0;j<n;j++) {
            if(grid[i][j] == '$') {
                start_x = i;
                start_y = j;
            }
            if(grid[i][j] == '@') {
                end_positions[end_count][0] =i;
                end_positions[end_count][1] =j;
                end_count++;
            }
        }
    }
    int total_p = 1<<k;
    for(int i=0;i<total_p;i++) {
        scanf("%lld", &p_vals[i]);
    }
    // Precompute sum_p and sum_p_safe/harmful
    for(int knowledge_id=0; knowledge_id < pow(3,k); knowledge_id++) {
        sum_p[knowledge_id] =0.0;
        for(int t=0;t<k;t++) {
            sum_p_safe[knowledge_id][t] =0.0;
            sum_p_harmful[knowledge_id][t] =0.0;
        }
        for(int i=0;i<(1<<k);i++) {
            if(matches(knowledge_id, i)) {
                sum_p[knowledge_id] += (double)p_vals[i];
                for(int t=0;t<k;t++) {
                    if( ((i>>t)&1) ) {
                        sum_p_harmful[knowledge_id][t] += (double)p_vals[i];
                    }
                    else {
                        sum_p_safe[knowledge_id][t] += (double)p_vals[i];
                    }
                }
            }
        }
    }
    double result = get_prob(start_x, start_y, H, 0);
    // Round to three decimal places
    result += 1e-9;
    printf("%.3lf\n", result);
    return 0;
}