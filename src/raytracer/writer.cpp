
#include <raytracer/writer.h>

// STB.
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#define FULL_QUALITY 100

namespace RT {

    IWriter::IWriter(std::string outputFilename, int imageWidth, int imageHeight) : _outputFilename(std::move(outputFilename)),
                                                                                    _imageWidth(imageWidth),
                                                                                    _imageHeight(imageHeight) {
    }

    IWriter::~IWriter() = default;

    void IWriter::WriteColor(int x, int y, const glm::vec3 &color, int numSamples) {
        float r = color.r;
        float g = color.g;
        float b = color.b;

        // Divide the input color by the number of samples.
        // Gamma corrected to a power of 1/2 (sqrt).
        float div = 1.0f / (float)numSamples;
//        r *= div;
//        g *= div;
//        b *= div;

        r = std::sqrt(r * div);
        g = std::sqrt(g * div);
        b = std::sqrt(b * div);

        OutputColor(x, y, r, g, b);
    }


    // JPGWriter.
    JPGWriter::JPGWriter(std::string outputFilename, int imageWidth, int imageHeight) : IWriter(std::move(outputFilename), imageWidth, imageHeight),
                                                                                        _channels(3),
                                                                                        _data(new unsigned char[_imageWidth * _imageHeight * _channels])
    {
    }

    JPGWriter::~JPGWriter() {
        stbi_write_jpg(("artifacts/" + _outputFilename + ".jpg").c_str(), _imageWidth, _imageHeight, _channels, _data, FULL_QUALITY);
        delete[] _data;
    }

    void JPGWriter::OutputColor(int x, int y, float r, float g, float b) {
        unsigned char* offset = _data + (x + _imageWidth * y) * _channels;
        offset[0] = static_cast<unsigned char>(255.999f * glm::clamp(r, 0.0f, 1.0f));
        offset[1] = static_cast<unsigned char>(255.999f * glm::clamp(g, 0.0f, 1.0f));
        offset[2] = static_cast<unsigned char>(255.999f * glm::clamp(b, 0.0f, 1.0f));
    }


    // PPMWriter.
    PPMWriter::PPMWriter(std::string outputFilename, int imageWidth, int imageHeight) : IWriter(std::move(outputFilename), imageWidth, imageHeight) {
        // Open file.
        _stream.open(_outputFilename.c_str(), std::ofstream::out);

        if (!_stream.is_open()) {
            throw std::runtime_error("Failed to open output file.");
        }

        // First line in a PPM file describes the format.
        // P3 means colors are encoded in ASCII.
        _stream << "P3" << std::endl;

        // Column / Row.
        _stream << _imageWidth << " " << _imageHeight << std::endl;

        // Maximum color value (255).
        _stream << 255 << std::endl;
    }

    PPMWriter::~PPMWriter() {
        _stream.close();
    }

    void PPMWriter::OutputColor(int, int, float r, float g, float b) {
        // Get in range [0, 255].
        _stream << static_cast<unsigned>(255.999f * glm::clamp(r, 0.0f, 1.0f)) << " "
                << static_cast<unsigned>(255.999f * glm::clamp(g, 0.0f, 1.0f)) << " "
                << static_cast<unsigned>(255.999f * glm::clamp(b, 0.0f, 1.0f)) << std::endl;
    }

}