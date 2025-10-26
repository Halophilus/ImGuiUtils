/*
 * DrawTools.h
 * Ben Henshaw
 * Header of procedural helper functions used to draw common
 * objects (textures, shapes, text) to the window using Dear ImGui conventions.
 */
#ifndef DRAWTOOLS_H
#define DRAWTOOLS_H
#include <string>
#include <vector>

#include "imgui.h"
#include "TextureTools.h"

namespace Draw {

    // Draws text to the screen
    void Text(std::string& text, ImU32 color, float transparency, ImVec2 position, ImFont* font, float fontSize = 0.0f);

    // Draws a stroke for a supplied sample of text
    void TextStroke(std::string& text, ImU32 strokeColor, float transparency, float strokeWidth, ImVec2 position, ImFont* font, float fontSize = 0.0f);

    // Draws text with a stroke around it
    void TextWithStroke(std::string& text, ImU32 strokeColor, ImU32 textColor, float transparency, float strokeWidth, ImVec2 position, ImFont* font, float fontSize = 0.0f);

    // Draws a filled rectangle
    void FilledRectangle(ImU32 color, float transparency, ImVec2 position, ImVec2 rectangleSize);

    // Draws a filled rectangle with rounded corners
    void FilledRoundedRectangle(ImU32 color, float transparency, ImVec2 position, ImVec2 rectangleSize, float rounding);

    // Draws a filled rectangle with a stroke around it
    void FilledRectangleWithStroke(ImU32 color, ImU32 strokeColor, float transparency, ImVec2 position, ImVec2 rectangleSize, float strokeWidth);

    // Draws a filled rectangle based on the size of a text draw
    void Highlight(std::string& text, ImFont* font, float width, ImU32 color, float transparency, ImVec2 position, float fontSize = 0.0f);

    // Draws a rounded filled rectangle behind text
    void HighlightRounded(std::string& text, ImFont* font, float width, ImU32 color, float transparency, ImVec2 position, float fontSize = 0.0f, float rounding = 0.0f);

    // Draws text with highlight behind it
    void TextWithHighlight(std::string& text, ImFont* font, float highlightWidth, ImU32 textColor, ImU32 highlightColor, float textTransparency, float highlightTransparency, ImVec2 position, float fontSize = 0.0f);

    // Draws text with a rounded highlight behind it
    void TextWithRoundedHighlight(std::string& text, ImFont* font, float highlightWidth, ImU32 textColor, ImU32 highlightColor, float textTransparency, float highlightTransparency, ImVec2 position, float fontSize, float rounding);

    // Draws stroked text with highlight behind it
    void StrokedTextWithHighlight(std::string& text, ImFont* font, float highlightWidth, float strokeWidth, ImU32 textColor, ImU32 highlightColor, ImU32 strokeColor, float textTransparency, float highlightTransparency, ImVec2 position, float fontSize = 0.0f);

    // Draws a box around a given dimensional vector
    void BoxAround(ImVec2 size, ImVec2 position, float width, ImU32 color, float transparency, float rounding, ImDrawFlags rectangleFlags = 0);

    // Draws a rounded rectangle behind an object
    void RoundedRectangleBehind(ImVec2 size, ImVec2 position, float width, ImU32 color, float transparency, float rounding);

    // Draws a box with a stroke around it
    void BoxAroundWithStroke(ImVec2 size, ImVec2 offset, float width, ImU32 color, float strokeWidth, ImU32 strokeColor, float transparency, float rounding, ImDrawFlags rectangleFlags = 0);

    // Draws a sprite 1:1 at a certain position
    void Sprite(TextureData spriteTexture, ImVec2 position, float transparency = 1.0);

    // Draws a sprite, but with a colored tint
    void TintedSprite(TextureData spriteTexture, ImVec2 position, ImU32 tintColor, float transparency = 1.0);

    // Draws a subsection of a sprite offset to where it would fall on the undivided texture
    void SpriteSubsection(TextureData sprite, ImVec2 position, ImVec2 startFraction, ImVec2 endFraction);

    // Draws an image at a certain location within a fixed frame at a certain zoom/scale level
    void Image(TextureData sprite, ImVec2 position, ImVec2 frameSize, float scale);

    // Draws a subsection of an image
    void Crop(TextureData sprite, ImVec2 position, ImVec2 cropPosition, ImVec2 cropSize, ImVec2 frameSize);

    // Draws an image with rounded edges
    void RoundedImage(TextureData sprite, ImVec2 position, ImVec2 frameSize, float scale, float rounding);

    // Draws an empty grid
    void Grid(ImVec2 origin, int columns, int rows, float cellWidth, float cellHeight, float gridlineWidth, ImU32 gridlineColor);

    // Fills a grid with the contents of a vector of textures
    void PopulateGrid(std::vector<TextureData> images, ImVec2 origin, int columns, int rows, float cellWidth, float cellHeight, float gridlineWidth);

    // Creates a spaced-out grid of rounded images
    void PopulateSparseRoundedGrid(std::vector<TextureData> images, ImVec2 origin, int columns, int rows, float cellWidth, float cellHeight, float spacing, float rounding);

    // Creates spaced-out grid with dates in the bottom left corner
    void PopulateSparseRoundedGridWithDates(std::vector<TextureData> images, ImVec2 origin, int columns, int rows, float cellWidth, float cellHeight, float spacing, float rounding, std::vector<std::string> dates, ImFont* font, bool& exitSelected);

} // Draw

#endif //DRAWTOOLS_H
