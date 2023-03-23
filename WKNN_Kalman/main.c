#include "WKNN.h"
// #include <Eigen/Dense>

struct data data_train[num_data_train];
struct data data_test[num_data_test];

int main()
{
    read_file_data_train(47);
    read_file_data_test(11);
    // print_data(data_test, num_data_test);
    // print_data(data_train, num_data_train);
    float error1;
    int j;
    for (j = 0; j < num_data_test; j++)
    {
        Spatial_distance(data_test[j], data_train);
        int i;
        for (i = 1; i <= 5; i++)
        {
            printf("K = %d", i);
            Weight_distance(i, Weight_Spatial, SD, data_test[j], data_train);
            // printf("Real coordinate of user is: x = %.2f(m); y = %.2f(m)\n", data_test[j].x, data_test[j].y);
            WKNN(i, data_train);
            // error_position(j);
            error1 = sqrt(pow(x_test - data_test[j].x, 2) + pow(y_test - data_test[j].y, 2));
            printf("\tError: %.3f(m)\n", error1);
            x_test = 0;
            y_test = 0;
        }

        clear_valuable();
    }
    return 0;
}