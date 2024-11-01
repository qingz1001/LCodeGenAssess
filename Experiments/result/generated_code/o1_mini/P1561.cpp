#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int U;
    int D;
} Cow;

int compare_s1(const void *a, const void *b) {
    Cow *cowA = (Cow *)a;
    Cow *cowB = (Cow *)b;
    if (cowA->U != cowB->U)
        return cowA->U - cowB->U;
    return cowA->D - cowB->D;
}

int compare_s2(const void *a, const void *b) {
    Cow *cowA = (Cow *)a;
    Cow *cowB = (Cow *)b;
    if (cowB->D != cowA->D)
        return cowB->D - cowA->D;
    return cowA->U - cowB->U;
}

int main(){
    int N;
    scanf("%d", &N);
    Cow *s1 = (Cow*)malloc(N * sizeof(Cow));
    Cow *s2 = (Cow*)malloc(N * sizeof(Cow));
    int s1_count=0, s2_count=0;
    for(int i=0;i<N;i++){
        int U, D;
        scanf("%d %d", &U, &D);
        if(U <= D){
            s1[s1_count].U = U;
            s1[s1_count].D = D;
            s1_count++;
        }
        else{
            s2[s2_count].U = U;
            s2[s2_count].D = D;
            s2_count++;
        }
    }
    qsort(s1, s1_count, sizeof(Cow), compare_s1);
    qsort(s2, s2_count, sizeof(Cow), compare_s2);
    long long t_up=0, t_down=0;
    for(int i=0;i<s1_count;i++){
        t_up += s1[i].U;
        if(t_down < t_up)
            t_down = t_up;
        t_down += s1[i].D;
    }
    for(int i=0;i<s2_count;i++){
        t_up += s2[i].U;
        if(t_down < t_up)
            t_down = t_up;
        t_down += s2[i].D;
    }
    printf("%lld\n", t_down);
    free(s1);
    free(s2);
    return 0;
}