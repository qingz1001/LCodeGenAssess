extern int Seniorious(int);

int Chtholly(int n, int c) {
    int left = 1;
    int right = n;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int result = Seniorious(mid);
        
        if (result == 0) {
            return mid;  // 找到了正确的数
        } else if (result == 1) {
            right = mid - 1;  // 目标数小于mid
        } else {
            left = mid + 1;  // 目标数大于mid
        }
    }
    
    return left;  // 如果循环结束仍未找到，返回left
}