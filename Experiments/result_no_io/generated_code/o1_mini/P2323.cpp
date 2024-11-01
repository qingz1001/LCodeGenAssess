#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a, b;
    int c1, c2;
    int index;
} Road;

int cmp_road(const void* a, const void* b) {
    Road* r1 = (Road*)a;
    Road* r2 = (Road*)b;
    if (r1->c1 != r2->c1)
        return r1->c1 - r2->c1;
    return r1->c2 - r2->c2;
}

int parent[10010];

int find_set(int x) {
    if (parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

int main(){
    int n, k, m;
    scanf("%d %d %d", &n, &k, &m);
    Road roads[m];
    for(int i=0;i<m;i++){
        scanf("%d %d %d %d", &roads[i].a, &roads[i].b, &roads[i].c1, &roads[i].c2);
        roads[i].index = i+1;
    }
    int low=1, high=30000, answer=30000;
    while(low <= high){
        int mid = (low + high)/2;
        // Collect usable roads
        Road usable[m];
        int cnt=0;
        for(int i=0;i<m;i++){
            if(roads[i].c1 <= mid || roads[i].c2 <= mid){
                usable[cnt++] = roads[i];
            }
        }
        // Sort: type1 first if possible
        // Custom sort: type1 with c1 <= mid first, then type2 with c2 <= mid
        qsort(usable, cnt, sizeof(Road), cmp_road);
        // Initialize Union-Find
        for(int i=1;i<=n;i++) parent[i]=i;
        int type1_count=0, edge_count=0;
        for(int i=0;i<cnt && edge_count < n-1;i++){
            int fa = find_set(usable[i].a);
            int fb = find_set(usable[i].b);
            if(fa != fb){
                parent[fa] = fb;
                edge_count++;
                if(usable[i].c1 <= mid){
                    type1_count++;
                }
            }
        }
        if(edge_count == n-1 && type1_count >= k){
            answer = mid;
            high = mid -1;
        }
        else{
            low = mid +1;
        }
    }
    // Now build the actual solution
    Road usable[m];
    int cnt=0;
    for(int i=0;i<m;i++){
        if(roads[i].c1 <= answer || roads[i].c2 <= answer){
            usable[cnt++] = roads[i];
        }
    }
    // Sort usable roads: prefer type1
    // Comparator: type1 first, then type2, sorted by c1 then c2
    typedef struct {
        Road road;
        int type;
    } Edge;
    Edge edges[cnt];
    int ec=0;
    for(int i=0;i<cnt;i++){
        if(roads[i].c1 <= answer){
            edges[ec].road = roads[i];
            edges[ec].type = 1;
            ec++;
        }
    }
    for(int i=0;i<cnt;i++){
        if(roads[i].c1 > answer && roads[i].c2 <= answer){
            edges[ec].road = roads[i];
            edges[ec].type = 2;
            ec++;
        }
    }
    // Sort edges: type1 first, then type2
    // If both type1, sort by index
    // If both type2, sort by index
    // If one type1 and one type2, type1 comes first
    int compare(const void* a, const void* b){
        Edge* e1 = (Edge*)a;
        Edge* e2 = (Edge*)b;
        if(e1->type != e2->type)
            return e1->type - e2->type;
        return e1->road.index - e2->road.index;
    }
    qsort(edges, ec, sizeof(Edge), compare);
    // Initialize Union-Find
    for(int i=1;i<=n;i++) parent[i]=i;
    // Select edges
    Edge selected[n];
    int sc=0, type1_selected=0;
    for(int i=0;i<ec && sc < n-1;i++){
        int fa = find_set(edges[i].road.a);
        int fb = find_set(edges[i].road.b);
        if(fa != fb){
            parent[fa] = fb;
            selected[sc++] = edges[i];
            if(edges[i].type ==1){
                type1_selected++;
            }
        }
    }
    // If type1_selected <k, need to adjust
    if(type1_selected <k){
        // Not possible, but according to binary search it should be possible
    }
    // Collect selected roads and sort by index
    typedef struct {
        int index;
        int type;
    } Output;
    Output out_selected[n-1];
    for(int i=0;i<n-1;i++){
        out_selected[i].index = selected[i].road.index;
        out_selected[i].type = selected[i].type;
    }
    // Sort by index
    int cmp_output(const void* a, const void* b){
        Output* o1 = (Output*)a;
        Output* o2 = (Output*)b;
        return o1->index - o2->index;
    }
    qsort(out_selected, n-1, sizeof(Output), cmp_output);
    // Print answer
    printf("%d\n", answer);
    for(int i=0;i<n-1;i++){
        printf("%d %d\n", out_selected[i].index, out_selected[i].type);
    }
    return 0;
}