#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *tech_awardees = (int *)malloc(n * sizeof(int));
    int *special_awardees = (int *)malloc(m * sizeof(int));

    for (int i = 0; i < n; ++i) {
        scanf("%d", &tech_awardees[i]);
    }

    for (int i = 0; i < m; ++i) {
        scanf("%d", &special_awardees[i]);
    }

    int tech_index = 0, special_index = 0;
    while (tech_index < n && special_index < m) {
        if (tech_awardees[tech_index] == special_awardees[special_index]) {
            printf("%d ", tech_awardees[tech_index]);
            ++tech_index;
            ++special_index;
        } else if (tech_awardees[tech_index] < special_awardees[special_index]) {
            ++tech_index;
        } else {
            ++special_index;
        }
    }

    free(tech_awardees);
    free(special_awardees);

    return 0;
}