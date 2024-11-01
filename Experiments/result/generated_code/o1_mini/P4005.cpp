#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int left;
    int right;
} Line;

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n;
        scanf("%d", &n);
        int a[n];
        for(int i=0;i<n;i++) scanf("%d", &a[i]);
        // Find lines with two transfer points
        int freq[101] = {0};
        for(int i=0;i<n;i++) freq[a[i]]++;
        Line lines[n/2 +1];
        int m=0;
        int first[101];
        for(int i=0;i<101;i++) first[i]=-1;
        for(int i=0;i<n;i++){
            if(freq[a[i]] ==2){
                if(first[a[i]]==-1){
                    first[a[i]]=i+1;
                }
                else{
                    lines[m].left = first[a[i]];
                    lines[m].right = i+1;
                    m++;
                }
            }
        }
        // Sort lines by left
        for(int i=0;i<m-1;i++){
            for(int j=i+1;j<m;j++){
                if(lines[i].left > lines[j].left){
                    Line temp = lines[i];
                    lines[i] = lines[j];
                    lines[j] = temp;
                }
            }
        }
        // Count crossings
        int crossings=0;
        for(int i=0;i<m;i++){
            for(int j=i+1;j<m;j++){
                if(lines[i].left < lines[j].left && lines[j].right < lines[i].right){
                    crossings++;
                }
            }
        }
        printf("%d ", crossings);
    }
    return 0;
}