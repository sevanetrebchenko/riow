
#include <raytracer/writers/ppm_writer.h>

namespace RT {

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
