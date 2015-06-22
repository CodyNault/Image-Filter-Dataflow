#include <image.hpp>
#include <sink.hpp>
#include <stdio.h>
#include <logging.hpp>

/**
 * Constructor for Sink. Initializes inout pointers to null.
 */
Sink::Sink()
{
    inputImg1 = NULL;
    inputImg2 = NULL;
}

/**
 * Setter for input 1 image pointer
 */
void Sink::SetInput(Image * imageArg)
{
    inputImg1 = imageArg;
}

/**
 * Setter for input 2 image pointer
 */
void Sink::SetInput2(Image * imageArg)
{
    inputImg2 = imageArg;
}

/**
 * Checks input 1 for pointer and if not set then throws exception
 */
void Sink::OneInputCheck()
{
    if(inputImg1 == NULL){
        DataFlowException except(SinkName(), "no input1!");
        throw except;
    }
}

/**
 * Checks input 1 and 2 for pointer and if not set then throws exception
 */
void Sink::TwoInputCheck()
{
    if(inputImg1 == NULL){
	char msg[1028];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException except(SinkName(), msg);
        throw except;
    }
    if(inputImg2 == NULL){
	char msg[1028];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException except(SinkName(), msg);
        throw except;
    }
}
