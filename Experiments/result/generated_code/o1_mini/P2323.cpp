#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a, b;
    int c1, c2;
    int t;
} Road;

typedef struct {
    Road **roads;
    int size;
} RoadList;

int parent[10005];

int find_set(int x){
    if(parent[x] != x){
        parent[x] = find_set(parent[x]);
    }
    return parent[x];
}

int cmp(const void *a, const void *b, void *arg){
    int c = *(int*)arg;
    Road *ra = *(Road**)a;
    Road *rb = *(Road**)b;
    int type_a = (ra->c1 <= c) ? 1 : ((ra->c2 <= c) ? 0 : -1);
    int type_b = (rb->c1 <= c) ? 1 : ((rb->c2 <= c) ? 0 : -1);
    if(type_a != type_b){
        return type_b - type_a; // type1 first, then type2
    }
    return 0;
}

int can_build(Road **roads_sorted, int m_minus1, int c, int n, int k){
    // Initialize Union-Find
    for(int i=1;i<=n;i++) parent[i] = i;
    int count =0;
    int level1 =0;
    for(int i=0;i<m_minus1;i++){
        Road *r = roads_sorted[i];
        if(r->c1 > c && r->c2 > c) continue;
        int fa = find_set(r->a);
        int fb = find_set(r->b);
        if(fa != fb){
            parent[fa] = fb;
            count++;
            if(r->c1 <= c){
                level1++;
            }
            if(count == n-1){
                break;
            }
        }
    }
    if(count == n-1 && level1 >= k){
        return 1;
    }
    return 0;
}

int main(){
    int n, k, m;
    scanf("%d %d %d", &n, &k, &m);
    int m_minus1 = m-1;
    Road roads_all[20000];
    for(int i=0;i<m_minus1;i++){
        scanf("%d %d %d %d", &roads_all[i].a, &roads_all[i].b, &roads_all[i].c1, &roads_all[i].c2);
        roads_all[i].t = i+1;
    }
    // Binary search for minimal c
    int l=1, r=30000, ans=30000;
    while(l <= r){
        int mid = l + (r - l)/2;
        // Create an array of pointers
        Road *roads_ptr[m_minus1];
        for(int i=0;i<m_minus1;i++) roads_ptr[i] = &roads_all[i];
        // Sort roads_ptr based on mid
        qsort_r(roads_ptr, m_minus1, sizeof(Road*), cmp, &mid);
        // Check if possible
        // Initialize Union-Find
        for(int i=1;i<=n;i++) parent[i] = i;
        int count =0;
        int level1 =0;
        for(int i=0;i<m_minus1;i++){
            Road *r = roads_ptr[i];
            if(r->c1 > mid && r->c2 > mid) continue;
            int fa = find_set(r->a);
            int fb = find_set(r->b);
            if(fa != fb){
                parent[fa] = fb;
                count++;
                if(r->c1 <= mid){
                    level1++;
                }
                if(count == n-1){
                    break;
                }
            }
        }
        if(count == n-1 && level1 >=k){
            ans = mid;
            r = mid -1;
        }
        else{
            l = mid +1;
        }
    }
    // Now build the spanning tree with ans
    // Create an array of pointers
    Road *roads_ptr_final[m_minus1];
    for(int i=0;i<m_minus1;i++) roads_ptr_final[i] = &roads_all[i];
    // Sort roads_ptr_final based on ans
    qsort_r(roads_ptr_final, m_minus1, sizeof(Road*), cmp, &ans);
    // Initialize Union-Find
    for(int i=1;i<=n;i++) parent[i] = i;
    // To store selected roads
    typedef struct {
        int t;
        int p;
    } Selected;
    Selected selected[m_minus1];
    int sel_count =0;
    int level1_count =0;
    for(int i=0;i<m_minus1;i++){
        Road *r = roads_ptr_final[i];
        if(r->c1 > ans && r->c2 > ans) continue;
        int fa = find_set(r->a);
        int fb = find_set(r->b);
        if(fa != fb){
            parent[fa] = fb;
            selected[sel_count].t = r->t;
            if(r->c1 <= ans){
                selected[sel_count].p = 1;
                level1_count++;
            }
            else{
                selected[sel_count].p = 2;
            }
            sel_count++;
            if(sel_count == n-1){
                break;
            }
        }
    }
    // Now, sort selected roads by t
    for(int i=0;i<sel_count-1;i++){
        for(int j=i+1;j<sel_count;j++){
            if(selected[i].t > selected[j].t){
                Selected temp = selected[i];
                selected[i] = selected[j];
                selected[j] = temp;
            }
        }
    }
    // Output
    printf("%d\n", ans);
    for(int i=0;i<sel_count;i++){
        printf("%d %d\n", selected[i].t, selected[i].p);
    }
    return 0;
}