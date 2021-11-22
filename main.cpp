#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void dump_ppm(vector<int>* buffer, string filename, const int WIDTH, const int HEIGHT) {
    ofstream image;
    cout << "dumping buffer in " << filename << endl;
    image.open(filename);
    {
		image << "P3" << endl;
		image << WIDTH << " " << HEIGHT << endl;
		image << "255" << endl;
	}
    for (auto value : *buffer) {
        image << value << " " << endl;
    }
    image.close();
    cout << "buffer dumped in " << filename << endl;
}

int main() {
    const int WIDTH = 500;
    const int HEIGHT = 500;
    vector<int> buffer;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            buffer.push_back(255);
        }
    }
    dump_ppm(&buffer, "test.ppm", WIDTH, HEIGHT);
    return 0;
}