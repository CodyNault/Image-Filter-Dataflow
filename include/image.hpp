#ifndef IMAGE_H
#define IMAGE_H
class Source;

typedef struct{
        unsigned char red;
        unsigned char green;
        unsigned char blue;
} Pixel;

class Image
{
private:
	int width;
	int height;
	Pixel *data;
public:
	Source *lastSource;
	Image(void);
	Image(int, int, Pixel *);
	Image(Image &);
	virtual ~Image(void);
	void ResetSize(int width, int height);
	int GetHeight(void) const;
	int GetWidth(void) const;
	Pixel * GetBuffer(void) const;
	void SetBuffer(Pixel *);
	void Update() const;
};

#endif
