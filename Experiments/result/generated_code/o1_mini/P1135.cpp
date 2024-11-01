#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 201
#define MAX_QUEUE 40000

typedef struct {
    int floor;
    int steps;
} Node;

int main(){
    int N, A, B;
    int K[MAX_N];
    scanf("%d %d %d", &N, &A, &B);
    for(int i=1;i<=N;i++) scanf("%d", &K[i]);

    int visited[MAX_N];
    memset(visited, 0, sizeof(visited));

    Node queue[MAX_QUEUE];
    int front=0, rear=0;
    queue[rear].floor = A;
    queue[rear].steps = 0;
    rear++;
    visited[A] = 1;

    while(front < rear){
        Node current = queue[front++];
        if(current.floor == B){
            printf("%d", current.steps);
            return 0;
        }

        // Up
        if(K[current.floor] >0){
            int next = current.floor + K[current.floor];
            if(next <= N && !visited[next]){
                visited[next]=1;
                queue[rear].floor = next;
                queue[rear].steps = current.steps +1;
                rear++;
            }
            // Down
            next = current.floor - K[current.floor];
            if(next >=1 && !visited[next]){
                visited[next]=1;
                queue[rear].floor = next;
                queue[rear].steps = current.steps +1;
                rear++;
            }
        }
    }
    printf("-1");
    return 0;
}