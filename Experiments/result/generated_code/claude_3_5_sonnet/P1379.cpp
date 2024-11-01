#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_QUEUE 362880
#define TARGET_STATE 123804765

typedef struct {
    int state;
    int step;
} Node;

int factorial[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
int dir[4] = {1, -1, 3, -3};
bool visited[362880] = {false};
Node queue[MAX_QUEUE];

int cantor(int state) {
    int a[9], hash = 0;
    for (int i = 8; i >= 0; i--) {
        a[i] = state % 10;
        state /= 10;
    }
    for (int i = 0; i < 9; i++) {
        int cnt = 0;
        for (int j = i + 1; j < 9; j++) {
            if (a[j] < a[i]) cnt++;
        }
        hash += cnt * factorial[8 - i];
    }
    return hash;
}

int bfs(int start) {
    int front = 0, rear = 0;
    queue[rear++] = (Node){start, 0};
    visited[cantor(start)] = true;
    
    while (front < rear) {
        Node cur = queue[front++];
        if (cur.state == TARGET_STATE) return cur.step;
        
        int zero_pos = 0;
        int temp = cur.state;
        while (temp % 10 != 0) {
            temp /= 10;
            zero_pos++;
        }
        
        for (int i = 0; i < 4; i++) {
            int new_pos = zero_pos + dir[i];
            if (new_pos < 0 || new_pos > 8 || (zero_pos % 3 == 0 && i == 1) || (zero_pos % 3 == 2 && i == 0)) 
                continue;
            
            int new_state = cur.state;
            int power = 1;
            for (int j = 0; j < 9; j++) {
                if (j == zero_pos || j == new_pos) {
                    int digit = (new_state / power) % 10;
                    new_state -= digit * power;
                    new_state += digit * (j == zero_pos ? (int)power * pow(10, new_pos - zero_pos) : power / pow(10, new_pos - zero_pos));
                }
                power *= 10;
            }
            
            int hash = cantor(new_state);
            if (!visited[hash]) {
                visited[hash] = true;
                queue[rear++] = (Node){new_state, cur.step + 1};
            }
        }
    }
    return -1;
}

int main() {
    int start;
    scanf("%d", &start);
    printf("%d\n", bfs(start));
    return 0;
}