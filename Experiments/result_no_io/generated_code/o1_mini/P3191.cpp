#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 20
#define MAXM 20
#define MAXDOOR 80
#define MAXPEOPLE 400
#define INF 1000000

typedef struct {
    int x, y;
} Position;

typedef struct {
    int x, y;
    int min_distance;
    int distances[MAXDOOR];
} Person;

typedef struct {
    int x, y;
    int dist;
} QueueNode;

int N, M;
char grid[MAXN][MAXM + 1];
Position doors[MAXDOOR];
int num_doors = 0;
Person people[MAXPEOPLE];
int num_people = 0;
int distance_map[MAXDOOR][MAXN][MAXM];
int doorAvailable[MAXDOOR];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int min(int a, int b){
    return a < b ? a : b;
}

void bfs(int door_idx) {
    int dist[MAXN][MAXM];
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            dist[i][j] = INF;
        }
    }
    QueueNode queue[MAXN*MAXM];
    int front = 0, rear = 0;
    int sx = doors[door_idx].x;
    int sy = doors[door_idx].y;
    dist[sx][sy] = 0;
    queue[rear++] = (QueueNode){sx, sy, 0};
    while(front < rear){
        QueueNode current = queue[front++];
        for(int d=0; d<4; d++){
            int nx = current.x + dx[d];
            int ny = current.y + dy[d];
            if(nx >=0 && nx < N && ny >=0 && ny < M && grid[nx][ny] != 'X' && dist[nx][ny]==INF){
                dist[nx][ny] = dist[current.x][current.y] + 1;
                queue[rear++] = (QueueNode){nx, ny, dist[nx][ny]};
            }
        }
    }
    for(int i=0;i<num_people;i++){
        distance_map[door_idx][people[i].x][people[i].y] = dist[people[i].x][people[i].y];
    }
}

int compare(const void *a, const void *b){
    Person pa = *(Person*)a;
    Person pb = *(Person*)b;
    if(pa.min_distance != pb.min_distance)
        return pa.min_distance - pb.min_distance;
    return 0;
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=0;i<N;i++) {
        scanf("%s", grid[i]);
    }
    // Collect doors and people
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            if(grid[i][j] == 'D'){
                doors[num_doors].x = i;
                doors[num_doors].y = j;
                num_doors++;
            }
            if(grid[i][j] == '.'){
                people[num_people].x = i;
                people[num_people].y = j;
                people[num_people].min_distance = INF;
                num_people++;
            }
        }
    }
    // BFS for each door
    for(int d=0; d<num_doors; d++) {
        bfs(d);
    }
    // Compute distances for each person
    for(int i=0;i<num_people;i++){
        int min_dist = INF;
        for(int d=0; d<num_doors; d++){
            int dist = distance_map[d][people[i].x][people[i].y];
            people[i].distances[d] = dist;
            if(dist < min_dist){
                min_dist = dist;
            }
        }
        people[i].min_distance = min_dist;
    }
    // Check for impossible
    int impossible = 0;
    for(int i=0;i<num_people;i++) {
        if(people[i].min_distance == INF){
            impossible = 1;
            break;
        }
    }
    if(impossible){
        printf("impossible\n");
        return 0;
    }
    // Sort people by min_distance
    qsort(people, num_people, sizeof(Person), compare);
    // Initialize doorAvailable
    for(int d=0; d<num_doors; d++) doorAvailable[d] = 0;
    // Assign people to doors
    int total_time = 0;
    for(int i=0;i<num_people;i++) {
        int best_time = INF;
        int best_door = -1;
        for(int d=0; d<num_doors; d++) {
            int dist = people[i].distances[d];
            if(dist == INF) continue;
            int evac_time = (dist > doorAvailable[d] ? dist : doorAvailable[d]) +1;
            if(evac_time < best_time){
                best_time = evac_time;
                best_door = d;
            }
        }
        if(best_door == -1){
            impossible = 1;
            break;
        }
        doorAvailable[best_door] = best_time;
        if(best_time > total_time) total_time = best_time;
    }
    if(impossible){
        printf("impossible\n");
    }
    else{
        printf("%d\n", total_time);
    }
    return 0;
}