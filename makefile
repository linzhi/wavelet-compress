Wavelet.o:main.o File.o HaarWaveletTransform.o Quantize.o VerificationResult.o WaveletComDec.o WaveletCompress.o WaveletDecompress.o
		g++ -o Wavelet main.o File.o HaarWaveletTransform.o Quantize.o VerificationResult.o WaveletComDec.o WaveletCompress.o WaveletDecompress.o

main.o:main.cpp WaveletCompress.h WaveletDecompress.h WaveletComDec.h
		g++ -c main.cpp

File.o:File.cpp File.h
		g++ -c File.cpp

HaarWaveletTransform.o:HaarWaveletTransform.cpp HaarWaveletTransform.h
		g++ -c HaarWaveletTransform.cpp

Quantize.o:Quantize.cpp Quantize.h
		g++ -c Quantize.cpp

VerificationResult.o:VerificationResult.cpp VerificationResult.h
		g++ -c VerificationResult.cpp

WaveletComDec.o:WaveletComDec.cpp WaveletComDec.h File.h Quantize.h HaarWaveletTransform.h VerificationResult.h
		g++ -c WaveletComDec.cpp 

WaveletCompress.o:WaveletCompress.cpp WaveletCompress.h File.h Quantize.h HaarWaveletTransform.h
		g++ -c WaveletCompress.cpp

WaveletDecompress.o:WaveletDecompress.cpp WaveletDecompress.h
		g++ -c WaveletDecompress.cpp

.PHONY:clean
clean:
	-rm *.o
