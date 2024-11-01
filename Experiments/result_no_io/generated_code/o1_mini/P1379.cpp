#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TARGET "123804765"
#define MAX_STATE 362880
#define QUEUE_SIZE 1000000

int factorial[10];
int visited[MAX_STATE];
char queue_states[QUEUE_SIZE][10];
int queue_steps[QUEUE_SIZE];
int front = 0, rear = 0;

void precompute_factorial() {
    factorial[0] = 1;
    for(int i=1;i<=9;i++) {
        factorial[i] = factorial[i-1]*i;
    }
}

int get_rank(char *s) {
    int rank = 0;
    int used[10] = {0};
    for(int i=0;i<9;i++) {
        int smaller = 0;
        int num = s[i]-'0';
        for(int j=0;j<num;j++) {
            if(!used[j]) smaller++;
        }
        rank += smaller * factorial[8-i];
        used[num] = 1;
    }
    return rank;
}

int main(){
    precompute_factorial();
    char initial[10];
    for(int i=0;i<9;i++) {
        char c;
        scanf(" %c", &c);
        initial[i] = c;
    }
    initial[9] = '\0';
    int target_rank = get_rank((char*)TARGET);
    int initial_rank = get_rank(initial);
    if(initial_rank == target_rank){
        printf("0");
        return 0;
    }
    // Initialize BFS
    strcpy(queue_states[rear], initial);
    queue_steps[rear] = 0;
    rear++;
    visited[initial_rank] = 1;
    // Directions: up, down, left, right
    int dirs[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
    while(front < rear){
        char current[10];
        strcpy(current, queue_states[front]);
        int steps = queue_steps[front];
        front++;
        // Find zero position
        int zero_pos;
        for(zero_pos=0; zero_pos<9; zero_pos++) if(current[zero_pos]=='0') break;
        int x = zero_pos / 3;
        int y = zero_pos % 3;
        for(int d=0;d<4;d++){
            int new_x = x + dirs[d][0];
            int new_y = y + dirs[d][1];
            if(new_x >=0 && new_x <3 && new_y >=0 && new_y <3){
                int new_pos = new_x * 3 + new_y;
                char next[10];
                strcpy(next, current);
                // Swap zero with the target
                char temp = next[zero_pos];
                next[zero_pos] = next[new_pos];
                next[new_pos] = temp;
                // Get rank
                int next_rank = get_rank(next);
                if(!visited[next_rank]){
                    visited[next_rank] = 1;
                    // Check if target
                    if(next_rank == target_rank){
                        printf("%d", steps+1);
                        return 0;
                    }
                    // Enqueue
                    strcpy(queue_states[rear], next);
                    queue_steps[rear] = steps +1;
                    rear++;
                }
            }
        }
    }
    return 0;
}