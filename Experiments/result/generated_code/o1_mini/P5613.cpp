#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 1001
#define MAX_M 1011
#define MAX_QUEUE 2000000

typedef struct{
    int pos;
    int m;
} State;

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    bool special[MAX_N];
    for(int i=0;i<=n;i++) special[i]=false;
    for(int i=0;i<k;i++){
        int a;
        scanf("%d", &a);
        if(a <= n) special[a]=true;
    }
    
    bool visited[MAX_N][MAX_M];
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=m+k+1 && j < MAX_M; j++) {
            visited[i][j] = false;
        }
    }
    
    State queue_arr[MAX_QUEUE];
    int front =0, rear=0;
    queue_arr[rear].pos =0;
    queue_arr[rear].m =m;
    rear++;
    visited[0][m] = true;
    int time =0;
    
    while(front < rear){
        int current_level_size = rear - front;
        for(int i=0;i<current_level_size;i++, front++){
            State current = queue_arr[front];
            int next_pos = current.pos + current.m;
            if(next_pos >= n){
                printf("%d", time +1);
                return 0;
            }
            if(next_pos > n) next_pos = n;
            int next_m = current.m;
            if(special[next_pos]){
                next_m +=1;
                if(next_m >= MAX_M) next_m = MAX_M-1;
            }
            if(next_pos <= n && next_m < MAX_M && !visited[next_pos][next_m]){
                visited[next_pos][next_m] = true;
                queue_arr[rear].pos = next_pos;
                queue_arr[rear].m = next_m;
                rear++;
                if(rear >= MAX_QUEUE){
                    // Queue overflow, should not happen with given constraints
                    break;
                }
            }
        }
        time++;
    }
    
    return 0;
}