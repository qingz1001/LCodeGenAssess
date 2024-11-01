#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    int n, m;
    fscanf(input, "%d %d", &n, &m);

    int total_triangles = (n * (n + 1) / 2) * (m * (m + 1) / 2);
    int deleted_edges = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            deleted_edges += (n - i + 1) * (m - j + 1);
        }
    }

    int valid_triangles = total_triangles - deleted_edges;

    fprintf(output, "%d\n", valid_triangles);

    fclose(input);
    fclose(output);

    return 0;
}