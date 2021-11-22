#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void dump_ppm(vector<uint>* buffer, string filename, const int width, const int height) {
    ofstream image;
    cout << "dumping buffer in " << filename << endl;
    image.open(filename);
    {
		image << "P3 " << endl;
		image <<  width << " " << height << " 255" << endl;
	}
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint pixel = buffer->at(y * width + x);
            auto r = pixel >> 8 * 0 & 0xff;
            auto g = pixel >> 8 * 1 & 0xff;
            auto b = pixel >> 8 * 2 & 0xff;
            image << r << " " << g << " " << b << endl;
        }
    }
    image.close();
    cout << "buffer dumped in " << filename << endl;
}

void write_circle(vector<uint>* buffer, int width, int height, int radius) {
    uint cx = width;
    uint cy = height;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint dx = cx - x * 2 - 1;
            uint dy = cy - y * 2 - 1;
            int r = radius * radius;
            if ((dx * dx) + (dy * dy) <= (r)) {
                buffer->at(y * width + x) = 0xFF00FF;
            }
        }
    }
}

void fill_buffer(vector<uint>* buffer, int width, int height) {
    for (int i = 0; i <= width * height; i++) {
        buffer->at(i) = 0;
    }
}

int main() {
    const int WIDTH = 800;
    const int HEIGHT = 600;
    vector<uint> buffer;
    for (int i = 0; i <= WIDTH * HEIGHT; i++) {
        buffer.push_back(0);
    }
    write_circle(&buffer, WIDTH, HEIGHT, HEIGHT / 2);
    dump_ppm(&buffer, "circle.ppm", WIDTH, HEIGHT);
    fill_buffer(&buffer, WIDTH, HEIGHT);
    return 0;
}