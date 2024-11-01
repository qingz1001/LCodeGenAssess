#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 40005
#define MAXQ 100005
#define MAXLEN 10005

typedef struct {
    char s[MAXLEN];
    int id;
} String;

int cmp(const void *a, const void *b){
    String *sa = (String*)a;
    String *sb = (String*)b;
    return strcmp(sa->s, sb->s);
}

int lcp_func(char *a, char *b){
    int l = 0;
    while(a[l] && b[l] && a[l]==b[l]) l++;
    return l;
}

typedef struct {
    int X, Y;
    int idx;
} Task;

int main(){
    int n, q;
    scanf("%d %d", &n, &q);
    String strings[MAXN];
    for(int i=0;i<n;i++){
        scanf("%s", strings[i].s);
        strings[i].id = i+1;
    }
    q = q;
    Task tasks[MAXQ];
    for(int i=0;i<q;i++){
        scanf("%d %d", &tasks[i].X, &tasks[i].Y);
        tasks[i].idx = i+1;
    }
    // Sort strings
    qsort(strings, n, sizeof(String), cmp);
    // Compute W(P*_G)
    long long W = 0;
    for(int i=1;i<n;i++){
        int lcp = lcp_func(strings[i-1].s, strings[i].s);
        W += (long long)lcp * lcp;
    }
    printf("%lld\n", W);
    // Prepare mapping from pair to task with max i
    // Using a simple approach since n <= 40000
    // Create position mapping
    int pos[MAXN];
    for(int i=0;i<n;i++) pos[strings[i].id] = i;
    // For each task, check if it can be an adjacent pair
    // We want to maximize the sum of 2^i, so prefer higher i
    // Use an array to store for each adjacent pair the max task index
    long long rewards = 0;
    int selected[MAXQ];
    memset(selected, 0, sizeof(selected));
    // To store the selected task indices
    int selected_tasks[MAXQ];
    int cnt = 0;
    // Create a mapping from pairs to the best task
    // To optimize, iterate tasks from high to low i
    // and assign to pairs if not already assigned
    // Sort tasks by decreasing idx
    qsort(tasks, q, sizeof(Task), 
        [](const void *a, const void *b) -> int {
            Task *ta = (Task*)a;
            Task *tb = (Task*)b;
            return tb->idx - ta->idx;
        });
    // Array to mark which adjacent pairs are used
    int used[MAXN];
    memset(used, 0, sizeof(used));
    for(int i=0;i<q;i++){
        int X = tasks[i].X;
        int Y = tasks[i].Y;
        if(pos[X]+1 == pos[Y] && !used[pos[X]]){
            used[pos[X]] = 1;
            selected_tasks[cnt++] = tasks[i].idx;
        }
    }
    // Sort selected_tasks
    qsort(selected_tasks, cnt, sizeof(int), 
        [](const void *a, const void *b) -> int {
            return (*(int*)a) - (*(int*)b);
        });
    // Print k and task indices
    printf("%d", cnt);
    for(int i=0;i<cnt;i++) printf(" %d", selected_tasks[i]);
    printf("\n");
    // Print permutation
    for(int i=0;i<n;i++) printf("%d%c", strings[i].id, (i==n-1)?'\n':' ');
    return 0;
}