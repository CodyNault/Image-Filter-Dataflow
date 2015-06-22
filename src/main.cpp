#include <PNMreader.hpp>
#include <PNMwriter.hpp>
#include <filters.hpp>
#include <logging.hpp>

int main(int argc, char *argv[])
{
    PNMreader reader(argv[1]);

    Crop crop;
    crop.SetRegion(300, 1400, 50, 400);
    crop.SetInput(reader.GetOutput());

    Transpose t;
    t.SetInput(crop.GetOutput());

    Invert i;
    i.SetInput(t.GetOutput());

    Color color(50, 1101, 0, 0, 128);
    
    LRConcat lr;
    lr.SetInput(color.GetOutput());
    lr.SetInput2(i.GetOutput());

    Color white(401, 1101, 255, 255, 255);

    Checkerboard cb;
    cb.SetInput(lr.GetOutput());
    cb.SetInput2(white.GetOutput());

    cb.GetOutput()->Update();

    PNMwriter writer;
    writer.SetInput(cb.GetOutput());
    writer.Write(argv[2]);

    CheckSum cs;
    cs.SetInput(cb.GetOutput());
    cs.OutputCheckSum();
    Logger::Finalize();
}
