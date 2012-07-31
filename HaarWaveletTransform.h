#ifndef HAARWAVELETTRANSFORM_H
#define HAARWAVELETTRANSFORM_H

void HaarTransform1D(double *data_input, int size);

void InverseHaarTransform1D(double *data_input, int size);

void HaarTransform2D(double **data_input, int hei, int wid);

void InverseHaarTransform2D(double **data_input, int hei, int wid);

void HaarTransform3D(double ***data_input, int lon, int wid, int hei);

void InverseHaarTransform3D(double ***data_input, int lon, int wid, int hei);

#endif 
