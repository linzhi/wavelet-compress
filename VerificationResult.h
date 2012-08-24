#ifndef VERIFICATION_RESULT_H
#define VERIFICATION_RESULT_H

double MeanSquaredError(double *file_in, double * file_out, int &file_size);

double PeakSignalToNoiseRatio(double mse);

#endif
