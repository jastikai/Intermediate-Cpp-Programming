/**
 * Copyright 2024 University of Oulu
 * Authors:
 *   Elmeri Uotila <roope.uotila@oulu.fi>
 */

#include "canvas.h"
#include <iostream>

Canvas::Canvas() {
    // Initialize items as an empty vector
    items = std::vector<CanvasItem*>();
    itemcount = 0;
}

Canvas::~Canvas()
{
	// Delete each CanvasItem in the vector
    // for (CanvasItem* item : items) {
    //     delete item;
    // }
    // items.clear();
    itemcount = 0;
}



void Canvas::Add(CanvasItem* item)
{

    items.push_back(item);
    itemcount++;
}

void Canvas::Remove(CanvasItem* item)
{
    // Find and remove the item from the list
    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end()) {
        items.erase(it);
        // Decrement the item count
        itemcount--;
    }
}

void Canvas::Swap(CanvasItem* item1, CanvasItem* item2)
{
    // Find given items from list and swap their positions
    // Swap only if both pointers are found
    auto it1 = std::find(items.begin(), items.end(), item1);
    auto it2 = std::find(items.begin(), items.end(), item2);
    if (it1 != items.end() && it2 != items.end()) {
        std::iter_swap(it1, it2);
    }
}

void Canvas::draw(PNG* canvas) const
{
    for (int i = 0; i < itemcount; i++) {
        CanvasItem* item = items[i];
        for (size_t x = 0, xmax = item->width(); x < xmax; x++) {
            for (size_t y = 0, ymax = item->height(); y < ymax; y++) {
                RGBAPixel coli = item->getBlendedPixel(x, y);
                Vector2 sc = item->scale();
                for (int xs = 0; xs < std::abs((int)(sc.x() - 0.001)) + 1; xs++) {
                    for (int ys = 0; ys < std::abs((int)(sc.y() - 0.001)) + 1; ys++) {
                        int x1 = x * sc.x() + xs + item->position().x();
                        int y1 = y * sc.y() + ys + item->position().y();
                        if (x1 >= 0 && x1 < (int)canvas->width() && y1 >= 0 && y1 < (int)canvas->height()) {
                            RGBAPixel* colc = (*canvas)(x1, y1);
                            colc->red = (coli.alpha * coli.red + (255 - coli.alpha) * colc->red) / 255;
                            colc->green = (coli.alpha * coli.green + (255 - coli.alpha) * colc->green) / 255;
                            colc->blue = (coli.alpha * coli.blue + (255 - coli.alpha) * colc->blue) / 255;
                            colc->alpha = 255;
                        }
                    }
                }
            }
        }
    }
}

