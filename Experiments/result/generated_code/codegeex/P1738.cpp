#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    char paths[n][101];
    int totalFolders = 0;
    int maxFolders = 0;

    for (int i = 0; i < n; i++) {
        scanf("%s", paths[i]);
        int currentFolders = 0;
        int pathLength = strlen(paths[i]);
        int j = 0;

        while (j < pathLength) {
            if (paths[i][j] == '/') {
                currentFolders++;
                totalFolders++;
            }
            j++;
        }

        maxFolders = (maxFolders > currentFolders) ? maxFolders : currentFolders;
        printf("%d\n", totalFolders);
    }

    return 0;
}