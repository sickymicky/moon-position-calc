#include <iostream>
#include <cmath>
#include <iomanip>

const double PI = 3.14159265358979323846;

// Function to calculate Julian date
long double calculateJulianDate(int year, int month, int day) {
    if (month <= 2) {
        year--;
        month += 12;
    }
    int A = year / 100;
    int B = 2 - A + (A / 4);
    return std::floor(365.25 * (year + 4716)) + std::floor(30.6001 * (month + 1)) + day + B - 1524.5;
}

// Normalize an angle to 0 <= angle < 360 degrees
double normalizeAngle(double angle) {
    while (angle < 0) angle += 360.0;
    while (angle >= 360) angle -= 360.0;
    return angle;
}

// Function to calculate Moon's position (approximate)
void calculateMoonPosition(int year, int month, int day) {
    long double julianDate = calculateJulianDate(year, month, day);
    long double daysSinceEpoch = julianDate - 2451545.0; // Days since January 1, 2000

    // Mean longitude of the Moon
    double L = normalizeAngle(218.316 + 13.176396 * daysSinceEpoch);

    // Mean anomaly of the Moon
    double M = normalizeAngle(134.963 + 13.064993 * daysSinceEpoch);

    // Mean distance of the Moon from its ascending node
    double F = normalizeAngle(93.272 + 13.229350 * daysSinceEpoch);

    // Longitude of the Moon (simplified model)
    double longitude = L + 6.289 * sin(M * PI / 180.0); // Add sine of the anomaly

    // Latitude of the Moon (simplified model)
    double latitude = 5.128 * sin(F * PI / 180.0);

    // Distance to the Moon in Earth radii (simplified)
    double distance = 385001 - 20905 * cos(M * PI / 180.0);

    // Output results
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Julian Date: " << julianDate << "\n";
    std::cout << "Moon's Ecliptic Longitude: " << longitude << " degrees\n";
    std::cout << "Moon's Ecliptic Latitude: " << latitude << " degrees\n";
    std::cout << "Distance to the Moon: " << distance << " km\n";
}

int main() {
    int year, month, day;
    std::cout << "Enter year: ";
    std::cin >> year;
    std::cout << "Enter month: ";
    std::cin >> month;
    std::cout << "Enter day: ";
    std::cin >> day;

    calculateMoonPosition(year, month, day);

    return 0;
}

