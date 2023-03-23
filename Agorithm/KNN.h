#include "readcsv.h"
#include "string.h"
#include "math.h"

// extern struct data;
enum Mode
{
    KNN,
    WKNN
};

enum Mode mode;

float distance;
float arr_distance[num_data_train] = {0};
float arr_distance_copy[num_data_train] = {0};
int count = 0;
float error[num_data_test];
// float weight;
float total_distance = 0;

void distance_Euclidean(struct data test, struct data train[])
{
    int i;
    for (i = 0; i < num_data_train; i++)
    {
        distance = 1 / sqrt(3) * sqrt(pow(test.RSSIA - train[i].RSSIA, 2) + pow(test.RSSIB - train[i].RSSIB, 2) + pow(test.RSSIC - train[i].RSSIC, 2)+pow(test.RSSID - train[i].RSSID, 2));
        arr_distance[i] = distance;
        arr_distance_copy[i] = arr_distance[i];
    }
    int n, m;
    float tg;
    // arrange elements tend to increase
    for (n = 0; n < num_data_train - 1; n++)
    {
        for (m = n + 1; m < num_data_train; m++)
        {
            if (arr_distance[n] > arr_distance[m])
            {
                tg = arr_distance[n];
                arr_distance[n] = arr_distance[m];
                arr_distance[m] = tg;
            }
        }
    }
    // int v;
    //     for (v = 0; v < 30; v++)
    // {
    //     printf("%f ", arr_distance[v]);
    // }
}

void position(int k, enum Mode mode, struct data user, struct data train[])
{
    float arr_distance_copy1[num_data_train] = {0};
    int r;
    // copy array distance
    for (r = 0; r < num_data_train; r++)
    {
        arr_distance_copy1[r] = arr_distance_copy[r];
    }
    int index[k];
    float average_x = 0;
    float average_y = 0;
    int i, l = 0;
    // choose k points have smallest E distance
    for (i = 0; i < k; i++)
    {
        int j;
        for (j = 0; j < num_data_train; j++)
        {
            if (arr_distance[i] == arr_distance_copy1[j])
            {
                index[l++] = j;
                arr_distance_copy1[j] = 0;
                break;
            }
        }
    }
    // check mode KNN
    if (mode == KNN)
    {
        for (i = 0; i < k; i++)
        {
            average_x = average_x + train[index[i]].x;
            average_y = average_y + train[index[i]].y;
        }
        average_x = average_x / k;
        average_y = average_y / k;
        // printf("K = %d\n", k);
        // printf("Coordinate of user predicted is: x = %.2f(m); y = %.2f(m)\n", average_x, average_y);

        // // error_positioning
        // error[count] = sqrt(pow(user.x - average_x, 2) + pow(user.y - average_y, 2));
        // printf("Error of positioning: %.3f(m)\n", error[count]);
        // count++;
    }
    // check mode WKNN
    if (mode == WKNN)
    {
        for (i = 0; i < k; i++)
        {
            total_distance = total_distance + 1 / arr_distance_copy[index[i]];
        }
        for (i = 0; i < k; i++)
        {
            train[index[i]].weight = (1 / arr_distance_copy[index[i]]) / total_distance;
            average_x = average_x + train[index[i]].weight * train[index[i]].x;
            average_y = average_y + train[index[i]].weight * train[index[i]].y;
        }
        total_distance = 0;
        // printf("Coordinate of user predicted is: x = %.2f(m); y = %.2f(m)\n", average_x, average_y);
    }
    printf("Coordinate of user predicted is: x = %.2f(m); y = %.2f(m)\n", average_x, average_y);

    // error_positioning
    error[count] = sqrt(pow(user.x - average_x, 2) + pow(user.y - average_y, 2));
    printf("Error of positioning: %.3f(m)\n", error[count]);
    count++;
}

// void handle_positioning()
