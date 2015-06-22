#include <PNMwriter.hpp>
#include <cstdlib>
#include <stdio.h>

/**
 * Writes Contents of Image input 1 to file designated in parameter
 */
void PNMwriter::Write(const char *filename)
{
	FILE *f_out;
	f_out = fopen(filename, "w+");
	if(f_out == NULL){
		fprintf(stderr, "Failure opening output file");
		exit(EXIT_FAILURE);
	}
	fprintf( f_out, "P6\n%d %d\n255\n", inputImg1->GetWidth(), inputImg1->GetHeight());
	fwrite (inputImg1->GetBuffer() , sizeof(Pixel), inputImg1->GetHeight() * inputImg1->GetWidth() , f_out);
	fclose(f_out);

}
