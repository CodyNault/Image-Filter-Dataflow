#ifndef SINK_H
#define SINK_H
#include <image.hpp>

class Sink
{
protected:
    const Image *inputImg1;
    const Image *inputImg2;
    void OneInputCheck();
    void TwoInputCheck();
public:
    Sink();
    virtual void SetInput(Image *);
    virtual void SetInput2(Image *);
    virtual const char * SinkName() = 0;
};
#endif
