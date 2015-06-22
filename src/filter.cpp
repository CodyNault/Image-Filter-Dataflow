#include <filter.hpp>
#include <cstdlib>
#include <stdio.h>
#include <logging.hpp>

/**
 * Update ensures inputs are up to date before execution
 */
void Filter::Update()
{
	updateSourceRefs(this);
	char msg[128];
	if(inputImg1 != NULL){
        	sprintf(msg, "%s: about to update input1", SourceName());
        	Logger::LogEvent(msg);
		inputImg1->Update();
        	sprintf(msg, "%s: done updating input1", SourceName());
        	Logger::LogEvent(msg);
	}
	if(inputImg2 != NULL){
        	sprintf(msg, "%s: about to update input2", SourceName());
        	Logger::LogEvent(msg);
		inputImg2->Update();
        	sprintf(msg, "%s: done updating input2", SourceName());
        	Logger::LogEvent(msg);
	}
	sprintf(msg, "%s: about to execute", SourceName());
	Logger::LogEvent(msg);
	try{
		Execute();
	}catch(DataFlowException& except){
        	sprintf(msg, "Throwing exception: (%s): %s", SourceName(), except.what());
        	Logger::LogEvent(msg);
		throw except;
	}
	Source::removeFromSourceRefs(this);
	sprintf(msg, "%s: done executing", SourceName());
	Logger::LogEvent(msg);
}
