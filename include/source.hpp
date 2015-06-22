#ifndef SOURCE_H
#define SOURCE_H
#include <image.hpp>
#include <set>

class Source
{
    protected:
	Image outputImg;
	virtual void Execute() = 0;
	virtual const char * SourceName() = 0;
	void static updateSourceRefs(Source *);
	void static removeFromSourceRefs(Source *);
    public:
	static std::set<Source *> sourceRefLog;
	virtual void Update() = 0;
	Image * GetOutput();
//	friend void Image::Update() const;
};
#endif
