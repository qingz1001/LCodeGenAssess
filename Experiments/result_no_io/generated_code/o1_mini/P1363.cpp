#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define maximum size
#define MAXN 1500
#define MAXM 1500

typedef struct {
    int i;
    int j;
    int k;
    int l;
} State;

// Queue implementation
typedef struct {
    State *data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

Queue* createQueue(int capacity){
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->data = (State*)malloc(sizeof(State)*capacity);
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->capacity = capacity;
    return q;
}

void enqueue(Queue *q, State s){
    if(q->size == q->capacity){
        q->capacity *=2;
        q->data = (State*)realloc(q->data, sizeof(State)*q->capacity);
    }
    q->data[q->rear++] = s;
    q->rear %= q->capacity;
    q->size++;
}

State dequeueq(Queue *q){
    State s = q->data[q->front++];
    q->front %= q->capacity;
    q->size--;
    return s;
}

int isEmpty(Queue *q){
    return q->size ==0;
}

int main(){
    int N, M;
    while(scanf("%d %d", &N, &M) != EOF){
        char **grid = (char**)malloc(N * sizeof(char*));
        for(int i=0;i<N;i++){
            grid[i] = (char*)malloc((M+2)*sizeof(char));
            scanf("%s", grid[i]);
        }
        int si, sj;
        int found = 0;
        for(int i=0;i<N && !found;i++) {
            for(int j=0;j<M && !found;j++) {
                if(grid[i][j] == 'S'){
                    si = i;
                    sj = j;
                    found =1;
                }
            }
        }
        // Initialize visited arrays
        int **visited_k = (int**)malloc(N * sizeof(int*));
        int **visited_l = (int**)malloc(N * sizeof(int*));
        for(int i=0;i<N;i++){
            visited_k[i] = (int*)malloc(M * sizeof(int));
            visited_l[i] = (int*)malloc(M * sizeof(int));
            for(int j=0; j<M; j++){
                visited_k[i][j] = 0x7FFFFFFF;
                visited_l[i][j] = 0x7FFFFFFF;
            }
        }
        // Initialize BFS
        Queue *q = createQueue(N*M*4);
        State start;
        start.i = si;
        start.j = sj;
        start.k =0;
        start.l =0;
        enqueue(q, start);
        visited_k[si][sj] =0;
        visited_l[si][sj] =0;
        int escaped =0;
        // Directions: up, down, left, right
        int di[4] = {-1, 1, 0, 0};
        int dj[4] = {0, 0, -1, 1};
        while(!isEmpty(q) && !escaped){
            State current = dequeueq(q);
            for(int d=0; d<4 && !escaped; d++){
                int ni = current.i + di[d];
                int nj = current.j + dj[d];
                int nk = current.k;
                int nl = current.l;
                if(ni <0){
                    nk = current.k -1;
                    ni += N;
                }
                else if(ni >=N){
                    nk = current.k +1;
                    ni -= N;
                }
                if(nj <0){
                    nl = current.l -1;
                    nj += M;
                }
                else if(nj >=M){
                    nl = current.l +1;
                    nj -= M;
                }
                if(grid[ni][nj] != '#' ){
                    if(visited_k[ni][nj] == 0x7FFFFFFF){
                        visited_k[ni][nj] = current.k + ((di[d]==-1)? -1 : (di[d]==1)? 1 : 0);
                        visited_l[ni][nj] = current.l + ((dj[d]==-1)? -1 : (dj[d]==1)? 1 : 0);
                        State next;
                        next.i = ni;
                        next.j = nj;
                        next.k = visited_k[ni][nj];
                        next.l = visited_l[ni][nj];
                        enqueue(q, next);
                    }
                    else{
                        int dk = current.k + ((di[d]==-1)? -1 : (di[d]==1)? 1 : 0) - visited_k[ni][nj];
                        int dl = current.l + ((dj[d]==-1)? -1 : (dj[d]==1)? 1 : 0) - visited_l[ni][nj];
                        if(dk !=0 || dl !=0){
                            printf("Yes\n");
                            escaped =1;
                        }
                    }
                }
            }
        }
        if(!escaped){
            printf("No\n");
        }
        // Free memory
        for(int i=0;i<N;i++) free(grid[i]);
        free(grid);
        for(int i=0;i<N;i++){
            free(visited_k[i]);
            free(visited_l[i]);
        }
        free(visited_k);
        free(visited_l);
        free(q->data);
        free(q);
    }
}