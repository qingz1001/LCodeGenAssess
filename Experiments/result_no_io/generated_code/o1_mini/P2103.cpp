#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 500
#define INF 100000000000000LL

typedef long long ll;

ll distance_matrix[MAX_N][MAX_N];
int C_count_size;
int *C;
int offset_array[MAX_N];
int N, M;

// Function to compute the index in C for pair (i, j) where i < j
int get_index(int i, int j) {
    return offset_array[i] + (j - i - 1);
}

int main(){
    int i, j, k;
    scanf("%d %d", &N, &M);
    
    // Initialize distance matrix
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(i == j){
                distance_matrix[i][j] = 0;
            }
            else{
                distance_matrix[i][j] = INF;
            }
        }
    }
    
    // Read edges
    int u, v;
    ll w;
    for(k=0; k<M; k++){
        scanf("%d %d %lld", &u, &v, &w);
        u--; v--; // 0-based indexing
        if(w < distance_matrix[u][v]){
            distance_matrix[u][v] = w;
            distance_matrix[v][u] = w;
        }
    }
    
    // Floyd-Warshall
    for(k=0; k<N; k++){
        for(i=0; i<N; i++){
            if(distance_matrix[i][k] == INF) continue;
            for(j=0; j<N; j++){
                if(distance_matrix[k][j] == INF) continue;
                if(distance_matrix[i][k] + distance_matrix[k][j] < distance_matrix[i][j]){
                    distance_matrix[i][j] = distance_matrix[i][k] + distance_matrix[k][j];
                }
            }
        }
    }
    
    // Precompute offset_array for indexing
    // offset_array[i] = i*N - i*(i+1)/2
    for(i=0;i<N;i++){
        offset_array[i] = i*N - (i*(i+1))/2;
    }
    
    // Initialize C
    C_count_size = (N*(N-1))/2;
    C = (int*)calloc(C_count_size, sizeof(int));
    if(!C){
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Iterate over each edge
    for(k=0; k<M; k++){
        // Reset variables for each edge
        // However, since edges are not stored, iterate again
        // To avoid storing edges, iterate the input again is not feasible
        // So, instead, store edges initially
        // Modify the initial edge reading to store edges
    }
    
    // To store edges, read again since we need to iterate over edges
    // Instead, store edges during the first read
    // Modify the above code to store edges
    // Reinitialize and read again with storing edges
    // Restart
    // Reset distance_matrix
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(i == j){
                distance_matrix[i][j] = 0;
            }
            else{
                distance_matrix[i][j] = INF;
            }
        }
    }
    
    // Store edges in arrays
    int *edges_u = (int*)malloc(M * sizeof(int));
    int *edges_v = (int*)malloc(M * sizeof(int));
    ll *edges_w = (ll*)malloc(M * sizeof(ll));
    if(!edges_u || !edges_v || !edges_w){
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Read edges again
    // Reset reading
    rewind(stdin);
    // Read N and M again
    scanf("%d %d", &N, &M);
    for(k=0; k<M; k++){
        scanf("%d %d %lld", &u, &v, &w);
        u--; v--; // 0-based indexing
        edges_u[k] = u;
        edges_v[k] = v;
        edges_w[k] = w;
        if(w < distance_matrix[u][v]){
            distance_matrix[u][v] = w;
            distance_matrix[v][u] = w;
        }
    }
    
    // Floyd-Warshall again
    for(k=0; k<N; k++){
        for(i=0; i<N; i++){
            if(distance_matrix[i][k] == INF) continue;
            for(j=0; j<N; j++){
                if(distance_matrix[k][j] == INF) continue;
                if(distance_matrix[i][k] + distance_matrix[k][j] < distance_matrix[i][j]){
                    distance_matrix[i][j] = distance_matrix[i][k] + distance_matrix[k][j];
                }
            }
        }
    }
    
    // Process each edge
    for(k=0; k<M; k++){
        int u_edge = edges_u[k];
        int v_edge = edges_v[k];
        ll w_edge = edges_w[k];
        
        // Direction u -> v
        for(i=0; i<N; i++){
            if(distance_matrix[i][u_edge] + w_edge == distance_matrix[i][v_edge]){
                for(j=0; j<N; j++){
                    if(distance_matrix[i][j] == distance_matrix[i][v_edge] + distance_matrix[v_edge][j]){
                        if(i < j){
                            int index = get_index(i, j);
                            C[index]++;
                        }
                        else if(j < i){
                            int index = get_index(j, i);
                            C[index]++;
                        }
                    }
                }
            }
        }
        
        // Direction v -> u
        for(i=0; i<N; i++){
            if(distance_matrix[i][v_edge] + w_edge == distance_matrix[i][u_edge]){
                for(j=0; j<N; j++){
                    if(distance_matrix[i][j] == distance_matrix[i][u_edge] + distance_matrix[u_edge][j]){
                        if(i < j){
                            int index = get_index(i, j);
                            C[index]++;
                        }
                        else if(j < i){
                            int index = get_index(j, i);
                            C[index]++;
                        }
                    }
                }
            }
        }
    }
    
    // Output the results
    int first = 1;
    for(i=0; i<N; i++){
        for(j=i+1; j<N; j++){
            if(!first){
                printf(" ");
            }
            else{
                first = 0;
            }
            printf("%d", C[get_index(i, j)]);
        }
    }
    printf("\n");
    
    // Free allocated memory
    free(C);
    free(edges_u);
    free(edges_v);
    free(edges_w);
    
    return 0;
}