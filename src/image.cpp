#include <image.hpp>
#include <cstdlib>
#include <cstring>
#include <source.hpp>
#include <stdio.h>
/**
 * @author Cody Nault
 * @date 6/5/2015
 * Project 3H
 *
 * This is the main Image class implementation
 */

/**
 * Default Image Constructor
 */
Image::Image(void)
{
	width = 0;
	height = 0;
	data = NULL;
	lastSource = NULL;
}

/**
 * Parametized Image Constructor
 * @param width image width
 * @param height image height
 * @param data Pixel buffer pointer
 */
Image::Image(int width, int height, Pixel *data)
{
	this->width = width;
	this->height = height;
	this->data = data;
	lastSource = NULL;
}

/**
 * Copy Image Constructor
 * @param im reference to image being copied
 */
Image::Image(Image &im)
{
	width = im.GetWidth();
	height = im.GetHeight();
	data = new Pixel[width * height];
	Pixel *originalBuffer = im.GetBuffer();
        std::memcpy(data, originalBuffer, width * height * sizeof(Pixel));
	lastSource = im.lastSource;
}

/**
 * Default Image Destructor
 */
Image::~Image(void)
{
	if(data != NULL){
		delete[] data;
	}
}

/**
 * Reset Image Size
 * @param width image width
 * @param height image height
 */
void Image::ResetSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

/**
 * Width Getter
 * @return image width
 */
int Image::GetWidth(void) const
{
	return width;
}

/**
 * Height Getter
 * @return image height
 */
int Image::GetHeight(void) const
{
	return height;
}

/**
 * Buffer Getter
 * @return pointer to image Pixel buffer
 */
Pixel * Image::GetBuffer(void) const
{
	return data;
}

/**
 * Buffer Setter
 * @param pointer to Pixel Buffer
 */
void Image::SetBuffer(Pixel *data)
{
	if(this->data != NULL){
		delete[] this->data;
	}
	this->data = data;
}

/**
 *Update calls update on the previous source
 */
void Image::Update() const
{
	if(lastSource != NULL){
		lastSource->Update();
	}
}
