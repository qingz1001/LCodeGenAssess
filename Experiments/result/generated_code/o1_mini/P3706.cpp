#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 90000
#define MAXM 300
#define MAXPAT 300
#define MAXLEN 300
#define MAXCHILD 2
#define INF 1e-12

typedef struct Node {
    int children[2];
    int fail;
    int output; // -1 if not terminal, else pattern index
} Node;

Node trie[MAXN];
int size = 1; // root is 0
int n, m;
char patterns[MAXPAT][MAXLEN +1];
int queue[MAXN];
int front, rear;

// Function to convert character to index
int charToIndex(char c){
    if(c == 'H') return 0;
    else return 1;
}

int main(){
    // Read n and m
    scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++) {
        scanf("%s", patterns[i]);
    }
    // Initialize trie
    for(int i=0;i<size;i++){
        trie[i].children[0] = trie[i].children[1] = -1;
        trie[i].fail = 0;
        trie[i].output = -1;
    }
    // Insert patterns
    for(int i=0;i<n;i++){
        int current = 0;
        for(int j=0;j<m;j++){
            int c = charToIndex(patterns[i][j]);
            if(trie[current].children[c]==-1){
                trie[current].children[c] = size;
                trie[size].children[0] = trie[size].children[1] = -1;
                trie[size].fail = 0;
                trie[size].output = -1;
                size++;
            }
            current = trie[current].children[c];
        }
        trie[current].output = i;
    }
    // Build fail links
    front = rear =0;
    queue[rear++] = 0;
    while(front < rear){
        int current = queue[front++];
        for(int c=0;c<2;c++){
            if(trie[current].children[c]!=-1){
                int child = trie[current].children[c];
                if(current !=0){
                    int f = trie[current].fail;
                    while(f !=0 && trie[f].children[c]==-1){
                        f = trie[f].fail;
                    }
                    if(trie[f].children[c]!=-1){
                        trie[child].fail = trie[f].children[c];
                    }
                    else{
                        trie[child].fail =0;
                    }
                }
                // If fail state has output, propagate
                if(trie[trie[child].fail].output != -1){
                    trie[child].output = trie[trie[child].fail].output;
                }
                queue[rear++] = child;
            }
            else{
                if(current ==0){
                    trie[current].children[c] =0;
                }
                else{
                    trie[current].children[c] = trie[trie[current].fail].children[c];
                }
            }
        }
    }
    // Assign state indices and mark terminal
    int *is_term = (int*)calloc(size, sizeof(int));
    int *pattern_of = (int*)calloc(size, sizeof(int));
    for(int i=0;i<size;i++) {
        if(trie[i].output != -1){
            is_term[i] =1;
            pattern_of[i] = trie[i].output;
        }
    }
    // Assign transient and absorbing indices
    int K=0, Rn=0;
    int *transient = (int*)malloc(size * sizeof(int));
    int *absorbing = (int*)malloc(size * sizeof(int));
    for(int i=0;i<size;i++) {
        if(!is_term[i]){
            transient[i] = K++;
        }
        else{
            absorbing[i] = Rn++;
        }
    }
    // If Rn !=n, map absorbing states to patterns
    // Assuming each terminal state corresponds to exactly one pattern
    // Build (I - Q) and R matrices
    // (I - Q) will be K x K, R will be K x n
    // To perform Gaussian elimination, augment (I - Q | R)
    // So total columns = K + n
    int total_cols = K + n;
    double **aug = (double**)malloc(K * sizeof(double*));
    for(int i=0;i<K;i++) {
        aug[i] = (double*)calloc(total_cols, sizeof(double));
    }
    // Fill augmented matrix
    for(int i=0;i<size;i++) {
        if(!is_term[i]){
            int row = transient[i];
            // Set I - Q
            aug[row][row] =1.0;
            for(int c=0;c<2;c++){
                int next = trie[i].children[c];
                if(!is_term[next]){
                    int col = transient[next];
                    aug[row][col] -=0.5;
                }
                else{
                    int pat = pattern_of[next];
                    aug[row][K + pat] +=0.5;
                }
            }
        }
    }
    // Initialize R matrix
    for(int i=0;i<K;i++) {
        for(int j=0;j<n;j++) {
            // Already filled in the augmented matrix
        }
    }
    // Gaussian Elimination
    for(int col=0; col < K + n; col++){
        // Find pivot
        int sel = -1;
        for(int row=0; row<K; row++){
            if(fabs(aug[row][col]) > INF){
                sel = row;
                break;
            }
        }
        if(sel == -1){
            continue;
        }
        // Swap rows
        if(sel != col){
            double *temp = aug[sel];
            aug[sel] = aug[col];
            aug[col] = temp;
        }
        // Normalize pivot row
        double factor = aug[col][col];
        for(int j=col; j < K + n; j++) {
            aug[col][j] /= factor;
        }
        // Eliminate other rows
        for(int row=0; row<K; row++){
            if(row != col && fabs(aug[row][col]) > INF){
                double f = aug[row][col];
                for(int j=col; j < K + n; j++) {
                    aug[row][j] -= f * aug[col][j];
                }
            }
        }
    }
    // Extract N*R which is the last n columns
    double *result = (double*)calloc(n, sizeof(double));
    // Initial state is root=0
    if(!is_term[0]){
        int row = transient[0];
        for(int j=0; j<n; j++) {
            result[j] = aug[row][K + j];
        }
    }
    // Print results
    for(int i=0;i<n;i++) {
        printf("%.10lf\n", result[i]);
    }
    // Free memory
    for(int i=0;i<K;i++) {
        free(aug[i]);
    }
    free(aug);
    free(transient);
    free(absorbing);
    free(is_term);
    free(pattern_of);
    free(result);
    return 0;
}