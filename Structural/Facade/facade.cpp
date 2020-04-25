#include <vector>
#include <memory>
#include <string>
#include <boost/lexical_cast.hpp>


class Point
{
public:
	Point() = default;

	explicit Point(const int x, const int y)
		: x{ x }, y{ y }
	{}

private:
	int x;
	int y;
};

class TextBuffer
{
public:
	explicit TextBuffer(uint8_t width, uint8_t height)
		: width(width), height(height)
	{}

	uint8_t get_size()
	{
		return width * height;
	}

	void add_string(std::string &ctsr)
	{}

private:
	uint8_t width;
	uint8_t height;
};

class Viewport
{
public:
	explicit Viewport(std::shared_ptr<TextBuffer> buffer, const uint8_t size,
		const Point& topLeft, const Point& topRight)
		: buffer{ buffer }, size{ size }, topLeft{ topLeft }, topRight{ topRight }
	{}

private:
	std::shared_ptr<TextBuffer> buffer;
	uint8_t size;
	Point topLeft;
	Point topRight;
};

class Window
{
public:
	explicit Window(const std::string& title, uint8_t width, uint8_t height)
		: title{ title }, width{ width }, height{ height }
	{}

	std::vector<std::shared_ptr<TextBuffer>>& buffers()
	{
		return m_buffers;
	}

	std::vector<std::shared_ptr<Viewport>>& viewports()
	{
		return m_viewports;
	}

private:
	std::string title;
	uint8_t width;
	uint8_t height;

	std::vector<std::shared_ptr<TextBuffer>> m_buffers;
	std::vector<std::shared_ptr<Viewport>> m_viewports;
};

class Console
{
public:
	std::vector<std::shared_ptr<Window>> windows;

	static Console& instance()
	{
		static Console console;
		return console;
	}

	std::shared_ptr<Window> multicolomn(const std::string& title, uint8_t columnCount,
		uint8_t columnWidth, uint8_t charsHigh)
	{
		auto w = std::make_shared<Window>(title, columnCount*columnWidth*charWidth,
			charsHigh*charHeight);
		for (uint8_t c = 0; c < columnCount; ++c)
		{
			auto buffer = std::make_shared<TextBuffer>(columnWidth, charsHigh);
			w->buffers().push_back(buffer);
			auto viewport = std::make_shared<Viewport>(buffer, buffer->get_size(), Point{},
				Point{ columnWidth*c, 0 });
			w->viewports().push_back(viewport);
			windows.push_back(w);
		}
		return w;
	}


	std::shared_ptr<Window> single(const std::string& title, uint8_t charsWide,
		uint8_t charsHigh)
	{
		auto w = std::make_shared<Window>(title, charsWide*charWidth,
			charsHigh*charHeight);
		auto buffer = std::make_shared<TextBuffer>(charsWide, charsHigh);
		w->buffers().push_back(buffer);
		auto viewport = std::make_shared<Viewport>(buffer, 10, Point{}, Point{90, 90});
		w->viewports().push_back(viewport);
		windows.push_back(w);
		return w;
	}

private:
	const int charWidth = 10;
	const int charHeight = 14;

	Console() {};
	Console(Console const&) = delete;
	void operator=(Console const&) = delete;
};

int main()
{
	// auto window = Console::instance().single("Test", 50, 30);
	// window->show();

	auto window = Console::instance().multicolomn("Test", 2, 40, 40);

	for (size_t i = 0; i<40; i++)
	{
		window->buffers()[1]->add_string("This is line " + boost::lexical_cast<std::string>(i));

	}

	return 0;
}