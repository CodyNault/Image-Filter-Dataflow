#ifndef PNMREADER_H
#define PNMREADER_H
#include <source.hpp>

class PNMreader : public Source
{
    private:
	char *filename;
	virtual const char * SourceName(){return "PNMreader";}
    public: 
	PNMreader(const char *filename);
	virtual void Execute();
	virtual ~PNMreader();
	void Update();
};
#endif
