#include <stdio.h>

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    int a[10];
    for(int i=0;i<k;i++) scanf("%d", &a[i]);
    int step =0, time =0, m_current = m, index=0;
    while(step < n){
        int next_step = step + m_current;
        if(next_step >= n){
            time +=1;
            break;
        }
        time +=1;
        step = next_step;
        if(index < k && step == a[index]){
            m_current +=1;
            index++;
        }
    }
    printf("%d\n", time);
}