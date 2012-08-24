#ifndef WAVELET_COMDEC_H
#define WAVELET_COMDEC_H

#include "File.h"
#include "Quantize.h"
#include "HaarWaveletTransform.h"
#include "VerificationResult.h"

void CompressDecompress(const char *file_input, char *file_output, int level, int value);

#endif
