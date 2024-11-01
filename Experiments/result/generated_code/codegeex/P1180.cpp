#include <stdio.h>
#include <stdlib.h>

int main() {
    double distance, max_capacity, km_per_liter, initial_cost;
    int num_stations;
    double *stations_distance, *stations_price;
    double *dp, current_fuel, current_cost;

    // 读取输入
    scanf("%lf", &distance);
    scanf("%lf %lf %lf %d", &max_capacity, &km_per_liter, &initial_cost, &num_stations);

    stations_distance = (double *)malloc(num_stations * sizeof(double));
    stations_price = (double *)malloc(num_stations * sizeof(double));

    for (int i = 0; i < num_stations; i++) {
        scanf("%lf %lf", &stations_distance[i], &stations_price[i]);
    }

    // 初始化动态规划数组
    dp = (double *)calloc(num_stations, sizeof(double));

    // 从第一个加油站开始
    for (int i = 0; i < num_stations; i++) {
        current_fuel = max_capacity;
        current_cost = initial_cost;

        // 遍历每个加油站
        for (int j = i; j < num_stations; j++) {
            double distance_to_next_station = j == 0 ? stations_distance[j] : stations_distance[j] - stations_distance[j - 1];
            double fuel_needed = distance_to_next_station / km_per_liter;

            // 如果油不够到下一个加油站，则加满油
            if (current_fuel < fuel_needed) {
                current_cost += (max_capacity - current_fuel) * stations_price[i];
                current_cost += 20; // 加油站付钱四舍五入到0.1元
                current_fuel = max_capacity;
            }

            // 更新当前油量
            current_fuel -= fuel_needed;

            // 更新动态规划数组
            if (j == 0) {
                dp[j] = current_cost;
            } else {
                dp[j] = current_cost + (max_capacity - current_fuel) * stations_price[j];
            }

            current_cost = dp[j];
        }
    }

    // 输出结果
    printf("%.1lf\n", dp[num_stations - 1]);

    // 释放内存
    free(stations_distance);
    free(stations_price);
    free(dp);

    return 0;
}