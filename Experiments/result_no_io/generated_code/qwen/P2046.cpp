#include <stdio.h>
#include <stdlib.h>

#define MAXN 501

int main() {
    int n;
    scanf("%d", &n);

    long long total_force = 0;

    for (int i = 0; i < n * (n + 1); i++) {
        long long west_to_east;
        scanf("%lld", &west_to_east);
        total_force += west_to_east;
    }

    for (int i = 0; i < n * (n + 1); i++) {
        long long north_to_south;
        scanf("%lld", &north_to_south);
        total_force += north_to_south;
    }

    for (int i = 0; i < n * (n + 1); i++) {
        long long east_to_west;
        scanf("%lld", &east_to_west);
        total_force += east_to_west;
    }

    for (int i = 0; i < n * (n + 1); i++) {
        long long south_to_north;
        scanf("%lld", &south_to_north);
        total_force += south_to_north;
    }

    printf("%lld\n", total_force);

    return 0;
}