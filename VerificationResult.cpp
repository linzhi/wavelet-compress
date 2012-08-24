#include <iostream>
#include <cmath>
#include "VerificationResult.h"

using namespace std;

double MeanSquaredError(double *file_in, double* file_out, int &file_size)
{
    int i;
    double mse = 0;
    
    for (i = 0; i < file_size; i++)
    {
        mse += pow((file_in[i] - file_out[i]), 2.0);
    }
    
    mse = mse / file_size;
    
    return mse;
}

double PeakSignalToNoiseRatio(double mse)
{
    double psnr = 0;
    
    psnr = 10.0 * log10((255.0 * 255.0) / mse);
    
    return psnr;
}
