#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a, b;
    int Ti, ti;
} Edge;

typedef struct {
    int a, b;
    int is_boy;
} E;

int parent[10005];
int ranku[10005];

int find_set(int x){
    if(parent[x] != x){
        parent[x] = find_set(parent[x]);
    }
    return parent[x];
}

int cmp(const void *a, const void *b){
    E *ea = (E*)a;
    E *eb = (E*)b;
    if(ea->is_boy != eb->is_boy){
        return eb->is_boy - ea->is_boy;
    }
    return 0;
}

int check(int C, Edge *edges, int m, int n, int k){
    E selected[20000];
    int cnt = 0;
    for(int i=0;i<m;i++){
        if(edges[i].Ti <= C){
            selected[cnt].a = edges[i].a;
            selected[cnt].b = edges[i].b;
            selected[cnt].is_boy = 1;
            cnt++;
        }
        if(edges[i].ti <= C){
            selected[cnt].a = edges[i].a;
            selected[cnt].b = edges[i].b;
            selected[cnt].is_boy = 0;
            cnt++;
        }
    }
    qsort(selected, cnt, sizeof(E), cmp);
    for(int i=1;i<=n;i++) { parent[i] = i; ranku[i] = 0;}
    int total = 0, boy = 0;
    for(int i=0;i<cnt;i++){
        int fa = find_set(selected[i].a);
        int fb = find_set(selected[i].b);
        if(fa != fb){
            parent[fa] = fb;
            total++;
            if(selected[i].is_boy) boy++;
            if(total == n-1) break;
        }
    }
    if(total == n-1 && boy >=k) return 1;
    return 0;
}

int main(){
    int n, k, m;
    scanf("%d %d %d", &n, &k, &m);
    Edge edges[20000];
    int maxC = 0;
    for(int i=0;i<m;i++){
        scanf("%d %d %d %d", &edges[i].a, &edges[i].b, &edges[i].Ti, &edges[i].ti);
        if(edges[i].Ti > maxC) maxC = edges[i].Ti;
        if(edges[i].ti > maxC) maxC = edges[i].ti;
    }
    int left = 1, right = maxC, ans = maxC;
    while(left <= right){
        int mid = left + (right - left)/2;
        if(check(mid, edges, m, n, k)){
            ans = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    printf("%d\n", ans);
    return 0;
}