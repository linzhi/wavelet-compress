#include <iostream>
#include "WaveletComDec.h"
using namespace std;

void CompressDecompress(const char *file_input, char *file_output, int level, int value)
{
    int i, j, k;
    int file_addr = 0;
    int file_size = 0;
    int lon = 0;
    int wid = 0;
    int hei = 0;
    int temp_ex_lon = 0;
    int temp_ex_wid = 0;
    int temp_ex_hei = 0;
    int ex_lon = 0;
    int ex_wid = 0;
    int ex_hei = 0;
    int temp;
    int temp_level = level;
    double *temp_file = NULL;
    double ***data_input = NULL;
    
    if (!FileLoad(file_input, file_addr, file_size))
    {
        cout << "Open file error" << endl;
        return ;
    }
    
    FileType(file_input, lon, wid, hei);
    
    temp_file = (double *)file_addr;
    
    data_input = SetData(data_input, lon, wid, hei, ex_lon, ex_wid, ex_hei);
    
    temp_ex_lon = ex_lon;
    temp_ex_wid = ex_wid;
    temp_ex_hei = ex_hei;
    
    for (i = 0; i < hei; i++)
    {
        for (j = 0; j < lon; j++)
        {
            for (k = 0; k < wid; k++)
            {
                temp =  lon * wid * i + wid * j +k;
                data_input[j][k][i] = temp_file[temp];
            }
        }
    }
    
    while (temp_level > 0 && ex_lon > 1 && ex_wid > 1 && ex_hei > 1)
    {
        HaarTransform3D(data_input, ex_lon, ex_wid, ex_hei);
        
        if (ex_lon > 1)
            ex_lon = ex_lon / 2;
        if (ex_wid > 1)
            ex_wid = ex_wid / 2;
        if (ex_hei > 1)
            ex_hei = ex_hei / 2;
        
        temp_level--;
    }
    
    DataQuantize3D(data_input, temp_ex_lon, temp_ex_wid, temp_ex_hei, value);
    
    while (temp_level < level && ex_lon > 1 && ex_wid > 1 && ex_hei > 1)
    {
        InverseHaarTransform3D(data_input, ex_lon, ex_wid, ex_hei);
        
        if (ex_lon > 1)
            ex_lon = ex_lon * 2;
        if (ex_wid > 1)
            ex_wid = ex_wid * 2;
        if (ex_hei > 1)
            ex_hei = ex_hei * 2;
        
        temp_level++;
    }
    
    for (i = 0; i < hei; i++)
    {
        for (j = 0; j < lon; j++)
        {
            for (k =0; k < wid; k++)
            {
                temp = lon * wid * i + wid * j +k;
                temp_file[temp] = data_input[j][k][i];
            }
        }
    }
    
    if (!FileSave(temp_file, file_output, temp + 1))
    {
        cout << "Error save file" << endl;
    }
    
    delete [] temp_file;
    delete [] data_input;
}
