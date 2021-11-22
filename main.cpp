#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Shape
{
public:
    Shape(int width, int height, int background, int foreground)
    {
        this->background = background;
        this->foreground = foreground;
        for (int i = 0; i <= width * height; i++)
        {
            buffer.push_back(background);
        }
        this->width = width;
        this->height = height;
    };
    virtual ~Shape() = default;
    virtual void draw() = 0;
    vector<uint> *getBuffer()
    {
        return &buffer;
    }
    int getWidth()
    {
        return width;
    }
    int getHeight()
    {
        return height;
    }
    int getForeground()
    {
        return foreground;
    }
    int getBackground()
    {
        return background;
    }

protected:
    vector<uint> buffer;
    int background;
    int foreground;
    int width;
    int height;
};

class FilledCircle : public Shape
{
    int radius;

public:
    FilledCircle(
        int width,
        int height,
        int background,
        int foreground,
        int radius) : Shape(width, height, background, foreground)
    {
        this->radius = radius;
    };
    void draw() override
    {
        uint cx = width;
        uint cy = height;
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                uint dx = cx - x * 2 - 1;
                uint dy = cy - y * 2 - 1;
                int r = radius * radius;
                if ((dx * dx) + (dy * dy) <= (r))
                {
                    buffer.at(y * width + x) = foreground;
                }
                else
                {
                    buffer.at(y * width + x) = background;
                }
            }
        }
    }
};

void dump_shape_to_ppm(Shape *shape, string filename)
{
    ofstream image;
    cout << "dumping buffer in " << filename << endl;
    image.open(filename);
    {
        image << "P3 " << endl;
        image << shape->getWidth() << " " << shape->getHeight() << " 255" << endl;
    }
    for (int y = 0; y < shape->getHeight(); y++)
    {
        for (int x = 0; x < shape->getWidth(); x++)
        {
            uint pixel = shape->getBuffer()->at(y * shape->getWidth() + x);
            auto r = pixel >> 8 * 0 & 0xff;
            auto g = pixel >> 8 * 1 & 0xff;
            auto b = pixel >> 8 * 2 & 0xff;
            image << r << " " << g << " " << b << endl;
        }
    }
    image.close();
    cout << "buffer dumped in " << filename << endl;
}

int main()
{
    const int WIDTH = 800;
    const int HEIGHT = 600;
    const int BACKGROUND = 0x00ff00;
    const int FOREGROUND = 0xff00ff;
    FilledCircle circle = FilledCircle(WIDTH, HEIGHT, BACKGROUND, FOREGROUND, HEIGHT / 2);
    circle.draw();
    dump_shape_to_ppm(&circle, "circle.ppm");
    return 0;
}
