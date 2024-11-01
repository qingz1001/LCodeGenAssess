#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned short parent_state[65536];
unsigned char move_pos1[65536];
unsigned char move_pos2[65536];
unsigned char visited[8193]; // 65536 / 8 = 8192, +1 for safety

unsigned short read_state() {
    unsigned short state = 0;
    char line[5];
    for(int r=0;r<4;r++) {
        scanf("%s", line);
        for(int c=0;c<4;c++) {
            if(line[c] == '1') {
                state |= (1 << (r * 4 + c));
            }
        }
    }
    return state;
}

int main(){
    unsigned short initial, target;
    initial = read_state();
    target = read_state();
    if(initial == target){
        printf("0\n");
        return 0;
    }
    // Initialize visited
    memset(visited, 0, sizeof(visited));
    // Initialize queue
    unsigned short queue_states[65536];
    int front = 0, rear = 0;
    queue_states[rear++] = initial;
    // Mark initial as visited
    visited[initial / 8] |= (1 << (initial % 8));
    // BFS
    while(front < rear){
        unsigned short current = queue_states[front++];
        // Get row and column for each position
        for(int pos=0; pos<16; pos++){
            // Current position's row and col
            int r = pos / 4;
            int c = pos % 4;
            // Check all four directions
            // Up
            if(r > 0){
                int neighbor = (r-1)*4 + c;
                unsigned short next = current;
                // Swap pos and neighbor
                unsigned short bit1 = (current >> pos) & 1;
                unsigned short bit2 = (current >> neighbor) & 1;
                if(bit1 != bit2){
                    next ^= (1 << pos);
                    next ^= (1 << neighbor);
                }
                if(!(visited[next / 8] & (1 << (next % 8)))){
                    visited[next / 8] |= (1 << (next % 8));
                    parent_state[next] = current;
                    move_pos1[next] = pos;
                    move_pos2[next] = neighbor;
                    queue_states[rear++] = next;
                    if(next == target){
                        front = rear; // Break outer loop
                        break;
                    }
                }
            }
            // Down
            if(r < 3){
                int neighbor = (r+1)*4 + c;
                unsigned short next = current;
                unsigned short bit1 = (current >> pos) & 1;
                unsigned short bit2 = (current >> neighbor) & 1;
                if(bit1 != bit2){
                    next ^= (1 << pos);
                    next ^= (1 << neighbor);
                }
                if(!(visited[next / 8] & (1 << (next % 8)))){
                    visited[next / 8] |= (1 << (next % 8));
                    parent_state[next] = current;
                    move_pos1[next] = pos;
                    move_pos2[next] = neighbor;
                    queue_states[rear++] = next;
                    if(next == target){
                        front = rear; // Break outer loop
                        break;
                    }
                }
            }
            // Left
            if(c > 0){
                int neighbor = r*4 + (c-1);
                unsigned short next = current;
                unsigned short bit1 = (current >> pos) & 1;
                unsigned short bit2 = (current >> neighbor) & 1;
                if(bit1 != bit2){
                    next ^= (1 << pos);
                    next ^= (1 << neighbor);
                }
                if(!(visited[next / 8] & (1 << (next % 8)))){
                    visited[next / 8] |= (1 << (next % 8));
                    parent_state[next] = current;
                    move_pos1[next] = pos;
                    move_pos2[next] = neighbor;
                    queue_states[rear++] = next;
                    if(next == target){
                        front = rear; // Break outer loop
                        break;
                    }
                }
            }
            // Right
            if(c < 3){
                int neighbor = r*4 + (c+1);
                unsigned short next = current;
                unsigned short bit1 = (current >> pos) & 1;
                unsigned short bit2 = (current >> neighbor) & 1;
                if(bit1 != bit2){
                    next ^= (1 << pos);
                    next ^= (1 << neighbor);
                }
                if(!(visited[next / 8] & (1 << (next % 8)))){
                    visited[next / 8] |= (1 << (next % 8));
                    parent_state[next] = current;
                    move_pos1[next] = pos;
                    move_pos2[next] = neighbor;
                    queue_states[rear++] = next;
                    if(next == target){
                        front = rear; // Break outer loop
                        break;
                    }
                }
            }
        }
    }
    // Reconstruct path
    unsigned short current = target;
    int steps = 0;
    int move1[10000], move2[10000];
    while(current != initial){
        move1[steps] = move_pos1[current];
        move2[steps] = move_pos2[current];
        current = parent_state[current];
        steps++;
    }
    // Print
    printf("%d\n", steps);
    for(int i=steps-1;i>=0;i--){
        int a = move1[i] / 4 + 1;
        int b = move1[i] % 4 + 1;
        int c = move2[i] / 4 + 1;
        int d = move2[i] % 4 + 1;
        printf("%d%d%d%d\n", a, b, c, d);
    }
    return 0;
}