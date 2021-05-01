
#include <raytracer/application.h>

int main() {
    RT::Application app("test", 400, 400);

    try {
        app.Init();
    }
    catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    app.Run();
    app.Shutdown();

    return 0;
}

//     // Program takes in filename, samples per pixel, number of ray bounces.
//    if (argc < 5) {
//        std::cout << "Invalid number of arguments passed to program\n";
//        std::cout << "Usage: " << argv[0] << " <filename> <height> <samples per pixel> <number of ray bounces>\n";
//        return 0;
//    }
//
//    // Camera
////    glm::vec3 eyePosition(0.0f, 1.5f, 4.0f);
////    glm::vec3 lookAtPosition(0.0f, 1.0f, 0.0f);
////    glm::vec3 globalUpVector(0.0f, 1.0f, 0.0f);
//
//    glm::vec3 eyePosition(0.0f, 1.0f, 5.0f);
//    glm::vec3 lookAtPosition(0.0f, 3.0f, 0.0f);
//    glm::vec3 globalUpVector(0.0f, 1.0f, 0.0f);
//    float focusDistance = glm::length(lookAtPosition - eyePosition);
//
//    RT::Camera camera(eyePosition, lookAtPosition, globalUpVector, 40, 16.0f / 9.0f, 0.0f, focusDistance, 0.0f, 1.0f);
//
//    // Image
//    unsigned samplesPerPixel = std::stoul(argv[3]);
//    unsigned numRayBounces = std::stoul(argv[4]);
//    RT::PPMWriter::IMAGE_HEIGHT = std::stoul(argv[2]);
//    RT::PPMWriter::IMAGE_WIDTH = static_cast<unsigned>(RT::PPMWriter::IMAGE_HEIGHT * camera.GetAspectRatio());
//
//    // World
//    RT::HittableCollection world = RandomScene();
//
//    // Render
//    RT::PPMWriter writer(argv[1]);
//
//    float u, v;
//    unsigned lineCounter = RT::PPMWriter::IMAGE_HEIGHT;
//
//    for (unsigned y = 0; y < RT::PPMWriter::IMAGE_HEIGHT; ++y) {
//        std::cout << "\rScanlines remaining: " << lineCounter-- << " " << std::flush;
//
//        for (unsigned x = 0; x < RT::PPMWriter::IMAGE_WIDTH; ++x) {
//            glm::vec3 pixelColor(0.0f, 0.0f, 0.0f);
//
//            // Antialiasing.
//            for (int sample = 0; sample < samplesPerPixel; ++sample) {
//                u = (x + RT::RandomFloat()) / float(RT::PPMWriter::IMAGE_WIDTH - 1);
//                v = (y + RT::RandomFloat()) / float(RT::PPMWriter::IMAGE_HEIGHT - 1);
//
//                pixelColor += RayColor(camera.GetRay(u, v), world, numRayBounces);
//            }
//
//            writer.WriteColor(pixelColor, samplesPerPixel);
//        }
//    }
//
//    // Flush extra characters from previous commands from the console.
//    std::cout << "\r                            " << std::flush;
//    std::cout << "\rDone." << std::endl;
//
//    return 0;