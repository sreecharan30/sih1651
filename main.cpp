#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>

// Constants
const double speedOfSound = 343;  // Speed of sound in air (m/s)

// Function to calculate Euclidean distance between two 3D points
double calculateDistance(const std::vector<double>& p1, const std::vector<double>& p2) {
    return std::sqrt(std::pow(p1[0] - p2[0], 2) + std::pow(p1[1] - p2[1], 2) + std::pow(p1[2] - p2[2], 2));
}

int main() {
    // Coordinates of the sound source
    std::vector<double> source = {788, 776, 847};

    // Coordinates of the 6 microphones
    std::vector<std::vector<double>> mics = {
        {0, 10, 0},
        {0, -10, 0},
        {10, 0, 0},
        {-10, 0, 0},
        {0, 0, 10},
        {0, 0, -10}
    };

    int numMics = mics.size();
    std::vector<double> delays(numMics);

    // Calculate delays for each microphone based on the distance from the source
    for (int i = 0; i < numMics; ++i) {
        double distance = calculateDistance(mics[i], source);
        delays[i] = distance / speedOfSound;  // Delay in seconds
    }

    // Print all delays
    std::cout << "Delays (seconds): ";
    for (double delay : delays) {
        std::cout << std::fixed << std::setprecision(4) << delay << ", ";
    }
    std::cout << std::endl;

    // Calculate distances based on time delays for microphones
    double distance_y = (delays[1] - delays[0]) * speedOfSound;  // Distance along Y-axis
    double distance_x = (delays[3] - delays[2]) * speedOfSound;  // Distance along X-axis
    double distance_z = (delays[5] - delays[4]) * speedOfSound;  // Distance along Z-axis

    // Calculate slopes in 3D space
    double slope_calculated = std::sqrt(std::pow(distance_y, 2) + std::pow(distance_z, 2)) / distance_x;
    double slope_source = std::sqrt(std::pow(source[1], 2) + std::pow(source[2], 2)) / source[0];

    // Calculate angles in degrees
    double angle_calculated = std::atan2(std::sqrt(std::pow(distance_y, 2) + std::pow(distance_z, 2)), distance_x) * 180.0 / M_PI;
    double angle_source = std::atan2(std::sqrt(std::pow(source[1], 2) + std::pow(source[2], 2)), source[0]) * 180.0 / M_PI;

    // Calculate the difference between the angles
    double angle_difference = angle_calculated - angle_source;

    // Print calculated slopes and angles
    std::cout << "Slope (Calculated): " << slope_calculated << std::endl;
    std::cout << "Slope (Source): " << slope_source << std::endl;
    std::cout << "Angle (Calculated): " << angle_calculated << " degrees" << std::endl;
    std::cout << "Angle (Source): " << angle_source << " degrees" << std::endl;
    std::cout << "Angle Difference: " << angle_difference << " degrees" << std::endl;

    // Reflect calculation (if needed)
    double slope_calculated_reflected = slope_calculated;
    double angle_calculated_reflected = angle_calculated;

    // Print slopes and angles after reflection
    std::cout << "Slope (Calculated Reflected): " << slope_calculated_reflected << std::endl;
    std::cout << "Angle (Calculated Reflected): " << angle_calculated_reflected << " degrees" << std::endl;

    return 0;
}