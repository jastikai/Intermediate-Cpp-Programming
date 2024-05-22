/**
 * @file rgbapixel.h
 * Definition of the RGBAPixel class for the EasyPNG library.
 *
 * @author Chase Geigle
 * @date Spring 2012
 */
 #ifndef RGBAPIXEL_H
 #define RGBAPIXEL_H
 
 // int types
 #include <cstdint>
 using std::uint8_t;
 
class RGBAPixel
{
public:
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
	
	RGBAPixel() // default constructor
	{
		red = 255;
		green = 255;
		blue = 255;
		alpha = 255;
	};
	
	RGBAPixel(uint8_t _r, uint8_t _g, uint8_t _b) // constructor overload
	{
		red = _r;
		green = _g;
		blue = _b;
		alpha = 255;
	};
};
#endif
