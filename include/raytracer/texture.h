
#ifndef RAYTRACER_TEXTURE_H
#define RAYTRACER_TEXTURE_H

namespace RT {

    class ITexture {
        public:
            virtual ~ITexture();

            [[nodiscard]] virtual glm::vec3 GetColorValue(float u, float v, const glm::vec3& intersectionPoint) const = 0;
            [[nodiscard]] virtual glm::vec3 GetColorValue(const glm::vec2& uvCoordinates, const glm::vec3& intersectionPoint) const = 0;
    };


    class SolidColorTexture : public ITexture {
        public:
            SolidColorTexture(glm::vec3 color);
            ~SolidColorTexture() override;

            [[nodiscard]] glm::vec3 GetColorValue(float u, float v, const glm::vec3& point) const override;
            [[nodiscard]] glm::vec3 GetColorValue(const glm::vec2& uvCoordinates, const glm::vec3& intersectionPoint) const override;

        private:
            glm::vec3 _color;
    };


    class ImageTexture : public ITexture {
        public:
            ImageTexture(const char* filename);
            ~ImageTexture() override;

            [[nodiscard]] glm::vec3 GetColorValue(float u, float v, const glm::vec3& point) const override;
            [[nodiscard]] glm::vec3 GetColorValue(const glm::vec2& uvCoordinates, const glm::vec3& intersectionPoint) const override;

        private:
            [[nodiscard]] glm::vec3 GetColor(float u, float v, const glm::vec3& point) const;

            unsigned char* _data;
            int _width;
            int _height;
            int _channels;
    };


}

#endif //RAYTRACER_TEXTURE_H
