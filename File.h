/*
 * FILE: File.h
 * Author: linzhi
 * Date: 2012-7-30
 */

#ifndef FILE_H
#define FILE_H

//load file and expand the data from unsigned char to double
int FileLoad(const char *file_input, int &file_addr, int &file_size);

//check the file's basic information
void FileType(const char *file_input, int &lon, int &wid, int &hei);

//If long width or height isn't powers of two function will calculate closest power of two
//and then fill empty space with 0
int GetClosestPowerOfTwo(int integer);

//fill the 3D data's extend space to zero, return a 3D data which is filled with zero
double ***SetData(double ***data_input, int &lon, int &wid, int &hei, int &ex_lon, int &ex_wid, int &ex_hei);

//save the compress result
int FileSave(double *data_input, char *file_output, int file_size);

#endif
