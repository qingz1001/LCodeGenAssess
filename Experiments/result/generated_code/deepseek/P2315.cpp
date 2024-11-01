#include <stdio.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    int n;
    fscanf(input, "%d", &n);
    
    int total_triangles = 0;
    
    for (int i = 0; i < n; i++) {
        int m;
        fscanf(input, "%d", &m);
        
        int count = 0;
        for (int j = 0; j < m; j++) {
            int x;
            fscanf(input, "%d", &x);
            if (x == 1) {
                count++;
            }
        }
        
        // Each row of 1s can form triangles with the previous rows
        total_triangles += count * (count - 1) / 2;
    }
    
    fprintf(output, "%d\n", total_triangles);
    
    fclose(input);
    fclose(output);
    
    return 0;
}