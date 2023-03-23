#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char des[40] = "\n";
int count = 0;
float aver[30];
int indexx = 1;
char buf[10];
float average = 0.0;

int check = 1;

char path[10];
int main()
{
    FILE *fpcsv = fopen("E:/test_w_csv.csv", "w");
    if (!fpcsv)
        printf("FileWrite Can't open file\n");
    char buffer[30] = {0};
    int i;
    for (i = 1; i <= 40; i++)
    {
        sprintf(path, "E:/Test_points/%d.txt", i);
        FILE *fp = fopen(path, "r");
        if (!fp)
        {
            printf("FileRead Can't open file\n");
        }
        else
        {
            while (fgets(buffer, 30, fp))
            {
                aver[count] = atof(buffer);
                average = average + aver[count];
                count++;
                if (indexx == 30)
                {
                    average = average / 30.0;
                    printf("%.4f\n",average);
                    if (check != 4)
                    {

                        sprintf(buf, "%.4f,", average);
                    }
                    else
                    {
                        sprintf(buf, "%.4f", average);
                    }
                    strcat(des, buf);
                    check++;
                    count = 0;
                    indexx=0;
                }
                indexx++;
                memset(buffer, 0, sizeof(buffer));
                // if (strcmp(buffer, "RSSI trung binh:\n") == 0)
                // {

                //     while (fgets(buffer, 30, fp))
                //     {
                //         if (count != 4)
                //         {
                //             buffer[strcspn(buffer, "\n")] = ',';
                //             strcat(des, buffer);
                //         }
                //         else
                //         {
                //             buffer[strcspn(buffer, "\n")] = '\0';
                //             strcat(des, buffer);
                //         }
                //         count++;
                //         // puts(buffer);
                //     }
                //     break;
                // }
                // memset(buffer, 0, sizeof(buffer));
            }
            fprintf(fpcsv, "%s\n", des);
            memset(des, 0, sizeof(des));
            // puts(des);
            fclose(fp);
        }
    }

    fclose(fpcsv);
}
