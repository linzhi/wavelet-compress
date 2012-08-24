#include <iostream>
#include <cmath>
using namespace std;

void DataQuantize2D(double **data_input, int hei, int wid, int value)
{
    int i;
    int j;
    double temp;
    
    if (value > 255)
        value = 255;
    if (value < 0)
        value = 0;
    
    for (i = 0; i < hei; i++)
    {
        for (j = 0; j < wid; j++)
        {
            temp = data_input[i][j];
            if (abs(temp) <= value)
                data_input[i][j] = 0.0;
        }
    }
}

void DataQuantize3D(double ***data_input, int lon, int wid, int hei, int value)
{
    int i;
    int j;
    int k;
    double temp;
    
    if (value > 255)
        value = 255;
    if (value < 0)
        value = 0;
    
    for (i = 0; i < lon; i++)
    {
        for (j = 0; j < wid; j++)
        {
            for (k = 0; k < hei; k++)
            {
                temp = data_input[i][j][k];
                if (abs(temp) <= value)
                    data_input[i][j][k] = 0.0;
            }
        }
    }
}
