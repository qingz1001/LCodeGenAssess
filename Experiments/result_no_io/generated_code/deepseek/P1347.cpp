#include <stdio.h>
#include <stdbool.h>

#define MAXN 26
#define MAXM 600

int n, m;
int graph[MAXN][MAXN];
int inDegree[MAXN];
bool visited[MAXN];

bool topologicalSort(int result[]) {
    int inDegreeCopy[MAXN];
    for (int i = 0; i < n; i++) {
        inDegreeCopy[i] = inDegree[i];
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (inDegreeCopy[j] == 0 && !visited[j]) {
                count++;
                if (count > 1) return false; // More than one node with 0 in-degree
                result[index++] = j;
                visited[j] = true;
                for (int k = 0; k < n; k++) {
                    if (graph[j][k]) {
                        inDegreeCopy[k]--;
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        char a, b;
        scanf(" %c<%c", &a, &b);
        int u = a - 'A';
        int v = b - 'A';
        if (graph[u][v] == 0) {
            graph[u][v] = 1;
            inDegree[v]++;
        }

        int result[MAXN];
        for (int j = 0; j < n; j++) {
            visited[j] = false;
        }

        if (topologicalSort(result)) {
            bool sorted = true;
            for (int j = 0; j < n; j++) {
                if (!visited[j]) {
                    sorted = false;
                    break;
                }
            }
            if (sorted) {
                printf("Sorted sequence determined after %d relations: ", i + 1);
                for (int j = 0; j < n; j++) {
                    printf("%c", result[j] + 'A');
                }
                printf(".\n");
                return 0;
            }
        } else {
            printf("Inconsistency found after %d relations.\n", i + 1);
            return 0;
        }
    }
    printf("Sorted sequence cannot be determined.\n");
    return 0;
}