#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LETTERS 52
#define MAX_NEIGHBORS 2

int char_to_index(char c) {
    if ('A' <= c && c <= 'Z') return c - 'A';
    return 26 + (c - 'a');
}

char index_to_char(int idx) {
    if (idx < 26) return 'A' + idx;
    return 'a' + (idx - 26);
}

int main(){
    int n;
    scanf("%d", &n);
    int adj[MAX_LETTERS][MAX_NEIGHBORS];
    int deg[MAX_LETTERS];
    memset(deg, 0, sizeof(deg));
    memset(adj, -1, sizeof(adj));
    int letters_present[MAX_LETTERS];
    memset(letters_present, 0, sizeof(letters_present));
    for(int i=0;i<n;i++){
        char a, b;
        scanf(" %c %c", &a, &b);
        int ia = char_to_index(a);
        int ib = char_to_index(b);
        letters_present[ia] = letters_present[ib] = 1;
        adj[ia][deg[ia]++] = ib;
        adj[ib][deg[ib]++] = ia;
    }
    // Collect all letters
    int total =0;
    for(int i=0;i<MAX_LETTERS;i++) if(letters_present[i]) total++;
    if(total != n+1){
        printf("No Solution");
        return 0;
    }
    // Find endpoints
    int endpoints[MAX_LETTERS];
    int ep=0;
    for(int i=0;i<MAX_LETTERS;i++) if(letters_present[i] && deg[i]==1){
        endpoints[ep++] = i;
    }
    if(ep !=2){
        printf("No Solution");
        return 0;
    }
    // Function to traverse
    char path1[MAX_LETTERS+1];
    char path2[MAX_LETTERS+1];
    // First traversal
    int start1 = endpoints[0];
    int current = start1;
    int prev = -1;
    int idx =0;
    path1[idx++] = index_to_char(current);
    while(idx < n+1){
        int next = -1;
        for(int i=0;i<deg[current];i++) {
            if(adj[current][i] != prev){
                next = adj[current][i];
                break;
            }
        }
        if(next == -1){
            break;
        }
        path1[idx++] = index_to_char(next);
        prev = current;
        current = next;
    }
    path1[idx] = '\0';
    // Second traversal
    int start2 = endpoints[1];
    current = start2;
    prev = -1;
    idx =0;
    path2[idx++] = index_to_char(current);
    while(idx < n+1){
        int next = -1;
        for(int i=0;i<deg[current];i++) {
            if(adj[current][i] != prev){
                next = adj[current][i];
                break;
            }
        }
        if(next == -1){
            break;
        }
        path2[idx++] = index_to_char(next);
        prev = current;
        current = next;
    }
    path2[idx] = '\0';
    // Check if both paths are valid
    if(idx != n+1){
        printf("No Solution");
        return 0;
    }
    // Compare lex
    if(strcmp(path1, path2) <0){
        printf("%s", path1);
    }
    else{
        printf("%s", path2);
    }
}