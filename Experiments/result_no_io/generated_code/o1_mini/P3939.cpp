#include <stdio.h>

#define MAXN 100005
#define MAXC 1000001

int a[MAXN];
int total_count_arr[MAXC];

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++){
        scanf("%d", &a[i]);
        total_count_arr[a[i]]++;
    }
    for(int i=0;i<m;i++){
        int type;
        scanf("%d", &type);
        if(type ==1){
            int l, r, c;
            scanf("%d %d %d", &l, &r, &c);
            int len = r - l +1;
            int count =0;
            if(len <=20){
                for(int j=l; j<=r; j++) if(a[j]==c) count++;
            }
            else{
                count = total_count_arr[c];
                for(int j=1; j<l; j++) if(a[j]==c) count--;
                for(int j=r+1; j<=n; j++) if(a[j]==c) count--;
            }
            printf("%d\n", count);
        }
        else if(type ==2){
            int x;
            scanf("%d", &x);
            int tmp = a[x];
            a[x] = a[x+1];
            a[x+1] = tmp;
        }
    }
    return 0;
}