#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Point
{
public:
    int x;
    int y;
    Point()
    {
        this->x = 0;
        this->y = 0;
    };
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    };
};

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

class FilledTriangle : public Shape
{
public:
    FilledTriangle(
        int width,
        int height,
        int foreground,
        int background,
        Point a,
        Point b,
        Point c) : Shape(width, height, foreground, background)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    };

    void draw() override
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int da = (a.x - x) * (b.y - a.y) - (b.x - a.x) * (a.y - y);
                int db = (b.x - x) * (c.y - b.y) - (c.x - b.x) * (b.y - y);
                int dc = (c.x - x) * (a.y - c.y) - (a.x - c.x) * (c.y * y);
                if ((da >= 0 && db >= 0 && dc >= 0) || (da <= 0 && db <= 0 && dc <= 0))
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

private:
    Point a;
    Point b;
    Point c;
};

class FilledRectangle : public Shape
{
public:
    FilledRectangle(
        int width,
        int height,
        int foreground,
        int background,
        Point a,
        Point b,
        Point c,
        Point d) : Shape(width, height, foreground, background)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    };

    void draw() override
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if ((x > a.x && x < c.x) && (y > a.y && y < c.y)) {
                    buffer.at(y * width + x) = foreground;
                } else {
                    buffer.at(y * width + x) = background;
                }
            }
        }
    }

private:
    Point a;
    Point b;
    Point c;
    Point d;
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
    const int BACKGROUND = 0xffff00;
    const int FOREGROUND = 0xff00ff;
    FilledCircle circle = FilledCircle(WIDTH, HEIGHT, BACKGROUND, FOREGROUND, HEIGHT / 2);
    circle.draw();
    dump_shape_to_ppm(&circle, "circle.ppm");
    FilledTriangle triangle = FilledTriangle(
        WIDTH,
        HEIGHT,
        BACKGROUND,
        FOREGROUND,
        Point(200, 505),
        Point(600, 200),
        Point(200, 5));
    triangle.draw();
    dump_shape_to_ppm(&triangle, "triangle.ppm");
    FilledRectangle square = FilledRectangle(
        WIDTH,
        HEIGHT,
        BACKGROUND,
        FOREGROUND,
        Point(100, 100),
        Point(100, 600),
        Point(600, 400),
        Point(200, 500)
        );
    square.draw();
    dump_shape_to_ppm(&square, "square.ppm");
    return 0;
}
