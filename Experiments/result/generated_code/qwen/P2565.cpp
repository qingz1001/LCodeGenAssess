#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // Check if there is a solution
    int total_faces = n * m;
    if (total_faces <= n) {
        printf("0\n");
        return 0;
    }

    // Generate the dice faces
    int faces[total_faces];
    for (int i = 0; i < total_faces; i++) {
        faces[i] = i + 1;
    }

    // Shuffle the faces to ensure randomness
    for (int i = total_faces - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = faces[i];
        faces[i] = faces[j];
        faces[j] = temp;
    }

    // Assign faces to dice
    int dice[n][m];
    int face_index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dice[i][j] = faces[face_index++];
        }
    }

    // Print the dice faces
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", dice[i][j]);
        }
        printf("\n");
    }

    return 0;
}