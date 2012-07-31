#ifndef QUANTIZE_H
#define QUANTIZE_H

//quantize the 2D data which is under value to 0
void DataQuantize2D(double **data_input, int hei, int wid, int value);

//quantize the 3D data which is under value to 0
void DataQuantize3D(double ***data_input, int lon, int wid, int hei, int value);

#endif
