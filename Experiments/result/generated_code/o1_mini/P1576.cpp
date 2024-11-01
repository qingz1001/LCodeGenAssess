#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 2005
#define MAXM 100005
#define INF 1e18

typedef struct {
    int to;
    double multiplier;
} Edge;

Edge edges[MAXM];
int head_list[MAXN];
int edge_cnt = 0;

typedef struct {
    double s;
    int node;
} HeapNode;

HeapNode heap_arr[MAXM];
int heap_size = 0;

void swap(HeapNode *a, HeapNode *b){
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heap_push(double s, int node){
    heap_size++;
    heap_arr[heap_size].s = s;
    heap_arr[heap_size].node = node;
    int i = heap_size;
    while(i > 1){
        int parent = i / 2;
        if(heap_arr[parent].s > heap_arr[i].s){
            swap(&heap_arr[parent], &heap_arr[i]);
            i = parent;
        }
        else break;
    }
}

int heap_pop(double *s, int *node){
    if(heap_size == 0) return 0;
    *s = heap_arr[1].s;
    *node = heap_arr[1].node;
    heap_arr[1] = heap_arr[heap_size];
    heap_size--;
    int i = 1;
    while(1){
        int left = 2*i;
        int right = 2*i+1;
        int smallest = i;
        if(left <= heap_size && heap_arr[left].s < heap_arr[smallest].s){
            smallest = left;
        }
        if(right <= heap_size && heap_arr[right].s < heap_arr[smallest].s){
            smallest = right;
        }
        if(smallest != i){
            swap(&heap_arr[i], &heap_arr[smallest]);
            i = smallest;
        }
        else break;
    }
    return 1;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i =1;i<=n;i++) head_list[i]=-1;
    for(int i=0;i<m;i++){
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        edges[edge_cnt].to = x;
        edges[edge_cnt].multiplier = 100.0 / (100.0 - (double)z);
        edges[edge_cnt].to = x;
        head_list[y] = edge_cnt++;
        // Since bidirectional, add the reverse
        edges[edge_cnt].to = y;
        edges[edge_cnt].multiplier = 100.0 / (100.0 - (double)z);
        head_list[x] = edge_cnt++;
    }
    int A, B;
    scanf("%d %d", &A, &B);
    double require[MAXN];
    for(int i=1;i<=n;i++) require[i] = INF;
    int processed[MAXN] = {0};
    require[B] = 100.0;
    heap_push(100.0, B);
    while(heap_size >0){
        double current_s;
        int u;
        heap_pop(&current_s, &u);
        if(processed[u]) continue;
        processed[u] = 1;
        for(int e = head_list[u]; e != -1; e = head_list[u]){
            int v = edges[e].to;
            double s_v = require[u] * edges[e].multiplier;
            if(s_v < require[v]){
                require[v] = s_v;
                heap_push(s_v, v);
            }
        }
    }
    printf("%.8lf\n", require[A]);
    return 0;
}