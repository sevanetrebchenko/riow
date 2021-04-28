
#include <raytracer/writers/image_writer.h>

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

}
