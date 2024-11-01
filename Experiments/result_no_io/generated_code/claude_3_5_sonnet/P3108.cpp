#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100000
#define MAX_COORD 1000000000

typedef long long ll;

struct Mirror {
    ll x, y;
    char type;
};

struct Mirror mirrors[MAX_N];
int N;
ll Bx, By;

int cmp(const void *a, const void *b) {
    struct Mirror *m1 = (struct Mirror *)a;
    struct Mirror *m2 = (struct Mirror *)b;
    if (m1->x != m2->x) return m1->x - m2->x;
    return m1->y - m2->y;
}

int binary_search(ll x, ll y) {
    int l = 0, r = N - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (mirrors[mid].x == x && mirrors[mid].y == y) return 1;
        if (mirrors[mid].x < x || (mirrors[mid].x == x && mirrors[mid].y < y)) l = mid + 1;
        else r = mid - 1;
    }
    return 0;
}

int main() {
    scanf("%d %lld %lld", &N, &Bx, &By);
    for (int i = 0; i < N; i++) {
        scanf("%lld %lld %c", &mirrors[i].x, &mirrors[i].y, &mirrors[i].type);
    }
    qsort(mirrors, N, sizeof(struct Mirror), cmp);

    ll count = 0;
    ll x = 0, y = 0, dx = 0, dy = 1;

    while (1) {
        ll nx = x + dx, ny = y + dy;
        if (nx == Bx && ny == By) {
            count++;
            break;
        }
        if (abs(nx) > MAX_COORD || abs(ny) > MAX_COORD) break;

        int found = binary_search(nx, ny);
        if (!found) {
            x = nx;
            y = ny;
            continue;
        }

        char type = mirrors[found].type;
        if ((dx == 0 && type == '/') || (dy == 0 && type == '\\')) {
            ll temp = dx;
            dx = dy;
            dy = temp;
        } else {
            ll temp = dx;
            dx = -dy;
            dy = -temp;
        }
        x = nx;
        y = ny;
    }

    x = 0, y = 0, dx = 0, dy = 1;
    while (1) {
        ll nx = x + dx, ny = y + dy;
        if (abs(nx) > MAX_COORD || abs(ny) > MAX_COORD) break;

        if (!binary_search(nx, ny)) {
            ll tx = nx, ty = ny;
            if (dx == 0) {
                tx = Bx;
                ty = ny + (Bx - nx);
            } else {
                ty = By;
                tx = nx + (By - ny);
            }
            if (tx == Bx && ty == By && !binary_search(nx, ny)) count++;
        }

        int found = binary_search(nx, ny);
        if (!found) {
            x = nx;
            y = ny;
            continue;
        }

        char type = mirrors[found].type;
        if ((dx == 0 && type == '/') || (dy == 0 && type == '\\')) {
            ll temp = dx;
            dx = dy;
            dy = temp;
        } else {
            ll temp = dx;
            dx = -dy;
            dy = -temp;
        }
        x = nx;
        y = ny;
    }

    printf("%lld\n", count);
    return 0;
}