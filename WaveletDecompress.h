/*
 *	解压缩保存于硬盘上的压缩文件
 *	1.解码（依据之前的编码算法）
 *	2.逆小波变换（依据前面的小波变换算法）
 */

#ifndef WAVELET_DECOMPRESS_H
#define WAVELET_DECOMPRESS_H

void Decompress(char *file_save, char *file_output);

#endif
