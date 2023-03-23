#include "Readcsv.h"
#include <math.h>

#define K 20

float inverse = 0;

float SD[num_data_train] = {0};
int index_S[num_data_train] = {0};

int index_common[K] = {0};
int count = 0;

float Weight_Spatial[K] = {0};

float x_test = 0;
float y_test = 0;

float error[num_data_test];
int index_error = 0;

enum compare
{
    OKE,
    NOT_OKE
};
int check = NOT_OKE;

/*
intput:
    data test[i]
    data train
output:
    distance[]: distance Spatial
    index_S
*/
void Spatial_distance(struct data test, struct data train[])
{
    int i;
    for (i = 0; i < num_data_train; i++)
    {
        int j;
        for (j = 0; j < num_Access_point; j++)
        {
            SD[i] = SD[i] + pow(test.RSSI[j] - train[i].RSSI[j], 2);
        }
        SD[i] = sqrt(SD[i] / num_Access_point);
        index_S[i] = i;
    }
    Arrange(SD, index_S);
}
/*
input:
    k
    distance[]: distance Spatial
    data test[i]
    data train
output:
    Weight_spatial
*/
void Weight_distance(int k, float Weight[], float distance[], struct data user, struct data train[])
{
    int j;
    for (j = 0; j < k; j++)
    {
        inverse = inverse + 1.0 / distance[j];
    }
    int i;
    for (i = 0; i < k; i++)
    {
        Weight[i] = (1.0 / distance[i]) / inverse;
    }
    inverse = 0;
    // memset(Weight, 0, sizeof(Weight));
}

/*
intput:
    k
    data train
output:
    x
    y
*/
void WKNN(int k, struct data train[])
{
    int i;
    for (i = 0; i < k; i++)
    {
        x_test = x_test + Weight_Spatial[i] * train[index_S[i]].x;
        y_test = y_test + Weight_Spatial[i] * train[index_S[i]].y;
    }
    //printf("Coordinate of user predicted is: x = %.2f(m); y = %.2f(m)\n", x_test, y_test);
}

void error_position(int th)
{
    error[index_error] = sqrt(pow(x_test - data_test[th].x, 2) + pow(y_test - data_test[th].y, 2));
    //printf("Error: %.3f(m)\n", error[index_error]);
    index_error++;
    float error_average = 0;
    if (index_error == num_data_test)
    {
        int j;
        for (j = 0; j < num_data_test; j++)
        {
            error_average = error_average + error[j];
        }
        error_average = error_average / num_data_test;
        printf("Error average: %.3f(m)\n", error_average);
        index_error = 0;
    }
}

void clear_valuable()
{
    memset(SD, 0, sizeof(SD));
    memset(index_S, 0, sizeof(index_S));
    memset(index_common, 0, sizeof(index_common));
    count = 0;
    inverse = 0;
    x_test = 0;
    y_test = 0;
}
