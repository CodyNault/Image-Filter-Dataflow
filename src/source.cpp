#include <image.hpp>
#include <source.hpp>
#include <logging.hpp>
#include <iostream>

/**
 * Returns a pointer to the output image
 */
Image * Source::GetOutput()
{
	outputImg.lastSource = this;
	return &outputImg;
}

//Set of Sources on the current update branch
std::set<Source *> Source::sourceRefLog;

/**
 * This registers source pointers with the static set for circular
 * reference prevention
 */
void Source::updateSourceRefs(Source *ref)
{
	if(Source::sourceRefLog.count(ref) > 0){
		DataFlowException except("Source", "Circular Reference in DataFlow");
                throw except;
	}
	Source::sourceRefLog.insert(ref);
}

/**
 * This unregisters source pointers with the static set for circular
 * reference prevention. It is important to unregister sources after
 * after they execute as it is perfectly reasonable to have a source to 
 * provide its output to multiple sinks. But by registering before update
 * and un-registering after, it prevents a single source from being referenced
 * multiple times on a single branch of the update tree.
 */
void Source::removeFromSourceRefs(Source *ref)
{
	Source::sourceRefLog.erase(ref);
}
