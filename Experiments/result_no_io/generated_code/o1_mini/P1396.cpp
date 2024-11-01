#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10005
#define MAXM 20005
#define INF 1000000000

typedef struct {
    int to;
    int w;
    int next;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN];
int edge_cnt = 0;

typedef struct {
    int node;
    int max_w;
} Element;

typedef struct {
    Element heap[MAXM];
    int size;
} PriorityQueue;

void initQueue(PriorityQueue *pq) {
    pq->size = 0;
}

void swap(Element *a, Element *b) {
    Element temp = *a;
    *a = *b;
    *b = temp;
}

void push(PriorityQueue *pq, Element e) {
    int i = pq->size++;
    pq->heap[i] = e;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (pq->heap[parent].max_w <= pq->heap[i].max_w)
            break;
        swap(&pq->heap[parent], &pq->heap[i]);
        i = parent;
    }
}

Element pop(PriorityQueue *pq) {
    Element top = pq->heap[0];
    pq->heap[0] = pq->heap[--pq->size];
    int i = 0;
    while (1) {
        int left = 2 * i + 1, right = 2 * i + 2, smallest = i;
        if (left < pq->size && pq->heap[left].max_w < pq->heap[smallest].max_w)
            smallest = left;
        if (right < pq->size && pq->heap[right].max_w < pq->heap[smallest].max_w)
            smallest = right;
        if (smallest == i)
            break;
        swap(&pq->heap[i], &pq->heap[smallest]);
        i = smallest;
    }
    return top;
}

int main(){
    int n, m, s, t;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    memset(head, -1, sizeof(head));
    for(int i=0;i<m;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[edge_cnt].to = v;
        edges[edge_cnt].w = w;
        edges[edge_cnt].next = head[u];
        head[u] = edge_cnt++;
        
        edges[edge_cnt].to = u;
        edges[edge_cnt].w = w;
        edges[edge_cnt].next = head[v];
        head[v] = edge_cnt++;
    }
    int min_max_w[MAXN];
    for(int i=1;i<=n;i++) min_max_w[i] = INF;
    min_max_w[s] = 0;
    PriorityQueue pq;
    initQueue(&pq);
    Element start;
    start.node = s;
    start.max_w = 0;
    push(&pq, start);
    while(pq.size){
        Element current = pop(&pq);
        if(current.node == t){
            printf("%d\n", current.max_w);
            return 0;
        }
        if(current.max_w > min_max_w[current.node]) continue;
        for(int e = head[current.node]; e != -1; e = edges[e].next){
            int neighbor = edges[e].to;
            int new_max = current.max_w > edges[e].w ? current.max_w : edges[e].w;
            if(new_max < min_max_w[neighbor]){
                min_max_w[neighbor] = new_max;
                Element next;
                next.node = neighbor;
                next.max_w = new_max;
                push(&pq, next);
            }
        }
    }
    return 0;
}