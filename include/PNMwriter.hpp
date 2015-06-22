#ifndef PNMWRITER_H
#define PNMWRITER_H
#include <sink.hpp>

class PNMwriter : public Sink
{
    public:
	void Write(const char *);
	virtual const char * SinkName() { return "PNMwriter"; }
};
#endif
