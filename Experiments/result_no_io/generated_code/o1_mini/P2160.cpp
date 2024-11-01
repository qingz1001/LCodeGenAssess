#include <stdio.h>
#include <stdlib.h>

// Maximum number of books
#define MAX_N 70

typedef struct {
    int h;
    int t;
} Book;

Book books[MAX_N];
int n;
long long min_S = 1e18;

// Function to compare books in descending order of height, then thickness
int compare(const void *a, const void *b) {
    Book *ba = (Book *)a;
    Book *bb = (Book *)b;
    if (ba->h != bb->h)
        return bb->h - ba->h;
    return bb->t - ba->t;
}

// Recursive DFS function
void dfs(int index, int h1, int h2, int h3, int t1, int t2, int t3) {
    if (index == n) {
        // All books assigned, calculate S
        int sum_h = h1 + h2 + h3;
        int max_t = t1;
        if (t2 > max_t) max_t = t2;
        if (t3 > max_t) max_t = t3;
        long long S = (long long)sum_h * (long long)max_t;
        if (S < min_S) min_S = S;
        return;
    }

    // Assign current book to shelf 1
    int new_h1 = (books[index].h > h1) ? books[index].h : h1;
    int new_t1 = t1 + books[index].t;
    // Prune if current S cannot be better
    long long current_sum_h = new_h1 + h2 + h3;
    int current_max_t = (new_t1 > t2) ? new_t1 : t2;
    current_max_t = (current_max_t > t3) ? current_max_t : t3;
    long long current_S = (long long)current_sum_h * (long long)current_max_t;
    if (current_S < min_S)
        dfs(index + 1, new_h1, h2, h3, new_t1, t2, t3);

    // Assign current book to shelf 2
    int new_h2 = (books[index].h > h2) ? books[index].h : h2;
    int new_t2 = t2 + books[index].t;
    current_sum_h = h1 + new_h2 + h3;
    current_max_t = (t1 > new_t2) ? t1 : new_t2;
    current_max_t = (current_max_t > t3) ? current_max_t : t3;
    current_S = (long long)current_sum_h * (long long)current_max_t;
    if (current_S < min_S)
        dfs(index + 1, h1, new_h2, h3, t1, new_t2, t3);

    // Assign current book to shelf 3
    int new_h3 = (books[index].h > h3) ? books[index].h : h3;
    int new_t3 = t3 + books[index].t;
    current_sum_h = h1 + h2 + new_h3;
    current_max_t = (t1 > t2) ? t1 : t2;
    current_max_t = (current_max_t > new_t3) ? current_max_t : new_t3;
    current_S = (long long)current_sum_h * (long long)current_max_t;
    if (current_S < min_S)
        dfs(index + 1, h1, h2, new_h3, t1, t2, new_t3);
}

int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++) {
        scanf("%d %d", &books[i].h, &books[i].t);
    }
    // Sort books in descending order of height
    qsort(books, n, sizeof(Book), compare);
    // Initialize shelves with 0 height and thickness
    dfs(0, 0, 0, 0, 0, 0, 0);
    printf("%lld\n", min_S);
    return 0;
}