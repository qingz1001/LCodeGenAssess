#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 100005

int n, m, q;
int room[MAX_M];
int last_exp[MAX_M];
int people[MAX_N];

void init() {
    memset(room, 0, sizeof(room));
    memset(last_exp, 0, sizeof(last_exp));
    for(int i = 1; i <= n; i++) {
        people[i] = 1;
        room[1]++;
    }
}

void move_person(int person, int to_room) {
    room[people[person]]--;
    room[to_room]++;
    people[person] = to_room;
}

int do_experiment(int l, int r) {
    int points = 0;
    for(int i = l; i <= r; i++) {
        if(room[i] > last_exp[i]) {
            points += room[i] - last_exp[i];
            last_exp[i] = room[i];
        }
    }
    return points;
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    init();

    char op;
    int a, b;
    for(int i = 0; i < q; i++) {
        scanf(" %c %d %d", &op, &a, &b);
        if(op == 'C') {
            move_person(a, b);
        } else if(op == 'W') {
            printf("%d\n", do_experiment(a, b));
        }
    }

    return 0;
}