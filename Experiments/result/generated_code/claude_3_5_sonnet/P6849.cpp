#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX_M 1000

int N, M;
int onion[MAX_N];
int drawer[MAX_M];
int power[MAX_N][MAX_M];
int result[MAX_N];

void readInput(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open input file.\n");
        exit(1);
    }

    fscanf(file, "%d %d", &N, &M);
    
    for (int i = 0; i < N; i++) {
        fscanf(file, "%d", &onion[i]);
    }
    
    for (int j = 0; j < M; j++) {
        fscanf(file, "%d", &drawer[j]);
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fscanf(file, "%d", &power[i][j]);
        }
    }

    fclose(file);
}

void writeOutput(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open output file.\n");
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        fprintf(file, "%d\n", result[i]);
    }

    fclose(file);
}

void solveSimple() {
    memset(result, 0, sizeof(result));
    int remainingSpace[MAX_M];
    memcpy(remainingSpace, drawer, sizeof(drawer));

    for (int i = 0; i < N; i++) {
        int maxPower = -1;
        int bestDrawer = -1;

        for (int j = 0; j < M; j++) {
            if (onion[i] <= remainingSpace[j] && power[i][j] > maxPower) {
                maxPower = power[i][j];
                bestDrawer = j;
            }
        }

        if (bestDrawer != -1) {
            result[i] = bestDrawer + 1;
            remainingSpace[bestDrawer] -= onion[i];
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    readInput(argv[1]);
    solveSimple();
    writeOutput(argv[2]);

    return 0;
}