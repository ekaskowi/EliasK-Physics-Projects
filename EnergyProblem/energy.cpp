#include <fstream>
#include <iostream>
// for cos
#include <cmath>
using std::ofstream;
using std::ios;

void add_to_file(double num) {
    ofstream txt;
    txt.open("data.txt", ios::app);

    txt << num << '\n';

    txt.close();
}

// generate a plot of U vs theta in a txt so i can export to excel lol
int main() {
    for (unsigned i = 0; i < 100; i++) {
        double i_radians = (i / 100.0) * 2.0 * M_PI;
        add_to_file((0.8 * i_radians) + 1 - cos(i_radians));
    }
    return 0;
}