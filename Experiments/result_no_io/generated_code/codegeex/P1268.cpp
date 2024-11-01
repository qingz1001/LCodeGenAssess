#include <stdio.h>
#include <stdlib.h>

#define MAXN 30
#define INF 100

int n;
int m[MAXN][MAXN];

// Function to find the minimum of three integers
int min(int a, int b, int c) {
    if (a <= b && a <= c)
        return a;
    else if (b <= a && b <= c)
        return b;
    else
        return c;
}

// Function to calculate the weight of the tree
int calculateWeight() {
    int totalWeight = 0;
    while (n > 2) {
        int minWeight = INF, minIndex = -1;
        // Find the pair of nodes with the minimum distance
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (m[i][j] < minWeight) {
                    minWeight = m[i][j];
                    minIndex = i;
                }
            }
        }
        // Calculate the weight of the new edge
        totalWeight += minWeight;
        // Merge the two nodes into one new node
        for (int i = 0; i < n; i++) {
            if (i != minIndex && i != minIndex + 1) {
                m[minIndex][i] = m[i][minIndex] = min(m[minIndex][i], m[minIndex + 1][i], m[minIndex][minIndex + 1]) + m[minIndex][minIndex + 1];
                m[i][minIndex + 1] = m[minIndex + 1][i] = INF;
            }
        }
        // Remove the last row and column
        n--;
    }
    return totalWeight;
}

int main() {
    // Read the number of nodes
    scanf("%d", &n);
    // Read the upper triangular matrix
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            scanf("%d", &m[i][j]);
            m[j][i] = m[i][j];
        }
    }
    // Initialize the diagonal elements to zero
    for (int i = 0; i < n; i++) {
        m[i][i] = 0;
    }
    // Calculate and print the weight of the tree
    printf("%d\n", calculateWeight());
    return 0;
}