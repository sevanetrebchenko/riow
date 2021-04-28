
#include <raytracer/writers/jpg_writer.h>
#include <utility>

// STB.
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#define FULL_QUALITY 100

namespace RT {


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

}
