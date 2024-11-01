#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n;
int pos[46], target_pos[46];

// Function to read disks for a specific peg
void read_pegs(int peg, int pos[]) {
    char buffer[1000];
    if(!fgets(buffer, sizeof(buffer), stdin)) return;
    char *token = strtok(buffer, " \n");
    if(token == NULL) return;
    if(token[0] == '0') return;
    while(token != NULL){
        int disk = atoi(token);
        pos[disk] = peg;
        token = strtok(NULL, " \n");
    }
}

// Recursive function to perform Hanoi moves
void hanoi(int k, int pos[], int target[], long long *count){
    if(k == 0) return;
    if(pos[k] != target[k]){
        int from = pos[k];
        int to = target[k];
        int aux = 6 - from - to;
        hanoi(k-1, pos, target, count);
        printf("move %d from %c to %c\n", k, 'A' + from -1, 'A' + to -1);
        (*count)++;
        pos[k] = to;
        hanoi(k-1, pos, target, count);
    }
    else{
        hanoi(k-1, pos, target, count);
    }
}

int main(){
    scanf("%d", &n);
    getchar(); // Consume the newline after the first number

    // Initialize positions
    memset(pos, 0, sizeof(pos));
    memset(target_pos, 0, sizeof(target_pos));

    // Read initial state for pegs A, B, C
    for(int peg=1; peg<=3; peg++){
        read_pegs(peg, pos);
    }

    // Read target state for pegs A, B, C
    for(int peg=1; peg<=3; peg++){
        read_pegs(peg, target_pos);
    }

    // Perform Hanoi moves and count them
    long long move_count = 0;
    hanoi(n, pos, target_pos, &move_count);

    // Print the total number of moves
    printf("%lld\n", move_count);
    return 0;
}