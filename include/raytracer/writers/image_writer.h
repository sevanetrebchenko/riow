
#ifndef RAYTRACER_IMAGE_WRITER_H
#define RAYTRACER_IMAGE_WRITER_H

#include <pch.h>

namespace RT {

    class IWriter {
        public:
            IWriter(std::string outputFilename, int imageWidth, int imageHeight);
            virtual ~IWriter();

            void WriteColor(int x, int y, const glm::vec3& color, int numSamples);

        protected:
            virtual void OutputColor(int x, int y, float r, float g, float b) = 0;

            int _imageWidth;
            int _imageHeight;
            std::string _outputFilename;
    };

}

#endif //RAYTRACER_IMAGE_WRITER_H
