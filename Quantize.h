/*
 *	FILE：quantize.h	
 *	量化处理：采用固定阈值法，设置一个固定值value
 *	算法描述：小于value的值全部置0，别的保持不变
 *
 */

#ifndef QUANTIZE_H
#define QUANTIZE_H

//quantize the 2D data which is under value to 0
void DataQuantize2D(double **data_input, int hei, int wid, int value);

//quantize the 3D data which is under value to 0
void DataQuantize3D(double ***data_input, int lon, int wid, int hei, int value);

#endif