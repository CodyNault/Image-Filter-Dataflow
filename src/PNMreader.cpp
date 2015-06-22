#include <PNMreader.hpp>
#include <string.h>
#include <cstdlib>
#include <stdio.h>
#include <logging.hpp>

/**
 * PNMreader constructor saves filename
 */
PNMreader::PNMreader(const char *filename)
{
	this->filename = new char[strlen(filename) + 1];
	strcpy(this->filename, filename);
}

/**
 * PNMreader destructor frees filename memory
 */
PNMreader::~PNMreader()
{
	delete[] this->filename;
}

/**
 * Reads contents of PNM file and generates Image object as output
 */
void PNMreader::Execute()
{
	FILE *f_in = NULL;
	char magicNum[3];
	int i = 0;
	int width = 0;
	int height = 0;
	int maxval = 0;
	unsigned char val[1];

	f_in = fopen(filename, "rb");
	if(f_in == NULL){
		fprintf(stderr, "Failure opening input file");
		exit(EXIT_FAILURE);
	}
	fscanf(f_in,"%s\n%d %d\n%d\n",magicNum,&width,&height,&maxval);

	Pixel *data = new Pixel[width * height];
	fread(data, sizeof(Pixel), width * height , f_in);
	fclose(f_in);
	outputImg.ResetSize(width,height);
	outputImg.SetBuffer(data);
}

/**
 * Performs execute with logging and exception handeling
 */
void PNMreader::Update(){
        char msg[128];
        sprintf(msg, "%s: about to execute", SourceName());
        Logger::LogEvent(msg);
        try{
                Execute();
        }catch(DataFlowException& except){
                sprintf(msg, "Throwing exception: (%s): %s", SourceName(), except.what());
                Logger::LogEvent(msg);
                throw except;
        }
        sprintf(msg, "%s: done executing", SourceName());
        Logger::LogEvent(msg);
}
