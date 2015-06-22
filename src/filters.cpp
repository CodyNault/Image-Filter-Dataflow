#include <filters.hpp>
#include <cstdlib>
#include <stdio.h>
#include <logging.hpp>

/**
 * Reduces image legth and width by half
 */
void Shrinker::Execute()
{
	OneInputCheck();
	Pixel *data = inputImg1->GetBuffer();
	int oldWidth = inputImg1->GetWidth();
	int newWidth = oldWidth / 2;
	int newHeight = inputImg1->GetHeight() / 2;
	Pixel *smallerData = new Pixel[ newWidth * newHeight];
	for(int i = 0; i < newHeight; i++)
	{
		for(int j = 0; j < newWidth; j++)
		{
			smallerData[i * newWidth + j] = data[2* i * oldWidth + 2 * j];
		}
	}
	outputImg.ResetSize(newWidth,newHeight);
	outputImg.SetBuffer(smallerData);
}

/**
 * Takes two images of same height and combines them side by side as a single
 * image. Throws exception if images are not the same height.
 */
void LRConcat::Execute()
{
	TwoInputCheck();
	if(inputImg1->GetHeight() != inputImg2->GetHeight()){
		char msg[1028];
		sprintf(msg, "LRConcat: heights must match: %d, %d", inputImg1->GetHeight(), inputImg2->GetHeight());
		DataFlowException except("LRConcat", msg);
		throw except;
	}
	int leftWidth = inputImg1->GetWidth();
	int rightWidth = inputImg2->GetWidth();
	int newWidth = leftWidth + rightWidth;
	int newHeight = inputImg1->GetHeight();
	Pixel *leftBuffer = inputImg1->GetBuffer();
	Pixel *rightBuffer = inputImg2->GetBuffer();
	Pixel *combinedBuffer = new Pixel[ newWidth * newHeight];
	for(int i = 0; i < newHeight; i++)
	{
		for(int j = 0; j < newWidth; j++)
		{
			if( j < leftWidth)
			{
				combinedBuffer[i*newWidth + j] = leftBuffer[i * leftWidth + j];	
			}else{
				combinedBuffer[i*newWidth + j] = rightBuffer[i * rightWidth + j - leftWidth];	
			}
		}
	}
	outputImg.ResetSize(newWidth, newHeight);
	outputImg.SetBuffer(combinedBuffer);
}

/**
 * Takes two images of same width and combines them on top of one another 
 * as a single image. Throws exception if images are not the same height.
 */
void TBConcat::Execute()
{
	TwoInputCheck();
	if(inputImg1->GetWidth() != inputImg2->GetWidth()){
		char msg[1028];
		sprintf(msg, "TBConcat: widths must match: %d, %d", inputImg1->GetWidth(), inputImg2->GetWidth());
		DataFlowException except("TBConcat", msg);
		throw except;
	}
	int topHeight = inputImg1->GetHeight();
	int bottomHeight = inputImg2->GetHeight();
	int newWidth = inputImg1->GetWidth();
	int newHeight = topHeight + bottomHeight;
	Pixel *topBuffer = inputImg1->GetBuffer();
	Pixel *bottomBuffer = inputImg2->GetBuffer();
	Pixel *combinedBuffer = new Pixel[ newWidth * newHeight];
	for(int i = 0; i < newHeight; i++)
	{
		for(int j = 0; j < newWidth; j++)
		{
			if( i < topHeight)
			{
				combinedBuffer[i*newWidth + j] = topBuffer[i * newWidth + j];	
			}else{
				combinedBuffer[i*newWidth + j] = bottomBuffer[(i - topHeight) * newWidth + j];	
			}
		}
	}
	outputImg.ResetSize(newWidth, newHeight);
	outputImg.SetBuffer(combinedBuffer);
}

/**
 * Constructor for Blender. Initializes factor value to 0.
 */
Blender::Blender()
{
	this->factor = 0;
}

/**
 * Settor for Blender's factor.
 */
void Blender::SetFactor(float factor)
{
	this->factor = factor;
}

/**
 * Given two inputs with the same height and width, This execution
 * combines the two images into one by taking input1 color channels 
 * multipled by the factor, and input2 color channels and multiplying
 * them by (1 - factor).
 */
void Blender::Execute()
{
	TwoInputCheck();
	if(this->factor < 0 || this->factor > 1){
		char msg[1028];
		sprintf(msg, "Invalid factor for Blender: %f", this->factor);
		DataFlowException except("Blender", msg);
		throw except;
	}
	if(inputImg1->GetWidth() != inputImg2->GetWidth()){
		char msg[1028];
		sprintf(msg, "Blender: widths must match: %d, %d", inputImg1->GetWidth(), inputImg2->GetWidth());
		DataFlowException except("Blender", msg);
		throw except;
	}
	if(inputImg1->GetHeight() != inputImg2->GetHeight()){

		char msg[1028];
		sprintf(msg, "Blender: heights must match: %d, %d", inputImg1->GetHeight(), inputImg2->GetHeight());
		DataFlowException except("Blender", msg);
		throw except;
	}
	int width = inputImg1->GetWidth();
	int height = inputImg1->GetHeight();
	Pixel *buffer1 = inputImg1->GetBuffer();
	Pixel *buffer2 = inputImg2->GetBuffer();
	Pixel *combinedBuffer = new Pixel[ width * height];
	float factor2 = 1.0 - factor;
	float red = 0.0, green = 0.0, blue = 0.0;
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			red = buffer1[i * width + j].red * factor + buffer2[ i * width + j].red * factor2; 
			combinedBuffer[i * width + j].red = static_cast<int>(red);
			green = buffer1[i * width + j].green * factor + buffer2[ i * width + j].green * factor2; 
			combinedBuffer[i * width + j].green = static_cast<int>(green);
			blue = buffer1[i * width + j].blue * factor + buffer2[ i * width + j].blue * factor2; 
			combinedBuffer[i * width + j].blue = static_cast<int>(blue);
		}
	}
	outputImg.ResetSize(width, height);
	outputImg.SetBuffer(combinedBuffer);
}

/**
 * Performs crop according to values given in constructor
 */
void Crop::Execute(void)
{
    OneInputCheck();
    if (Istart < 0 || Istop < 0 || Jstart < 0 || Jstop < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: uninitialized region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istart >= inputImg1->GetWidth() || Istop >= inputImg1->GetWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image width", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Jstart >= inputImg1->GetHeight() || Jstop >= inputImg1->GetHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image height", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istop < Istart || Jstop < Jstart)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }

    int height = Jstop-Jstart+1;
    int width  = Istop-Istart+1;
    int inputWidth = inputImg1->GetWidth();
    Pixel *outBuffer = new Pixel[width * height];
    Pixel *inBuffer1 = inputImg1->GetBuffer();
    for (int i = Istart ; i <= Istop ; i++)
        for (int j = Jstart ; j <= Jstop ; j++)
        {
            int idx1 = j*inputWidth+i;
            int idx  = (j-Jstart)*width+(i-Istart);
            outBuffer[idx].red   = inBuffer1[idx1].red;
            outBuffer[idx].green = inBuffer1[idx1].green;
            outBuffer[idx].blue = inBuffer1[idx1].blue;
        }
    outputImg.ResetSize(width, height);
    outputImg.SetBuffer(outBuffer);
}

/**
 * Transposes image from input 1. 
 */
void Transpose::Execute()
{
	OneInputCheck();
        int oldHeight = inputImg1->GetHeight();
        int oldWidth = inputImg1->GetWidth();
        int newHeight = oldWidth;
        int newWidth = oldHeight;
	Pixel *outBuffer = new Pixel[newHeight * newWidth];
	Pixel *inBuffer1 = inputImg1->GetBuffer();
	for (int h = 0 ; h < oldHeight ; h++){
        	for (int w = 0 ; w < oldWidth ; w++){
			outBuffer[w * oldHeight + h] = inBuffer1[h * oldWidth + w];
                }
        }
        outputImg.ResetSize(newWidth, newHeight);
        outputImg.SetBuffer(outBuffer);
}

/**
 * Inverts colors by replacing each channel with 255 current color value
 */
void Invert::Execute()
{
        OneInputCheck();
        int height = inputImg1->GetHeight();
        int width = inputImg1->GetWidth();
        Pixel *outBuffer = new Pixel[height * width];
        Pixel *inBuffer1 = inputImg1->GetBuffer();
        for (int h = 0 ; h < height ; h++){
                for (int w = 0 ; w < width ; w++){
                        outBuffer[h * width + w].red = 255 - inBuffer1[h * width + w].red;
                        outBuffer[h * width + w].green = 255 - inBuffer1[h * width + w].green;
                        outBuffer[h * width + w].blue = 255 - inBuffer1[h * width + w].blue;
                }
        }
        outputImg.ResetSize(width, height);
        outputImg.SetBuffer(outBuffer);
}

/**
 * Combines two images in checkerboard pattern
 */
void Checkerboard::Execute()
{
	TwoInputCheck();
        if(inputImg1->GetWidth() != inputImg2->GetWidth()){
                char msg[1028];
                sprintf(msg, "Checkerboard: widths must match: %d, %d", inputImg1->GetWidth(), inputImg2->GetWidth());
                DataFlowException except("Blender", msg);
                throw except;
        }
        if(inputImg1->GetHeight() != inputImg2->GetHeight()){

                char msg[1028];
                sprintf(msg, "Checkerboard: heights must match: %d, %d", inputImg1->GetHeight(), inputImg2->GetHeight());
                DataFlowException except("Blender", msg);
                throw except;
        }
	int width = inputImg1->GetWidth();
        int height = inputImg1->GetHeight();
        Pixel *buffer1 = inputImg1->GetBuffer();
        Pixel *buffer2 = inputImg2->GetBuffer();
        Pixel *combinedBuffer = new Pixel[ width * height];
        float red = 0.0, green = 0.0, blue = 0.0;
        for(int i = 0; i < height; i++)
        {
                for(int j = 0; j < width; j++)
                {
			if((( i / 10 + j / 10) % 2 == 0)){
				combinedBuffer[i * width + j] = buffer1[i * width + j];
			}else{
				combinedBuffer[i * width + j] = buffer2[i * width + j];
			}
                }
        }
        outputImg.ResetSize(width, height);
        outputImg.SetBuffer(combinedBuffer);

}

/**
 * Constructor for a source that outputs a solid color
 */
Color::Color(int w, int h, int r, int g, int b)
{
	red = r;
	green = g;
	blue = b;
	width = w;
	height = h;
}

/**
 *Generates solid color image
 */
void Color::Execute()
{
	int length = width * height;
	Pixel *data = new Pixel[length];
	for(int i = 0; i < length; i++){
		data[i].red = red;
		data[i].green = green;
		data[i].blue = blue;
	}
	outputImg.ResetSize(width,height);
        outputImg.SetBuffer(data);
}

/**
 * Update triggers execution with logging and error handeling
 */
void Color::Update()
{
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

/**
 * This method takes the image from the input and generates a 
 * checksum file based on the filenmae provided as a parameter.
 */
void CheckSum::OutputCheckSum()
{
	unsigned char redSum = 0;
	unsigned char greenSum = 0;
	unsigned char blueSum = 0;
        OneInputCheck();
	int numOfPixels = inputImg1->GetWidth() * inputImg1->GetHeight();
	Pixel *inBuffer1 = inputImg1->GetBuffer();

	for(int i = 0; i < numOfPixels; i++){
		redSum = (unsigned char) (redSum + inBuffer1[i].red);
		greenSum =(unsigned char) (greenSum + inBuffer1[i].green);
		blueSum = (unsigned char) (blueSum + inBuffer1[i].blue);
	}
        FILE *f_out;
        f_out = fopen("log/checksum", "w+");
        if(f_out == NULL){
        	f_out = fopen("../log/checksum", "w+");
        	if(f_out == NULL){
                	fprintf(stderr, "Failure opening output file");
                	exit(EXIT_FAILURE);
		}
        }
        fprintf( f_out, "CHECKSUM: %d, %d, %d\n", redSum, greenSum, blueSum);
        fclose(f_out);
}
