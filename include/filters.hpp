#ifndef FILTERS_H
#define FILTERS_H
#include <source.hpp>
#include <sink.hpp>
#include <filter.hpp>

class Shrinker : public Filter
{
    public:
	virtual void Execute();
        virtual const char *FilterName() { return "Shrinker"; };
};

class LRConcat : public Filter
{
    public:
	virtual void Execute();
        virtual const char *FilterName() { return "LRConcat"; };
};

class TBConcat : public Filter
{
    public:
	virtual void Execute();
        virtual const char *FilterName() { return "TBConcat"; };
};

class Blender : public Filter
{ 
    private:
	float factor;
    public:
	Blender();
	virtual void Execute();
	void SetFactor(float);
        virtual const char *FilterName() { return "Blender"; };
};

class Crop : public Filter
{
  public:
                   Crop()  { Istart = Istop = Jstart = Jstop = -1; };
    virtual const char *FilterName() { return "Crop"; };
    virtual void   Execute();
    void           SetRegion(int Istart_, int Istop_, int Jstart_, int Jstop_)
                      {
                        Istart = Istart_;
                        Istop  = Istop_;
                        Jstart = Jstart_;
                        Jstop  = Jstop_;
                      }

  private:
    int Istart, Istop, Jstart, Jstop;
};

class Transpose : public Filter
{
    public:
        virtual void Execute();
        virtual const char *FilterName() { return "Transpose"; };
};

class Invert : public Filter
{
    public:
        virtual void Execute();
        virtual const char *FilterName() { return "Invert"; };
};

class Checkerboard : public Filter
{
    public:
        virtual void Execute();
        virtual const char *FilterName() { return "Checkerboard"; };
};

class Color : public Source
{
    private:
	int width, height, red, green, blue;
    public:
        Color(int, int, int, int, int);
        virtual void Execute();
	virtual void Update();
        virtual const char *SourceName() { return "Color"; };
};

class CheckSum : public Sink
{
    public:
        void OutputCheckSum();
        virtual const char *SinkName() { return "CheckSum"; };
};

#endif
