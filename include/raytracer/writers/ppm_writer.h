
#ifndef RAYTRACER_PPM_WRITER_H
#define RAYTRACER_PPM_WRITER_H

#include <raytracer/writers/image_writer.h>

namespace RT {

    class PPMWriter : public IWriter {
        public:
            PPMWriter(std::string outputFilename, int imageWidth, int imageHeight);
            ~PPMWriter() override;

        private:
            void OutputColor(int x, int y, float r, float g, float b) override;

            std::ofstream _stream;
    };

}

#endif //RAYTRACER_PPM_WRITER_H
