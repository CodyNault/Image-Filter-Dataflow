#ifndef FILTER_H
#define FILTER_H
#include <source.hpp>
#include <sink.hpp>
#include <image.hpp>

class Filter : public Source, public Sink
{
    private:
        virtual const char * SourceName(){return FilterName();}
        virtual const char * SinkName(){return FilterName();}
        virtual const char * FilterName() = 0;
    public:
	void Update();
	virtual void Execute() = 0;
};

#endif
