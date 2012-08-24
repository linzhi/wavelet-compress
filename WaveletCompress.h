#ifndef WAVELET_COMPRESS_H
#define WAVELET_COMPRESS_H

#include "File.h"
#include "Quantize.h"
#include "HaarWaveletTransform.h"

void Compress(const char *file_input, char *file_output, int level, int value);
	
#endif 
