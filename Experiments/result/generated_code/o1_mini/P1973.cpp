#include<stdio.h>
#include<stdlib.h>

typedef struct {
    long long start;
    long long end;
    int index;
} Activity;

int cmp(const void* a, const void* b){
    Activity* aa = (Activity*)a;
    Activity* bb = (Activity*)b;
    if(aa->start != bb->start)
        return aa->start < bb->start ? -1 : 1;
    return aa->end < bb->end ? -1 : 1;
}

int main(){
    int n;
    scanf("%d", &n);
    Activity activities[n];
    for(int i=0;i<n;i++){
        scanf("%lld %lld", &activities[i].start, &activities[i].end);
        activities[i].end += activities[i].start;
        activities[i].index = i;
    }
    qsort(activities, n, sizeof(Activity), cmp);
    // Without constraints
    // Assign to A and B greedily
    long long lastA = -1, lastB = -1;
    int countA = 0, countB = 0;
    for(int i=0;i<n;i++){
        if(activities[i].start >= lastA){
            lastA = activities[i].end;
            countA++;
        }
        if(activities[i].start >= lastB){
            lastB = activities[i].end;
            countB++;
        }
    }
    int res = countA < countB ? countA : countB;
    printf("%d\n", res);
    // For each activity, force include it
    for(int forced=0; forced<n; forced++){
        // Try assigning forced to A
        long long faA = activities[forced].end;
        long long faB = -1;
        int ca = 1, cb = 0;
        for(int i=0;i<n;i++){
            if(i == forced) continue;
            if(activities[i].start >= faA){
                faA = activities[i].end;
                ca++;
            }
        }
        // Assign forced to B
        faA = -1;
        faB = activities[forced].end;
        cb = 1;
        for(int i=0;i<n;i++){
            if(i == forced) continue;
            if(activities[i].start >= faB){
                faB = activities[i].end;
                cb++;
            }
        }
        int current = (ca < cb) ? ca : cb;
        printf("%d\n", current);
    }
    return 0;
}