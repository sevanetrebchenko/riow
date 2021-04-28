
#ifndef RAYTRACER_WRITER_H
#define RAYTRACER_WRITER_H

#include <pch.h>

namespace RT {

    // Interface for writing output files.
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


    // Writes to .jpg files.
    class JPGWriter : public IWriter {
        public:
            JPGWriter(std::string outputFilename, int imageWidth, int imageHeight);
            ~JPGWriter() override;

        private:
            void OutputColor(int x, int y, float r, float g, float b) override;

            int _channels;
            unsigned char* _data;
    };


    // Writes to .ppm files.
    class PPMWriter : public IWriter {
        public:
            PPMWriter(std::string outputFilename, int imageWidth, int imageHeight);
            ~PPMWriter() override;

        private:
            void OutputColor(int x, int y, float r, float g, float b) override;

            std::ofstream _stream;
    };

}

#endif //RAYTRACER_WRITER_H
