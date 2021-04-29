
#ifndef RAYTRACER_DIRECTORY_H
#define RAYTRACER_DIRECTORY_H

#include <pch.h>

namespace RT {

    [[nodiscard]] std::vector<std::string> GetFiles(std::string directoryPath);

    [[nodiscard]] std::vector<std::string> GetAssetNames(const std::vector<std::string>& filePaths);
    [[nodiscard]] std::string GetAssetName(const std::string& assetPath);

    [[nodiscard]] std::string GetAssetExtension(const std::string& assetPath);

    [[nodiscard]] std::string ConvertToNativeSeparators(std::string path);

}

#endif //RAYTRACER_DIRECTORY_H
