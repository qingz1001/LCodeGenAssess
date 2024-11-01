#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int factorial_arr[10] = {1,1,2,6,24,120,720,5040,40320,362880};

int get_rank(char s[9]){
    int rank = 0;
    for(int i=0;i<9;i++){
        int cnt = 0;
        for(int j=i+1;j<9;j++) if(s[j] < s[i]) cnt++;
        rank += cnt * factorial_arr[8-i];
    }
    return rank;
}

void rank_to_string(int rank, char s[9]){
    char elems[9] = {'0','1','2','3','4','5','6','7','8'};
    for(int i=0;i<9;i++){
        int f = factorial_arr[8-i];
        int idx = rank / f;
        s[i] = elems[idx];
        for(int j=idx;j<8-i;j++) elems[j] = elems[j+1];
        rank %= f;
    }
}

int main(){
    char input[10];
    scanf("%s", input);
    char target_s[10] = "123804765";
    int target_rank = get_rank(target_s);
    int initial_rank = get_rank(input);
    if(initial_rank == target_rank){
        printf("0");
        return 0;
    }
    int adj[9][4] = {
        {1,3,-1,-1},
        {0,2,4,-1},
        {1,5,-1,-1},
        {0,4,6,-1},
        {1,3,5,7},
        {2,4,8,-1},
        {3,7,-1,-1},
        {4,6,8,-1},
        {5,7,-1,-1}
    };
    int visited[362880];
    memset(visited, -1, sizeof(visited));
    int queue[362880];
    int front = 0, back = 0;
    queue[back++] = initial_rank;
    visited[initial_rank] = 0;
    while(front < back){
        int current = queue[front++];
        char current_s[9];
        rank_to_string(current, current_s);
        int zero_pos;
        for(zero_pos=0; zero_pos<9; zero_pos++) if(current_s[zero_pos] == '0') break;
        for(int i=0;i<4;i++){
            if(adj[zero_pos][i]==-1) continue;
            char next_s[9];
            memcpy(next_s, current_s, 9);
            char temp = next_s[zero_pos];
            next_s[zero_pos] = next_s[adj[zero_pos][i]];
            next_s[adj[zero_pos][i]] = temp;
            int next_rank = get_rank(next_s);
            if(visited[next_rank]==-1){
                visited[next_rank] = visited[current] + 1;
                if(next_rank == target_rank){
                    printf("%d", visited[next_rank]);
                    return 0;
                }
                queue[back++] = next_rank;
            }
        }
    }
    return 0;
}