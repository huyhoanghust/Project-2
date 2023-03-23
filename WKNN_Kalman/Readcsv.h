#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define num_data_train  10054
#define num_data_test   2107
#define num_Access_point    9

struct data
{
    char *time;
    int count;
    float x;
    float y;
    float RSSI[num_Access_point];
    float TP_distance[num_Access_point];
    float RP_distance[num_Access_point];
    float weight;
};

struct data data_train[num_data_train] = {0};
struct data data_test[num_data_test] = {0};

int indexx = 0;

void read_csv(struct data Data[], char* path)
{
    // Substitute the full file path
    // for the string file_path
    FILE *fp = fopen(path, "r");

    if (!fp)
        printf("Can't open file\n");

    else
    {
        // Here we have taken size of
        // array 1024 you can modify it
        char buffer[1024];

        int row = -2;
        while (fgets(buffer, 1024, fp))
        {
            row++;
            if (row == -1)
                continue;

            // Splitting the data
            Data[indexx].time = strtok(buffer, ",");
            Data[indexx].count = (int)atof(strtok(NULL, ","));
            Data[indexx].x = (float)atof(strtok(NULL, ","));
            Data[indexx].y = (float)atof(strtok(NULL, ","));
            int i;
            for (i = 0; i<num_Access_point;i++)
            {
                Data[indexx].RSSI[i] = (float)atof(strtok(NULL, ","));
            }
            indexx++;
        }
        fclose(fp);
    }
}

void print_data(struct data Data[], int num)
{
    int i;
    for (i = 0; i < num ; i++)
    {
        printf("%f %f ", Data[i].x, Data[i].y);
        int k;
        for(k =0; k<num_Access_point;k++)
        {
            printf("%f ", Data[i].RSSI[k]);
        }
        printf("\n");
    }
}

void Arrange(float distance[], int index[])
{
    // arrange elements tend to increase
    int k, m;
    float tg1;
    int tg2;
    for (k = 0; k < num_data_train - 1; k++)
    {
        for (m = k + 1; m < num_data_train; m++)
        {
            if (distance[k] > distance[m])
            {
                //arrange distance
                tg1 = distance[k];
                distance[k] = distance[m];
                distance[m] = tg1;
                //arrange index
                tg2 = index[k];
                index[k]=index[m];
                index[m]=tg2;
            }
        }
    }
}

void read_file_data_train(int num_file)
{
    char path[30];
    int i;
    for(i=1;i<=num_file;i++)
    {
        sprintf(path, "D:/data_project2/train/data (%d).csv", i);
        read_csv(data_train, path);
    }
    indexx = 0;
}

void read_file_data_test(int num_file)
{
    char path[30];
    int i;
    for(i=1;i<=num_file;i++)
    {
        sprintf(path, "D:/data_project2/test/test (%d).csv", i);
        read_csv(data_test, path);
    }
    indexx = 0;
}