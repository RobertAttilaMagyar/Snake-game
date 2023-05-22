#pragma once
class Colour
{
public:
	int red, green, blue;
	Colour(int r = 0, int g = 0, int b = 255) {
		red = r; green = g, blue = b;
	}
	void operator=(const Colour c)
	{
		this->blue = c.blue;
		this->red = c.red;
		this->green = c.green;
	}
};

