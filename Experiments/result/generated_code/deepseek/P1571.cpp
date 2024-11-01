#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *tech_awards = (int *)malloc(n * sizeof(int));
    int *special_awards = (int *)malloc(m * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &tech_awards[i]);
    }

    for (int i = 0; i < m; i++) {
        scanf("%d", &special_awards[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (tech_awards[i] == special_awards[j]) {
                printf("%d ", tech_awards[i]);
                break;
            }
        }
    }

    free(tech_awards);
    free(special_awards);

    return 0;
}