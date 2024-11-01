#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 1024
#define MAX_N 50
#define MAX_SIZE 10000

typedef struct {
    int size;
    int index;
} Person;

int compare_desc(const void *a, const void *b) {
    Person *pa = (Person *)a;
    Person *pb = (Person *)b;
    if (pb->size != pa->size)
        return pb->size - pa->size;
    else
        return pa->index - pb->index;
}

int compare_cakes_desc(const void *a, const void *b) {
    return (*(int*)b) - (*(int*)a);
}

int main(){
    int n;
    scanf("%d", &n);
    int cakes[MAX_N];
    for(int i=0;i<n;i++) scanf("%d", &cakes[i]);
    qsort(cakes, n, sizeof(int), compare_cakes_desc);
    int m;
    scanf("%d", &m);
    Person people[MAX_M];
    for(int i=0;i<m;i++){
        scanf("%d", &people[i].size);
        people[i].index = i;
    }
    qsort(people, m, sizeof(Person), compare_desc);
    int used[MAX_M];
    memset(used, 0, sizeof(used));
    int total_assigned = 0;
    for(int i=0;i<n;i++){
        int size = cakes[i];
        int dp[size+1];
        int track[size+1];
        for(int s=0;s<=size;s++) {
            dp[s] = -1;
            track[s] = -1;
        }
        dp[0] = 0;
        for(int j=0;j<m;j++){
            if(used[people[j].index]) continue;
            int p_size = people[j].size;
            for(int s=size; s>=p_size; s--){
                if(dp[s - p_size] != -1 && dp[s - p_size] +1 > dp[s]){
                    dp[s] = dp[s - p_size] +1;
                    track[s] = j;
                }
            }
        }
        if(dp[size] == -1) continue;
        total_assigned += dp[size];
        int s = size;
        while(s > 0){
            int j = track[s];
            if(j == -1) break;
            used[people[j].index] = 1;
            s -= people[j].size;
        }
    }
    printf("%d\n", total_assigned);
    return 0;
}