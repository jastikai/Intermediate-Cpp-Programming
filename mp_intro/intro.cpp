#include "RGB/png.h"
#include "RGB/rgbapixel.h"

#include <string>
#include <cmath>

void rotate(std::string inputFile, std::string outputFile) {
	PNG pic(inputFile);
	// Your code here
	int height = (int)pic.height();
	int width = (int)pic.width();
	
	PNG rotatedPic(width, height);
	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			RGBAPixel * pixel = pic(x, y);
			
			RGBAPixel * rotatedPixel = rotatedPic(width - x - 1, height - y - 1);
			
			*rotatedPixel = *pixel;
		}
	}
	rotatedPic.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
	PNG png(width, height);
	// Your code here
	// Generate gradient pattern
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            // Calculate color components based on position
            uint8_t red = static_cast<uint8_t>(x * 255 / width);
            uint8_t green = static_cast<uint8_t>(y * 255 / height);
            uint8_t blue = static_cast<uint8_t>((x + y) * 255 / (width + height));

            // Set pixel color
            RGBAPixel *pixel = png(x, y);
            pixel->red = red;
            pixel->green = green;
            pixel->blue = blue;
            pixel->alpha = 255;
        }
    }

   
	return png;
}
