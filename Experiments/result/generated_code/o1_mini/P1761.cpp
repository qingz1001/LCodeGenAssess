#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_X 2250000
#define STEP 0.001

int main(){
    int n;
    double s[51];
    while(scanf("%d", &n) && n !=0){
        for(int i=0;i<n;i++) scanf("%lf", &s[i]);
        double x[51];
        for(int i=0;i<n;i++){
            if(i==0){
                x[i] = s[i]/sqrt(2.0);
            }
            else{
                double max_x = 0.0;
                for(int j=0;j<i;j++){
                    double tmp = x[j] + (s[j] + s[i])/sqrt(2.0);
                    if(tmp > max_x) max_x = tmp;
                }
                x[i] = max_x;
            }
        }
        // Initialize height_max
        float *height_max = (float*)calloc(MAX_X +1, sizeof(float));
        int visible[51];
        memset(visible, 0, sizeof(visible));
        for(int i=n-1;i>=0;i--){
            double left = x[i] - s[i]/sqrt(2.0);
            double right = x[i] + s[i]/sqrt(2.0);
            if(left <0) left =0.0;
            int found =0;
            for(double pos = left; pos <= right && !found; pos += STEP){
                double height = s[i]/sqrt(2.0) - fabs(pos - x[i]);
                if(height > height_max[(int)(pos / STEP + 0.5)]){
                    visible[i] =1;
                    found =1;
                }
            }
            if(visible[i]){
                for(double pos = left; pos <= right; pos += STEP){
                    double height = s[i]/sqrt(2.0) - fabs(pos - x[i]);
                    int idx = (int)(pos / STEP + 0.5);
                    if(height > height_max[idx]){
                        height_max[idx] = (float)height;
                    }
                }
            }
        }
        // Print visible indices in ascending order
        for(int i=0;i<n;i++) if(visible[i]){
            printf("%d ", i+1);
        }
        printf("\n");
        free(height_max);
    }
    return 0;
}