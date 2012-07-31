#include <iostream>
#include <cmath>
#include "HaarWaveletTransform.h"

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
 * Inverse Transform for once using 1D haar wavelet
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
    
    //haar transform for height
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

    //haar transform for width
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
 * Inverse Transform for once using 2D haar wavelet
 */
void InverseHaarTransform2D(double **data_input, int hei, int wid)
{
    int i, j;
    double *temp_hei = new double[hei];
    double *temp_wid = new double[wid];
    
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
    double **temp_lon_wid = NULL;
    double **temp_hei_wid = NULL;
    double **temp_hei_lon = NULL;
    
    temp_lon_wid = new double *[lon];
    for (i = 0; i < lon; i++)
    {
        temp_lon_wid[i] = new double[wid];
    }
    
    temp_hei_wid = new double *[hei];
    for (j = 0; j < hei; j++)
    {
        temp_hei_wid[j] = new double[wid];
    }
    
    temp_hei_lon = new double *[hei];
    for (k = 0; k < hei; k++)
    {
        temp_hei_lon[k] = new double[lon];
    }
    
    //haar transform for long and width
    if ((lon > 1) && (wid > 1))
    {
        for (i = 0; i < hei; i++)
        {
            for (j = 0; j < lon; j++)
            {
                for (k = 0; k < wid; k++)
                {
                    temp_lon_wid[j][k] = data_input[j][k][i];
                }
            }
            
            HaarTransform2D(temp_lon_wid, lon, wid);
            
            for (j = 0; j < lon; j++)
            {
                for (k = 0; k < wid; k++)
                {
                    data_input[j][k][i] = temp_lon_wid[j][k];
                }
            }
        }
    }
    
    //haar transfomr for width and height
    if ((hei > 1) && (wid > 1))
    {
        for (i = 0; i < lon; i++)
        {
            for (j = 0; j < hei; j++)
            {
                for (k = 0; k < wid; k++)
                {
                    temp_hei_wid[j][k] = data_input[i][k][j];
                }
            }
            
            HaarTransform2D(temp_hei_wid, hei, wid);
            
            for (j = 0; j < hei; j++)
			{
                for (k = 0; k < wid; k++)
                {
                    data_input[i][k][j] = temp_hei_wid[j][k];
                }
            }
        }
    }
    
    //haar transform for height and long
    if ((hei > 1) && (lon > 1))
	{
        for (i = 0; i < wid; i++)
        {
            for (j = 0; j < hei; j++)
            {
                for (k = 0; k < lon; k++)
                {
                    temp_hei_lon[j][k] = data_input[k][i][j];
				}
            }
            
            HaarTransform2D(temp_hei_lon, hei, lon);
            
            for (j = 0; j < hei; j++)
            {
                for (k = 0; k < lon; k++)
                {
                    data_input[k][i][j] = temp_hei_lon[j][k];
                }
            }
        }
    }
    
    delete [] temp_lon_wid;
    delete [] temp_hei_wid;
    delete [] temp_hei_lon;
}

/*
 * Inverse Transform for once using 3D haar wavelet
 */
void InverseHaarTransform3D(double ***data_input, int lon, int wid, int hei)
{
    //in the data_input[i][j][k] k is standard for height, j is standard for long
    // and i is standard for width
    int i, j, k;
    double **temp_lon_wid;
    double **temp_hei_wid;
    double **temp_hei_lon;
    
    temp_lon_wid = new double *[lon];
    for (i = 0; i < lon; i++)
    {
        temp_lon_wid[i] = new double[wid];
    }
    
    temp_hei_wid = new double *[hei];
    for (j = 0; j < hei; j++)
    {
        temp_hei_wid[j] = new double[wid];
    }
    
    temp_hei_lon = new double *[hei];
    for (k = 0; k < hei; k++)
    {
        temp_hei_lon[k] = new double[lon];
    }
    
    //haar transform for long and width
    if ((lon > 1) && (wid > 1))
    {
        for (i = 0; i < hei; i++)
        {
            for (j = 0; j < lon; j++)
            {
                for (k = 0; k < wid; k++)
                {
                    temp_lon_wid[j][k] = data_input[j][k][i];
                }
            }
            
            InverseHaarTransform2D(temp_lon_wid, lon, wid);
            
            for (j = 0; j < lon; j++)
            {
                for (k = 0; k < wid; k++)
                {
                    data_input[j][k][i] = temp_lon_wid[j][k];
                }
            }
        }
    }
    
    //haar transfomr for width and height
    if ((hei > 1) && (wid > 1))
    {
        for (i = 0; i < lon; i++)
        {
            for (j = 0; j < hei; j++)
            {
                for (k = 0; k < wid; k++)
                {
                    temp_hei_wid[j][k] = data_input[i][k][j];
                }
            }
            
            InverseHaarTransform2D(temp_hei_wid, hei, wid);
            
            for (j = 0; j < hei; j++)
            {
                for (k = 0; k < wid; k++)
                {
                    data_input[i][k][j] = temp_hei_wid[j][k];
                }
            }
        }
    }
    
    //haar transform for height and long
    if ((hei > 1) && (lon > 1))
    {
        for (i = 0; i < wid; i++)
        {
            for (j = 0; j < hei; j++)
            {
                for (k = 0; k < lon; k++)
                {
                    temp_hei_lon[j][k] = data_input[k][i][j];
                }
            }
            
            InverseHaarTransform2D(temp_hei_lon, hei, lon);

			for (j = 0; j < hei; j++)
            {
                for (k = 0; k < lon; k++)
                {
                    data_input[k][i][j] = temp_hei_lon[j][k];
                }
            }
        }
    }
    
    delete [] temp_lon_wid;
    delete [] temp_hei_wid;
    delete [] temp_hei_lon;
}
