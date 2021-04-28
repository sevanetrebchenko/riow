
#ifndef RAYTRACER_JPG_WRITER_H
#define RAYTRACER_JPG_WRITER_H

#include <raytracer/writers//image_writer.h>

namespace RT {

    class JPGWriter : public IWriter {
        public:
            JPGWriter(std::string outputFilename, int imageWidth, int imageHeight);
            ~JPGWriter() override;

        private:
            void OutputColor(int x, int y, float r, float g, float b) override;

            int _channels;
            unsigned char* _data;
    };

}

#endif //RAYTRACER_JPG_WRITER_H
