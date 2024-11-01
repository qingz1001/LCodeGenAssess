#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int r, c, h, id;
} Cell;

typedef struct {
    int from;
    int to;
} Edge;

int compare_cells(const void *a, const void *b){
    Cell *ca = (Cell*)a;
    Cell *cb = (Cell*)b;
    if(cb->h != ca->h)
        return cb->h - ca->h;
    return 0;
}

int compare_edges(const void *a, const void *b){
    Edge *ea = (Edge*)a;
    Edge *eb = (Edge*)b;
    if(ea->from != eb->from)
        return ea->from - eb->from;
    return ea->to - eb->to;
}

int main(){
    int W, L;
    scanf("%d %d", &W, &L);
    int N = W * L;
    int *H = (int*)malloc(N * sizeof(int));
    for(int i=0;i<N;i++) scanf("%d", &H[i]);
    
    Cell *cells = (Cell*)malloc(N * sizeof(Cell));
    for(int i=0;i<L;i++) {
        for(int j=0;j<W;j++) {
            int idx = i * W + j;
            cells[idx].r = i;
            cells[idx].c = j;
            cells[idx].h = H[idx];
            cells[idx].id = idx;
        }
    }
    
    qsort(cells, N, sizeof(Cell), compare_cells);
    
    int *parent = (int*)malloc(N * sizeof(int));
    for(int i=0;i<N;i++) parent[i] = i;
    
    // Directions: up, down, left, right
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    
    for(int i=0; i<N; ){
        int current_h = cells[i].h;
        int j = i;
        while(j < N && cells[j].h == current_h) j++;
        // Union same height
        for(int k=i; k<j; k++){
            int idx = cells[k].id;
            int r = cells[k].r;
            int c = cells[k].c;
            for(int d=0; d<4; d++){
                int nr = r + dr[d];
                int nc = c + dc[d];
                if(nr >=0 && nr < L && nc >=0 && nc < W){
                    int nidx = nr * W + nc;
                    if(H[nidx] == current_h){
                        // Find position in sorted cells
                        // Cells are sorted by height descending, but within same height order is arbitrary
                        // So we need to find the position of nidx in i to j-1
                        // To optimize, we can assume all same height are together
                        // and since sorted, nidx must be between i and j-1
                        // So iterate through i to j-1 to find nidx
                        // To speed up, we can skip this step and just union
                        // since H[nidx] == current_h
                        // and all same height are being processed
                        // Thus, we can union directly
                        // without checking if nidx is already processed
                        // which they are in this loop
                        // But to ensure that nidx is within current group
                        // we skip if nidx is not in i to j-1
                        // To implement efficiently, assume all H[nidx] == current_h are contiguous
                        // So we can proceed to union
                        // To prevent excessive searching, use a reverse index
                        // But for simplicity, perform a linear search
                        // This is acceptable since each cell has up to 4 neighbors
                        // and k runs from i to j-1
                        // So total operations are manageable
                        // Find the index of nidx
                        // Binary search could be used, but linear is fine here
                        int m;
                        for(m=i; m<j; m++) if(cells[m].id == nidx) break;
                        if(m < j){
                            // Union idx and nidx
                            // Find roots
                            int a = idx;
                            while(a != parent[a]) a = parent[a];
                            int b_idx = nidx;
                            while(b_idx != parent[b_idx]) b_idx = parent[b_idx];
                            if(a != b_idx){
                                parent[b_idx] = a;
                            }
                        }
                    }
                }
            }
        }
        i = j;
    }
    
    // Assign component IDs
    int *root_to_cid = (int*)malloc(N * sizeof(int));
    for(int i=0;i<N;i++) root_to_cid[i] = -1;
    int cid = 0;
    int *cid_map = (int*)malloc(N * sizeof(int));
    for(int i=0;i<N;i++){
        int root = cells[i].id;
        while(root != parent[root]) root = parent[root];
        if(root_to_cid[root] == -1){
            root_to_cid[root] = cid;
            cid_map[i] = cid;
            cid++;
        }
        else{
            cid_map[i] = root_to_cid[root];
        }
    }
    int total_cid = cid;
    
    // Build edge list
    Edge *edges = (Edge*)malloc(4 * N * sizeof(Edge));
    int edge_count = 0;
    for(int i=0;i<N;i++){
        int r = cells[i].r;
        int c = cells[i].c;
        int from = cid_map[i];
        for(int d=0; d<4; d++){
            int nr = r + dr[d];
            int nc = c + dc[d];
            if(nr >=0 && nr < L && nc >=0 && nc < W){
                int nidx = nr * W + nc;
                if(H[nidx] < H[cells[i].id]){
                    int to = -1;
                    // Find component ID of nidx
                    int root = nidx;
                    while(root != parent[root]) root = parent[root];
                    if(root_to_cid[root] == -1){
                        root_to_cid[root] = cid;
                        cid_map[nidx] = cid;
                        cid++;
                        total_cid++;
                    }
                    to = root_to_cid[root];
                    if(from != to){
                        edges[edge_count].from = from;
                        edges[edge_count].to = to;
                        edge_count++;
                    }
                }
            }
        }
    }
    
    // Sort edges and remove duplicates
    qsort(edges, edge_count, sizeof(Edge), compare_edges);
    int unique_edges = 0;
    int *in_degree = (int*)calloc(total_cid, sizeof(int));
    int *out_degree = (int*)calloc(total_cid, sizeof(int));
    for(int i=0;i<edge_count;i++){
        if(i == 0 || edges[i].from != edges[i-1].from || edges[i].to != edges[i-1].to){
            out_degree[edges[i].from]++;
            in_degree[edges[i].to]++;
        }
    }
    
    // Count sources and sinks
    int sources = 0, sinks = 0;
    for(int i=0;i<total_cid;i++){
        if(in_degree[i] == 0) sources++;
        if(out_degree[i] == 0) sinks++;
    }
    
    if(total_cid == 1){
        printf("0\n");
    }
    else{
        printf("%d\n", sources > sinks ? sources : sinks);
    }
    
    free(H);
    free(cells);
    free(parent);
    free(root_to_cid);
    free(cid_map);
    free(edges);
    free(in_degree);
    free(out_degree);
    return 0;
}