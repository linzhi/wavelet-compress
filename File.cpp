/*
 *	FILE: File.c
 *	Date: 2012-7-15
 *	Author: linzhi
 */

#include <iostream> 
#include <fstream>
#include <cstring>
#include "File.h"

using namespace std;

const int NUMBER_OF_BITS = 8 * sizeof(int);
const int RIGHT_BIT = 1;
const int LEFT_BIT = 1 << (NUMBER_OF_BITS - 1);

int FileLoad(const char *file_input, int &file_addr, int &file_size)
{
    fstream file;
    int i;
    int size;
    
    file.open(file_input, ios::in | ios::binary);
    
    if (!file.is_open()) 
		return 0;

    //get the file size
    file.seekg(0, ios::end);
    size = file.tellg();
    file.seekg(ios::beg);	
    
    unsigned char *temp_data = new unsigned char[size];
    file.read((char *)temp_data, size);
	file.close();
    
    double *file_buf = new double[size];
    
    for (i = 0; i < size; i++)
    {
        file_buf[i] = temp_data[i];
    }
    
    file_size = size;
    file_addr = (int)file_buf;
    
    delete [] temp_data;
    
    return 1;
}

void FileType(const char *file_input, int &lon, int &wid, int &hei)
{
    const char *file_type[] ={"bonsai", "fuel", "BostonTeapot", "engine", "foot", "fueld2",
										"tooth", "fish", "fishd2", "CT-chest", "lobster", "skull",
										"leg", "silicium", "nucleon", "colon", "colond2"};
    if (strcmp(file_input, file_type[0]) == 0)
    {
        lon = 256;
        wid = 256;
        hei = 256;
    }
    
    if (strcmp(file_input, file_type[1]) == 0)
    {
        lon = 64;
        wid = 64;
        hei = 64;
    }
    
    if (strcmp(file_input, file_type[2]) == 0)
    {
        lon = 256;
        wid = 256;
        hei = 178;
    }
    
    if (strcmp(file_input, file_type[3]) == 0)
    {
        lon = 256;
        wid = 256;
        hei = 128;
    }
    
    if (strcmp(file_input, file_type[4]) == 0)
    {
        lon = 256;
        wid = 256;
        hei = 256;
    }
    
    if (strcmp(file_input, file_type[5]) == 0)
    {
        lon = 32;
        wid = 32;
        hei = 32;
    }
    
    if (strcmp(file_input, file_type[6]) == 0)
    {
        lon = 256;
        wid = 256;
        hei = 161;
    }
    
    if (strcmp(file_input, file_type[7]) == 0)
    {
        lon = 256;
        wid = 256;
        hei = 152;
    }
    
    if (strcmp(file_input, file_type[8]) == 0)
    {
        lon = 128;
        wid = 128;
        hei = 256;
    }
    
    if (strcmp(file_input, file_type[9]) == 0)
    {
        lon = 384;
        wid = 384;
        hei = 240;
    }
    
    if (strcmp(file_input, file_type[10]) == 0)
    {
        lon = 301;
        wid = 324;
        hei = 56;
    }
    
    if (strcmp(file_input, file_type[11]) == 0)
    {
        lon = 256;
        wid = 256;
        hei = 256;
    
    if (strcmp(file_input, file_type[12]) == 0)
    {
        lon = 341;
        wid = 341;
        hei = 93;
    }
    
    if (strcmp(file_input, file_type[13]) == 0)
    {
        lon = 98;
        wid = 34;
        hei = 34;
    }
    
    if (strcmp(file_input, file_type[14]) == 0)
    {
        lon = 41;
        wid = 41;
        hei = 41;
    }
    
    if (strcmp(file_input, file_type[15]) == 0)
    {
        lon = 512;
        wid = 512;
        hei = 512;
    }
    
    if (strcmp(file_input, file_type[16]) == 0)
    {
        lon = 256;
        wid = 256;
        hei  = 221;
    }
}

int FileSave(double *data_input, char *file_output, int file_size)
{
    int i;
    unsigned char *mem = new unsigned char[file_size];
    unsigned char *file_buf = new unsigned char[file_size];
    
    for (i = 0; i < file_size; i++)
    {
        if (data_input[i] > 255.0)
            data_input[i] = 255.0;
        
        if (data_input[i] < 0.0)
            data_input[i] = 0.0;
        
        file_buf[i] = (unsigned char)data_input[i];
    }
    
    memcpy(mem, file_buf, file_size);
    
    ofstream file_save(file_output, ios::out | ios::binary);
    
    if(!file_save.is_open())
        return 0;
    
    file_save.write((char *)mem, file_size);
    file_save.close();
    
    delete [] mem;
    delete [] file_buf;
    
    return 1;
}

int GetClosestPowerOfTwo(int integer)
{
    int high_bit = 0;
    int bits_counter = 0;
    int mask = 1;
    int i;
    
    //if it isn't powers of two
    if (integer & (integer - 1))
    {
        for (i = 0; i < NUMBER_OF_BITS; i++)
        {
            if ((integer & mask) != 0)
            {
                high_bit = i;
                ++bits_counter;
            }
            mask <<= 1;
        }
        
        return 1 << (high_bit + 1);
    }
    else if (integer == 1)
    {
        return integer + 1;
    }
    else
    {
        return integer;
    }
}

double ***SetData(double ***data_input, int &lon, int &wid, int &hei, int &ex_lon, int &ex_wid, int &ex_hei)
{
    int i, j, k;
    ex_lon = GetClosestPowerOfTwo(lon);
    ex_wid = GetClosestPowerOfTwo(wid);
    ex_hei = GetClosestPowerOfTwo(hei);
    
    //create a three-dimensional pointer then allocate space to store data
    //data_input[i] standard for the i long
    //data_input[i][j] standard for the i layer j width
    //data_input[i][j][k] standard for the i long j width k layer
    data_input = new double **[ex_lon];
    
    for (i = 0; i < ex_lon; i++)
    {
        data_input[i] = new double *[ex_wid];
    }
    
    for (i = 0; i < ex_lon; i++)
    {
        for (j = 0; j < ex_wid; j++)
        {
            data_input[i][j] = new double[ex_hei];
        }
    }
    
    for (i = 0; i < ex_hei; i++)
    {
        for (j = 0; j < ex_lon; j++)
        {
            for (k = 0; k < ex_wid; k++)
            {
                data_input[j][k][i] = 0.0;
            }
        }
    }

    return data_input;
}
