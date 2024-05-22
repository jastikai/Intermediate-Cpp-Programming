/**
 * Copyright 2024 University of Oulu
 * Authors:
 *   Elmeri Uotila <roope.uotila@oulu.fi>
 */

#include "canvasitem.h"

CanvasItem::CanvasItem(size_t x, size_t y, Vector2 pos, Vector2 scale, RGBAPixel color) {
    resize(x, y);
    
    // Set default alpha values to 0 and other color channels to 255
    for (size_t i = 0; i < x; ++i) {
        for (size_t j = 0; j < y; ++j) {
            RGBAPixel* pixel = (*this)(i, j);
            pixel->red = 255;
            pixel->green = 255;
            pixel->blue = 255;
            pixel->alpha = 0;
            // printf("canvasitem\n");
        }
    }
    
    position_ = pos;
    color_ = color;
    scale_ = scale;
}



RGBAPixel CanvasItem::getBlendedPixel(size_t x, size_t y) {
    // Get the original pixel from the CanvasItem
    RGBAPixel* originalPixel = (*this)(x, y);

    // Create a copy of the original pixel
    RGBAPixel blendedPixel = *originalPixel;

    // Multiply each channel of the blended pixel with the corresponding channel of color_
    blendedPixel.red = (blendedPixel.red * color_.red) / 255;
    blendedPixel.green = (blendedPixel.green * color_.green) / 255;
    blendedPixel.blue = (blendedPixel.blue * color_.blue) / 255;
    blendedPixel.alpha = (blendedPixel.alpha * color_.alpha) / 255;

    return blendedPixel;
}


Vector2 CanvasItem::position(){
	return position_;
}

Vector2 CanvasItem::scale(){
	return scale_;
}

void CanvasItem::SetPosition(Vector2 pos){
	position_ = pos;
}