#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int list[20];
    int count;
    int min_denom;
} Solution;

int a, b;
Solution best;
int current_list[20];
int current_count;

ll gcd(ll a, ll b) {
    while (b != 0) {
        ll temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

void update_best() {
    if (current_count < best.count) {
        best.count = current_count;
        for(int i=0;i<current_count;i++) {
            best.list[i] = current_list[i];
        }
        best.min_denom = current_list[0];
    }
    else if (current_count == best.count) {
        if (current_list[0] > best.min_denom) {
            for(int i=0;i<current_count;i++) {
                best.list[i] = current_list[i];
            }
            best.min_denom = current_list[0];
        }
    }
}

void recurse(ll num, ll den, int start) {
    if (num == 0) {
        update_best();
        return;
    }
    if (current_count >= best.count)
        return;
    // Calculate the lower bound for d
    ll d_start = (den + num -1) / num;
    for(ll d = d_start; d <= 10000000; d++) {
        // Check if 1/d <= num/den
        if (d > 10000000) break;
        ll new_num = num * d - den;
        ll new_den = den * d;
        if (new_num < 0)
            continue;
        ll g = gcd(new_num, new_den);
        new_num /= g;
        new_den /= g;
        current_list[current_count] = d;
        current_count++;
        if (new_num == 0) {
            update_best();
        }
        else {
            recurse(new_num, new_den, d+1);
        }
        current_count--;
    }
}

int main(){
    scanf("%d %d", &a, &b);
    best.count = 100;
    best.min_denom = 0;
    recurse(a, b, 1);
    for(int i=0;i<best.count;i++) {
        if(i > 0) printf(" ");
        printf("%d", best.list[i]);
    }
    printf("\n");
    return 0;
}