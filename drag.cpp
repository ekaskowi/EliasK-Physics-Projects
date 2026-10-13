#include <iostream>
#include <cmath>
// cmath includes std::log(double x) & M_PI
#include <vector>

using std::cout;
using std::endl;
using std::cos;
using std::sin;
using std::vector;
using std::log;

// The range in a linear medium:
// 0 = (Vy0 + Vter) * R / Vx0 + Vter * (tau) * Ln(1 - R / Vx0* (tau))
// where tau = (mass / drag coeff.)
// Vter = (mass * g) / drag coeff = 1, then tau must also = 1
// therefore the eq becomes: 
// 0 = (Vy0 + 1) * R / Vx0 + Ln(1 - R / Vx0)

// In a vacuum:
// R = 2 * Vx0 * Vy0 / g
// max angle = pi / 4

double compute_max_range_vacuum(double a) {  // angle in radians
    double vx0 = cos(a);
    double vy0 = sin(a);

    return 2.0 * vx0 * vy0;
}

// 0 = (Vy0 + 1) * R / Vx0 + Ln(1 - R / Vx0)
vector<double> compute_max_range(double a, double step){
    vector<double> result(2);
    
    double vx0 = cos(a);
    double vy0 = sin(a);

    // initial guess for R at max value (R = vx0), because Ln(1 - R / vx0) is only valid on the interval [0, vx0)
    double R = vx0 - 0.1;

    // reduce until eq is positive, and return R just before and just after last step. this gives you the range where the eq ~= 0
    double eq = (vy0 + 1.0) * R / vx0 + log(1.0 - R / vx0);
    while (eq < 0.0) {
        result.at(1) = R;
        R = R - step;
        eq = (vy0 + 1.0) * R / vx0 + log(1.0 - R / vx0);
    }
    result.at(0) = R;
    
    return result;
}

int main() {
    // found this angle list after a lot of random guesses
    double angle_list[] = {
        M_PI / 9.0,  // 20 deg
        M_PI / 6.0,   // 30 deg
        35.1 * 0.01745329, // 35 deg
        35.37 * 0.01745329,
        35.38 * 0.01745329,
        35.39 * 0.01745329,
        35.4 * 0.01745329,
        35.41 * 0.01745329,
        35.42 * 0.01745329,
        35.43 * 0.01745329,
        36.5 * 0.01745329, // 36.5 deg
        M_PI / 4.0,   // 45 deg
    };

    cout << "---------------------------------------" << endl;
    cout << "Max range in vacuum: " << compute_max_range_vacuum(M_PI / 4.0) << endl;
    for (double a : angle_list) {
        vector<double> max_range = compute_max_range(a, 0.0001);
    cout << "Angle: " << a * 57.2957795 << " degrees, Range in vacuum between: [" << max_range.at(0) << ", " << max_range.at(1) << "]"<< endl;
    }
    cout << "---------------------------------------" << endl;

    return 0;
}
