#include <iostream>
#include <string>

struct Image
{
    virtual ~Image() = default;
    virtual void draw() = 0;
};

struct Bitmap : Image
{
    Bitmap(const std::string& filename)
    {
        std::cout << "Loading a file from " << filename << std::endl;
    }

    void draw() override
    {
        std::cout << "Drawing image" << std::endl;
    }
};

struct LazyBitmap : Image
{
    LazyBitmap(const std::string& filename)
        : filename{filename},
          bmp{nullptr}
    {}

    void draw() override
    {
        if(!bmp)
            bmp = new Bitmap{filename};

        bmp->draw();
    }

    ~LazyBitmap()
    {
        delete bmp;
    }

private:
    Bitmap* bmp;
    std::string filename;

};

void draw_image(Image& img)
{
    std::cout << "About to draw the image" << std::endl;
    img.draw();
    std::cout << "Done drawing the image" << std::endl;
}

void virtual_proxy()
{
    LazyBitmap bmp{"pokeman.png"};
    draw_image(bmp);
    draw_image(bmp);
}

int main()
{
    virtual_proxy();

    return 0;
}