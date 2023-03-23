#include "KNN.h"

#define K 9
#define mode KNN

extern struct data data_train[num_data_train];
extern struct data data_test[num_data_test];

int main()
{
    read_csv(data_train, "A:/Train_points.csv");
    read_csv(data_test, "A:/Test_points.csv");
    print_data(data_train, num_data_train);
    printf("\n");
    print_data(data_test, num_data_test);
    float _error = 0;
    float average_error;
    int i;
    for (i = 1; i <= K; i++)
    {
    int j;
    for (j = 0; j < num_data_test; j++)
    {
        printf("K = %d\n", i);
        printf("Real coordinate of user is: x = %.2f(m); y = %.2f(m)\n", data_test[j].x, data_test[j].y);
        distance_Euclidean(data_test[j], data_train);
        position(i, mode, data_test[j], data_train);
        _error = _error + error[j];
    }
    average_error = _error / num_data_test;
    printf("Average Error of positioning: %.3f(m)\n", average_error);
    // position(3, data_test[0], data_train);
    count = 0;
    _error = 0;
    // }
    //     for (i = 1; i <= K; i++)
    //     {
    //         printf("K = %d\n", i);
    //             printf("Real coordinate of user is: x = %.2f(m); y = %.2f(m)\n", data_test[0].x, data_test[0].y);
    //             distance_Euclidean(data_test[0], data_train);
    //             position(i, mode, data_test[0], data_train);
    // //        printf("Average Error of positioning: %.3f(m)\n", average_error);
    //         // position(3, data_test[0], data_train);
    //         // count = 0;
    //         // _error = 0;
    }
    return 0;
}