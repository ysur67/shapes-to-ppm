#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void dump_ppm(vector<int>* buffer, string filename, const int width, const int height) {
    ofstream image;
    cout << "dumping buffer in " << filename << endl;
    image.open(filename);
    {
		image << "P3 " << endl;
		image << " " << width << " " << height << " 255" << endl;
	}
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int pixel = buffer->at(y * width + x);
            image << pixel << " ";
        }
    }
    image.close();
    cout << "buffer dumped in " << filename << endl;
}

void write_circle(vector<int>* buffer, int width, int height, int radius) {
    uint cx = width;
    uint cy = height;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint dx = cx - x * 2 - 1;
            uint dy = cy - y * 2 - 1;
            int r = radius * radius;
            if ((dx * dx) + (dy * dy) <= (r)) {
                buffer->at(y * width + x) = 255;
            }
        }
    }
}

int main() {
    const int WIDTH = 1920;
    const int HEIGHT = 1080;
    vector<int> buffer;
    for (int i = 0; i <= WIDTH * HEIGHT; i++) {
        buffer.push_back(0);
    }
    write_circle(&buffer, WIDTH, HEIGHT, 900);
    dump_ppm(&buffer, "circle.ppm", WIDTH, HEIGHT);
    return 0;
}