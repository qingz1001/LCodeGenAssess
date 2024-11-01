#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 300

double similarity[MAX_N + 1][MAX_N + 1];
int parent1[MAX_N + 1], parent2[MAX_N + 1];

void calculate_similarity(int x, int y) {
    if (similarity[x][y] >= 0) return;
    
    if (x == y) {
        similarity[x][y] = 1.0;
        return;
    }
    
    if (parent1[x] == 0 || parent1[y] == 0) {
        similarity[x][y] = 0.0;
        return;
    }
    
    calculate_similarity(parent1[x], parent1[y]);
    calculate_similarity(parent1[x], parent2[y]);
    calculate_similarity(parent2[x], parent1[y]);
    calculate_similarity(parent2[x], parent2[y]);
    
    similarity[x][y] = (similarity[parent1[x]][parent1[y]] +
                        similarity[parent1[x]][parent2[y]] +
                        similarity[parent2[x]][parent1[y]] +
                        similarity[parent2[x]][parent2[y]]) / 4.0;
}

void print_percentage(double value) {
    int percentage = (int)(value * 10000 + 0.5);
    if (percentage == 0) {
        printf("0%%\n");
    } else if (percentage % 100 == 0) {
        printf("%d%%\n", percentage / 100);
    } else {
        printf("%d.%02d%%\n", percentage / 100, percentage % 100);
    }
}

int main() {
    int n, k, m;
    scanf("%d %d", &n, &k);
    
    memset(parent1, 0, sizeof(parent1));
    memset(parent2, 0, sizeof(parent2));
    
    for (int i = 0; i < k; i++) {
        int child, p1, p2;
        scanf("%d %d %d", &child, &p1, &p2);
        parent1[child] = p1;
        parent2[child] = p2;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            similarity[i][j] = -1;
        }
    }
    
    scanf("%d", &m);
    
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        calculate_similarity(x, y);
        print_percentage(similarity[x][y]);
    }
    
    return 0;
}