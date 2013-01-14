#include <iostream>
#include <cmath>
#include "HaarWaveletTransform.h"

using namespace std;

const double SQRT2 = sqrt(2.0);

/*
 * Transform for once using 1D haar wavelet
 */

void HaarTransform1D(double *data_input, int size)
{
    double *temp_data = new double[size];
    int temp_size = size;
    int i;
    
    temp_size = temp_size / 2;
    
    for (i = 0; i < temp_size; i++)
    {
        temp_data[i] = (data_input[2 * i] + data_input[(2 * i) + 1]) / SQRT2;
        temp_data[temp_size + i] = (data_input[2 * i] - data_input[(2 * i) + 1]) / SQRT2;
    }
    
    for (i = 0; i < size; i++)
    {
        data_input[i] = temp_data[i];
    }
    
    delete [] temp_data;
}

/*
 * Inverse transform for once using 1D haar wavelet
 */

void InverseHaarTransform1D(double *data_input, int size)
{
    double *temp_data = new double[size];
    int temp_size = size;
    int i;
    
    temp_size = temp_size / 2;
    
    for (i = 0; i < temp_size; i++)
    {
        temp_data[2 * i] = (data_input[i] + data_input[temp_size + i]) / SQRT2;
        temp_data[2 * i + 1] = (data_input[i] - data_input[temp_size + i]) / SQRT2;
    }
    
    for (i = 0; i < size; i++)
    {
        data_input[i] = temp_data[i];
    }
    
    delete [] temp_data;
}

/*
 * Transform for once using 2D haar wavelet
 */

void HaarTransform2D(double **data_input, int hei, int wid)
{
    int i, j;
    double *temp_hei = new double[hei];
    double *temp_wid = new double[wid];
    
    //haar transform for width
    if (wid > 1)
    {
        for (i = 0; i < hei; i++)
        {
            for (j = 0; j < wid; j++)
                temp_wid[j] = data_input[i][j];
            
            HaarTransform1D(temp_wid, wid);
            
            for (j = 0; j < wid; j++)
                data_input[i][j] = temp_wid[j];
        }
    }
    
    //haar transform for height
    if (hei > 1)
    {
        for (i = 0; i < wid; i++)
        {
            for (j = 0; j < hei; j++)
                temp_hei[j] = data_input[j][i];
            
            HaarTransform1D(temp_hei, hei);
            
            for (j = 0; j < hei; j++)
                data_input[j][i] = temp_hei[j];
        }
    }
    
    delete [] temp_hei;
    delete [] temp_wid;
}

/*
 * Inverse transform for once using 2D haar wavelet
 */

void InverseHaarTransform2D(double **data_input, int hei, int wid)
{
    int i, j;
    double *temp_hei = new double[hei];
    double *temp_wid = new double[wid];
    
    //inverse haar transform for height
    if (hei > 1)
    {
        for (i = 0; i < wid; i++)
        {
            for (j = 0; j < hei; j++)
                temp_hei[j] = data_input[j][i];
            
            InverseHaarTransform1D(temp_hei, hei);

            for (j = 0; j < hei; j++)
                data_input[j][i] = temp_hei[j];
        }
    }
    
    // inverse haar transform for width
    if (wid > 1)
    {
        for (i = 0; i < hei; i++)
        {
            for (j = 0; j < wid; j++)
                temp_wid[j] = data_input[i][j];
            
            InverseHaarTransform1D(temp_wid, wid);
            
            for (j = 0; j < wid; j++)
                data_input[i][j] = temp_wid[j];
        }
    }
    
    delete [] temp_hei;
    delete [] temp_wid;
}

/*
 * Transform for once using 3D haar wavelet
 */

void HaarTransform3D(double ***data_input, int lon, int wid, int hei)
{
    //in the data_input[i][j][k] k is standard for height, j is standard for long
	// and i is standard for width
    int i, j, k;
    double *temp_lon = NULL;
    double *temp_wid = NULL;
    double *temp_hei = NULL;
    
    temp_lon = new double [lon];
    temp_wid = new double [wid];
    temp_hei = new double [hei];
    
    //haar transform for long 
    if ((wid > 1) && (hei > 1))
    {
        for (i = 0; i < hei; i++)
        {
            for (j = 0; j < wid; j++)
            {
                for (k = 0; k < lon; k++)
                {
                    temp_lon[k] = data_input[k][j][i];
                }
                
                HaarTransform1D(temp_lon, lon);
                
                for (k = 0; k < lon; k++)
                {
                    data_input[k][j][i] = temp_lon[k];
                }
            }
        }
    }
    
    //haar transform for width
    if ((lon > 1) && (hei > 1))
    {
        for (i = 0; i < hei; i++)
        {
            for (j = 0; j < lon; j++)
            {
                for (k = 0; k < wid; k++)
                {
                    temp_wid[k] = data_input[j][k][i];
                }
                
                HaarTransform1D(temp_wid, wid);
                
                for (k = 0; k < wid; k++)
                {
                    data_input[j][k][i] = temp_wid[k];
                }
            }
        }
    }
    
    //haar transform for height
    if ((lon > 1) && (wid > 1))
    {
        for (i = 0; i < lon; i++)
        {
            for (j = 0; j < wid; j++)
            {
                for (k = 0; k < hei; k++)
                {
                    temp_hei[k] = data_input[i][j][k];
                }
                
                HaarTransform1D(temp_hei, hei);
                
                for (k = 0; k < hei; k++)
                {
                    data_input[i][j][k] = temp_hei[k];
                }
            }
        }
    }
    
    delete [] temp_lon;
    delete [] temp_wid;
    delete [] temp_hei;
}

/*
 * Inverse transform for once using 3D haar wavelet
 */

void  InverseHaarTransform3D(double ***data_input, int lon, int wid, int hei)
{
    //in the data_input[i][j][k] k is standard for height, j is standard for long
    // and i is standard for width
    int i, j, k;
    double *temp_lon = NULL;
    double *temp_wid = NULL;
    double *temp_hei = NULL;
    
    temp_lon = new double [lon];
    temp_wid = new double [wid];
    temp_hei = new double [hei];
    
    //haar transform for height
    if ((lon > 1) && (wid > 1))
    {
        for (i = 0; i < lon; i++)
        {
            for (j = 0; j < wid; j++)
            {
                for (k = 0; k < hei; k++)
                {
                    temp_hei[k] = data_input[i][j][k];
                }
                
                InverseHaarTransform1D(temp_hei, hei);
                
                for (k = 0; k < hei; k++)
                {
                    data_input[i][j][k] = temp_hei[k];
                }
            }
        }
    }
    
    //haar transfomr for width
    if ((lon > 1) && (hei > 1))
    {
        for (i = 0; i < hei; i++)
        {
            for (j = 0; j < lon; j++)
            {
                for (k = 0; k < wid; k++)
                {
                    temp_wid[k] = data_input[j][k][i];
                }
                
                InverseHaarTransform1D(temp_wid, wid);
                
                for (k = 0; k < wid; k++)
                {
                    data_input[j][k][i] = temp_wid[k];
                }
            }
        }
    }
    
    //haar transform for long
    if ((wid > 1) && (hei > 1))
    {
        for (i = 0; i < hei; i++)
        {
            for (j = 0; j < wid; j++)
            {
                for (k = 0; k < lon; k++)
                {
                    temp_lon[k] = data_input[k][j][i];
                }
                
                InverseHaarTransform1D(temp_lon, lon);
                
                for (k = 0; k < lon; k++)
                {
                    data_input[k][j][i] = temp_lon[k];
                }
            }
        }
    }
    
    delete [] temp_lon;
    delete [] temp_wid;
    delete [] temp_hei;
}
