#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1001

typedef struct Node {
    int neighbors[MAXN];
    int degree;
} Node;

Node tree[MAXN];
int N;

// Comparison function for descending order
int cmp_desc(const void* a, const void* b){
    int ia = *(int*)a;
    int ib = *(int*)b;
    return ib - ia;
}

// Recursive function to compute broadcast time
int compute_time(int current, int parent){
    int children[MAXN];
    int cnt = 0;
    for(int i=0;i<tree[current].degree;i++){
        int neighbor = tree[current].neighbors[i];
        if(neighbor != parent){
            children[cnt++] = compute_time(neighbor, current);
        }
    }
    if(cnt == 0) return 0;
    qsort(children, cnt, sizeof(int), cmp_desc);
    int max_time = 0;
    for(int i=0;i<cnt;i++){
        int temp = children[i] + i +1;
        if(temp > max_time) max_time = temp;
    }
    return max_time;
}

int main(){
    scanf("%d", &N);
    for(int i=2;i<=N;i++){
        int parent;
        scanf("%d", &parent);
        tree[i].neighbors[tree[i].degree++] = parent;
        tree[parent].neighbors[tree[parent].degree++] = i;
    }
    int min_time = -1;
    int candidates[MAXN];
    int cnt_cand =0;
    for(int i=1;i<=N;i++){
        int t = compute_time(i, -1);
        if(min_time == -1 || t < min_time){
            min_time = t;
            cnt_cand =0;
            candidates[cnt_cand++] = i;
        }
        else if(t == min_time){
            candidates[cnt_cand++] = i;
        }
    }
    printf("%d\n", min_time);
    for(int i=0;i<cnt_cand;i++){
        if(i>0) printf(" ");
        printf("%d", candidates[i]);
    }
    printf("\n");
    return 0;
}