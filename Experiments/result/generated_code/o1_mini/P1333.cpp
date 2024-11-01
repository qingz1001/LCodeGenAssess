#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EDGES 250000
#define MAX_COLORS 500000
#define MAX_STRING_LENGTH 11

typedef struct {
    char a[MAX_STRING_LENGTH];
    char b[MAX_STRING_LENGTH];
} Edge;

Edge edges[MAX_EDGES];
char colors_list[MAX_COLORS][MAX_STRING_LENGTH];
int edge_count = 0;
int color_count = 0;

// Comparator for qsort
int cmp_strs(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

// Union-Find structures
int parent_ids[MAX_COLORS];
int degree[MAX_COLORS];

int find_set(int x) {
    if (parent_ids[x] != x)
        parent_ids[x] = find_set(parent_ids[x]);
    return parent_ids[x];
}

void union_set(int x, int y) {
    int fx = find_set(x);
    int fy = find_set(y);
    if (fx != fy)
        parent_ids[fx] = fy;
}

// Function to get unique ID using binary search
int get_id(char *s, char unique_colors[][MAX_STRING_LENGTH], int unique_count) {
    int left = 0, right = unique_count - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(s, unique_colors[mid]);
        if (cmp == 0)
            return mid;
        if (cmp < 0)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1; // Should not happen
}

int main(){
    char line[32];
    char temp1[MAX_STRING_LENGTH];
    char temp2[MAX_STRING_LENGTH];
    
    // Read all edges and collect color strings
    while (fgets(line, sizeof(line), stdin)) {
        if (sscanf(line, "%s %s", temp1, temp2) != 2)
            break;
        strcpy(edges[edge_count].a, temp1);
        strcpy(edges[edge_count].b, temp2);
        strcpy(colors_list[color_count++], temp1);
        strcpy(colors_list[color_count++], temp2);
        edge_count++;
        if(edge_count >= MAX_EDGES || color_count >= MAX_COLORS){
            break;
        }
    }
    
    // Sort the colors_list
    qsort(colors_list, color_count, MAX_STRING_LENGTH, cmp_strs);
    
    // Remove duplicates to get unique_colors_list
    char unique_colors_list[MAX_COLORS][MAX_STRING_LENGTH];
    int unique_count = 0;
    if (color_count > 0) {
        strcpy(unique_colors_list[unique_count++], colors_list[0]);
        for(int i =1; i < color_count; i++) {
            if(strcmp(colors_list[i], unique_colors_list[unique_count-1]) !=0 ){
                strcpy(unique_colors_list[unique_count++], colors_list[i]);
                if(unique_count >= MAX_COLORS){
                    break;
                }
            }
        }
    }
    
    // Initialize Union-Find and degrees
    for(int i =0; i < unique_count; i++) {
        parent_ids[i] = i;
        degree[i] = 0;
    }
    
    // Map edges to IDs, build degrees and union sets
    for(int i =0; i < edge_count; i++) {
        int id1 = get_id(edges[i].a, unique_colors_list, unique_count);
        int id2 = get_id(edges[i].b, unique_colors_list, unique_count);
        if(id1 == -1 || id2 == -1){
            // Invalid color, should not happen
            printf("Impossible\n");
            return 0;
        }
        degree[id1]++;
        degree[id2]++;
        union_set(id1, id2);
    }
    
    // Find the root of the first vertex with degree >0
    int first_root = -1;
    for(int i =0; i < unique_count; i++) {
        if(degree[i] > 0){
            first_root = find_set(i);
            break;
        }
    }
    
    if(first_root == -1){
        // No edges, possible
        printf("Possible\n");
        return 0;
    }
    
    // Check all vertices with degree >0 are connected
    int connected = 1;
    for(int i =0; i < unique_count; i++) {
        if(degree[i] > 0 && find_set(i) != first_root){
            connected = 0;
            break;
        }
    }
    
    if(!connected){
        printf("Impossible\n");
        return 0;
    }
    
    // Count the number of vertices with odd degree
    int odd = 0;
    for(int i =0; i < unique_count; i++) {
        if(degree[i] % 2 != 0){
            odd++;
            if(odd > 2){
                break;
            }
        }
    }
    
    if(odd == 0 || odd == 2){
        printf("Possible\n");
    }
    else{
        printf("Impossible\n");
    }
    
    return 0;
}