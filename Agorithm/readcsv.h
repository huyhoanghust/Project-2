#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define num_data_train  304
#define num_data_test   40

struct data
{
    int count;
    float x;
    float y;
    int RSSIA, RSSIB, RSSIC, RSSID;
    float weight;
};

struct data data_train[num_data_train] = {0};
struct data data_test[num_data_test] = {0};

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
            Data[row].count = (int)atof(strtok(buffer, ","));
            Data[row].x = (float)atof(strtok(NULL, ","));
            Data[row].y = (float)atof(strtok(NULL, ","));
            Data[row].RSSIA = (float)atof(strtok(NULL, ","));
            Data[row].RSSIB = (float)atof(strtok(NULL, ","));
            Data[row].RSSIC = (float)atof(strtok(NULL, ","));
            Data[row].RSSID = (float)atof(strtok(NULL, ","));
        }
        fclose(fp);
    }
}

void print_data(struct data Data[], int num)
{
    int i;
    for (i = 0; i < num ; i++)
    {
        printf("%f %f %f %f %f %f\n", Data[i].x, Data[i].y, Data[i].RSSIA, Data[i].RSSIB, Data[i].RSSIC,Data[i].RSSID);
    }
}