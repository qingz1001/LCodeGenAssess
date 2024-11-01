#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 1000

int N, M;
int a[MAX_N];
int b[MAX_M];
int w[MAX_N][MAX_M];
int result[MAX_N];

void greedy_solution() {
    for (int i = 0; i < N; i++) {
        int max_power = -1;
        int best_drawer = 0;
        
        for (int j = 0; j < M; j++) {
            if (b[j] >= a[i] && w[i][j] > max_power) {
                max_power = w[i][j];
                best_drawer = j + 1;
            }
        }
        
        if (best_drawer > 0) {
            result[i] = best_drawer;
            b[best_drawer - 1] -= a[i];
        } else {
            result[i] = 0;
        }
    }
}

int main() {
    char input_filename[20];
    char output_filename[20];
    
    for (int file_num = 1; file_num <= 10; file_num++) {
        sprintf(input_filename, "drawer%d.in", file_num);
        sprintf(output_filename, "drawer%d.out", file_num);
        
        FILE *input_file = fopen(input_filename, "r");
        if (input_file == NULL) {
            printf("Failed to open input file: %s\n", input_filename);
            continue;
        }
        
        fscanf(input_file, "%d %d", &N, &M);
        
        for (int i = 0; i < N; i++) {
            fscanf(input_file, "%d", &a[i]);
        }
        
        for (int j = 0; j < M; j++) {
            fscanf(input_file, "%d", &b[j]);
        }
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                fscanf(input_file, "%d", &w[i][j]);
            }
        }
        
        fclose(input_file);
        
        greedy_solution();
        
        FILE *output_file = fopen(output_filename, "w");
        if (output_file == NULL) {
            printf("Failed to open output file: %s\n", output_filename);
            continue;
        }
        
        for (int i = 0; i < N; i++) {
            fprintf(output_file, "%d\n", result[i]);
        }
        
        fclose(output_file);
        
        printf("Processed file: %s\n", input_filename);
    }
    
    return 0;
}