/*
 * DrawTools.cpp
 * Source file implementation of procedural helper functions used to draw common
 * objects (textures, shapes, text) to the window using Dear ImGui conventions.
 */
#include "DrawTools.h"
#include "imgui.h"
#include <iomanip>
#include <vector>

#include "ColorTools.h"
#include "../ImVec2Operators.h"

#include "imgui_internal.h"
#include "PositionTools.h"
#include "Window.h"

namespace Draw {
    // Function:    Text
    // -----------------
    // Draws colored text to the screen of a set transparency
    //
    // string text:         text to be written to the screen
    // ImU32 color:         color of text
    // float transparency:  relative transparency of text
    // ImVec2 position:     coordinates of upper left of text box
    // ImFont font:         font style to be used
    // float fontSize:      point size of font
    void Text(std::string& text, ImU32 color, float transparency, ImVec2 position, ImFont* font, float fontSize)
    {
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        // Apply transparency to the input color
        ImU32 colorWithAlpha = (color & 0x00FFFFFF) | (ImU32)(transparency * 255.0f) << 24;

        // Draw the text
        drawList->AddText(
            font,
            fontSize,
            position,
            colorWithAlpha,
            text.c_str()
        );
    }

    // Function:    TextStroke
    // -----------------------
    // Radially redraws text to generate a stroke/outline effect
    //
    // string text:         text to be written to the scree
    // ImU32 strokeColor:   color of the stroke drawn around the displayed textn
    // float transparency:  relative transparency of stroke
    // float strokeWidth:   thickness of the stroke in pixels
    // ImVec2 position:     coordinates of upper left of text box
    // ImFont font:         font style to be used
    // float fontSize:      point size of font
    void TextStroke(std::string& text, ImU32 strokeColor, float transparency, float strokeWidth, ImVec2 position, ImFont* font, float fontSize)
    {
        constexpr int segments = 32;
        float step = 2.0f * IM_PI / segments;

        for (int i = 0; i < segments; ++i) {
            float angle = step * i;
            ImVec2 offset = ImVec2(cosf(angle), sinf(angle)) * strokeWidth;
            Text(text, strokeColor, transparency, position + offset, font, fontSize);
        }

    }

    // Function:    TextWithStroke
    // ---------------------------
    // Draws text with a stroke to produce an outlined-text effect
    //
    // string text:         text to be written to the scree
    // ImU32 strokeColor:   color of the stroke drawn around the displayed text
    // ImU32 textColor:     color of the text in the foreground
    // float transparency:  relative transparency of text
    // float strokeWidth:   thickness of the stroke in pixels
    // ImVec2 position:     coordinates of upper left of text box
    // ImFont font:         font style to be used
    // float fontSize:      point size of font
    void TextWithStroke(std::string& text, ImU32 strokeColor, ImU32 textColor, float transparency, float strokeWidth, ImVec2 position, ImFont* font, float fontSize)
    {
        TextStroke(text, strokeColor, transparency, strokeWidth, position, font, fontSize);
        Text(text, textColor, transparency, position, font, fontSize);
    }

    // Function:    SolidRectangle
    // ---------------------------
    // Draws a filled rectangle of a specific color and transparency at a specified position
    //
    // ImU32 color:             background color of the rectangle
    // float transparency:      opacity of the rectangle
    // ImVec2 position:         coordinates rectangle's upper left corner
    // ImVec2 rectangleSize:    size of rectangle to be drawn
    void FilledRectangle(ImU32 color, float transparency, ImVec2 position, ImVec2 rectangleSize)
    {
        // Pull Rendering Information
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        // Apply transparency to the input color
        ImU32 colorWithAlpha = color & 0x00FFFFFF; // mask out existing alpha
        colorWithAlpha |= (ImU32)(transparency * 255.0f) << 24; // insert new alpha

        // Draw background rectangle
        drawList->AddRectFilled(
            position,
            position + rectangleSize,
            colorWithAlpha
        );
    }

    // Function:    FilledRoundedRectangle
    // -----------------------------------
    // Draws a filled rounded rectangle of a specific color and transparency at a specified position
    //
    // ImU32 color:             background color of the rectangle
    // float transparency:      opacity of the rectangle
    // ImVec2 position:         coordinates rectangle's upper left corner
    // ImVec2 rectangleSize:    size of rectangle to be drawn
    // float rounding:          radius for corner rounding (in pixels)
    void FilledRoundedRectangle(ImU32 color, float transparency, ImVec2 position, ImVec2 rectangleSize, float rounding)
    {
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        // Apply transparency to the input color
        ImU32 colorWithAlpha = color & 0x00FFFFFF; // mask out existing alpha
        colorWithAlpha |= (ImU32)(transparency * 255.0f) << 24; // insert new alpha

        // Draw background rectangle with rounded corners
        drawList->AddRectFilled(
            position,
            position + rectangleSize,
            colorWithAlpha,
            rounding,
            ImDrawFlags_RoundCornersAll // round all corners
        );
    }

    // Function:    SolidRectangleWithStroke
    // -------------------------------------
    // Draws a filled rectangle with a stroke around it
    //
    // ImU32 color:             background color of the rectangle
    // ImU32 strokeColor:       color of stroke outline
    // float transparency:      opacity of the rectangle
    // ImVec2 position:         coordinates rectangle's upper left corner
    // ImVec2 rectangleSize:    size of rectangle to be drawn
    // float strokeWidth:       width of stroke outline in pixels
    void FilledRectangleWithStroke(ImU32 color, ImU32 strokeColor, float transparency, ImVec2 position, ImVec2 rectangleSize, float strokeWidth)
    {
        FilledRectangle(strokeColor, transparency, ImVec2(position.x - strokeWidth, position.y - strokeWidth), rectangleSize + ImVec2(strokeWidth * 2, strokeWidth *2));
        FilledRectangle(color, transparency, position, rectangleSize);
    }

    // Function:    Highlight
    // ----------------------
    // Draws a filled rectangle to serve as the outline for text in a particular font
    //
    // string text:             content of the drawn text
    // ImFont font:             font style
    // float width:             width of outer gap between outside of text box and inside of rectangle
    // ImU32 color:             color of highlight box
    // float transparency:      opacity of the highlight
    // ImVec2 position:         coordinates of text box's upper left corner
    // float fontSize:          size of the font
    void Highlight(std::string& text, ImFont* font, float width, ImU32 color, float transparency, ImVec2 position, float fontSize)
    {
        // Calculate text size for a specific font size
        //ImVec2 textSize = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, text.c_str());
        ImVec2 textSize = ImGui::CalcTextSize(text.c_str());

        // Determine size of rectangle
        ImVec2 highlightOffset = position - ImVec2(width, width);
        ImVec2 rectangleSize = textSize + ImVec2(2 * width, 2 * width);

        // Draw Background
        FilledRectangle(color, transparency, highlightOffset, rectangleSize);
    }

    // Function:    HighlightRounded
    // -----------------------------
    // Draws a filled rounded rectangle to serve as the outline for text in a particular font
    //
    // string text:             content of the drawn text
    // ImFont font:             font style
    // float width:             width of outer gap between outside of text box and inside of rectangle
    // ImU32 color:             color of highlight box
    // float transparency:      opacity of the highlight
    // ImVec2 position:         coordinates of text box's upper left corner
    // float fontSize:          size of the font
    // float rounding:          radius for corner rounding
    void HighlightRounded(std::string& text, ImFont* font, float width, ImU32 color, float transparency, ImVec2 position, float fontSize, float rounding)
    {
        // Calculate text size for the given font
        ImGui::PushFont(font);
        ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
        ImGui::PopFont();

        // Determine size of rectangle
        ImVec2 highlightOffset = position - ImVec2(width, width);
        ImVec2 rectangleSize   = textSize + ImVec2(2 * width, 2 * width);

        // Draw background highlight with rounded corners
        FilledRoundedRectangle(color, transparency, highlightOffset, rectangleSize, rounding);
    }

    // Function:    TextWithHighlight
    // ------------------------------
    // Draws text with a highlight box behind it
    //
    // string text:                 content of the drawn text
    // ImFont font:                 font style
    // float highlightWidth:        width of outer gap between outside of text box and inside of rectangle
    // ImU32 textColor:             color of text
    // ImU32 highlightColor:        color of the highlight
    // float textTransparency:      opacity of the text
    // float highlightTransparency: opacity of the highlight
    // ImVec2 position:             coordinates of text box's upper left corner
    // float fontSize:              size of the font
    void TextWithHighlight(std::string& text, ImFont* font, float highlightWidth, ImU32 textColor, ImU32 highlightColor, float textTransparency, float highlightTransparency, ImVec2 position, float fontSize)
    {
        Highlight(text, font, highlightWidth, highlightColor, highlightTransparency, position, fontSize);
        Text(text, textColor, textTransparency, position, font, fontSize);
    }

    // Function:    TextWithHighlightRounded
    // --------------------------------------
    // Draws text with a rounded highlight box behind it
    //
    // string text:                 content of the drawn text
    // ImFont font:                 font style
    // float highlightWidth:        width of outer gap between outside of text box and inside of rectangle
    // float rounding:              rounding radius for the highlight corners
    // ImU32 textColor:             color of text
    // ImU32 highlightColor:        color of the highlight
    // float textTransparency:      opacity of the text
    // float highlightTransparency: opacity of the highlight
    // ImVec2 position:             coordinates of text box's upper left corner
    // float fontSize:              size of the font
    void TextWithRoundedHighlight(std::string& text, ImFont* font, float highlightWidth, ImU32 textColor, ImU32 highlightColor, float textTransparency, float highlightTransparency, ImVec2 position, float fontSize, float rounding)
    {
        HighlightRounded(text, font, highlightWidth, highlightColor,highlightTransparency, position, fontSize, rounding);
        Text(text, textColor, textTransparency, position, font, fontSize);
    }


    // Function:    StrokedTextWithHighlight
    // -------------------------------------
    // Draws stroked text with a highlight box behind it
    //
    // string text:                 content of the drawn text
    // ImFont font:                 font style
    // float highlightWidth:        width of outer gap between outside of text box and inside of rectangle
    // float strokeWidth:           width of the stroke outline outside of the drawn text
    // ImU32 textColor:             color of text
    // ImU32 highlightColor:        color of the highlight
    // ImU32 strokeColor:           color of stroke outline
    // float textTransparency:      opacity of the text
    // float highlightTransparency: opacity of the highlight
    // ImVec2 position:             coordinates of text box's upper left corner
    // float fontSize:              size of the font
    void StrokedTextWithHighlight(std::string& text, ImFont* font, float highlightWidth, float strokeWidth, ImU32 textColor, ImU32 highlightColor, ImU32 strokeColor, float textTransparency, float highlightTransparency, ImVec2 position, float
                                  fontSize)
    {
        Highlight(text, font, highlightWidth, highlightColor, highlightTransparency, position, 0);
        TextWithStroke(text, strokeColor, textColor, textTransparency, strokeWidth, position, font, 0);
    }

    // Function:    BoxAround
    // ----------------------
    // Draws a rectangular outline around a provided set of coordinates of a set thickness
    //
    // ImVec2 size:                 size of the space being enclosed with a box
    // ImVec2 position:             coordinates to upper left corner of the space being enclosed
    // float width:                 width of the box in pixels
    // ImU32 color:                 color of the box
    // float transparency:          opacity of the box
    // float rounding:              filleting radius of the box edges
    // ImDrawFlags rectangleFlags:  ImGui-specific flags for rectangle formatting
    void BoxAround(ImVec2 size, ImVec2 position, float width, ImU32 color, float transparency, float rounding, ImDrawFlags rectangleFlags)
    {
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        // Apply transparency to the input color
        ImU32 colorWithAlpha = color & 0x00FFFFFF; // mask out existing alpha
        colorWithAlpha |= (ImU32)(transparency * 255.0f) << 24; // insert new alpha

        ImVec2 p_min = position - ImVec2(width, width);
        ImVec2 p_max = position + size + ImVec2(width, width);

        drawList->AddRect(p_min, p_max, colorWithAlpha, rounding, rectangleFlags, width);
    }

    // Function:    RoundedRectangleBehind
    // -----------------------------------
    // Draws a rounded rectangle around a provided set of coordinates of a set thickness
    //
    // ImVec2 size:                 size of the space being enclosed with a box
    // ImVec2 position:             coordinates to upper left corner of the space being enclosed
    // float width:                 width of the box in pixels
    // ImU32 color:                 color of the box
    // float transparency:          opacity of the box
    // float rounding:              filleting radius of the box edges
    // ImDrawFlags rectangleFlags:  ImGui-specific flags for rectangle formatting
    void RoundedRectangleBehind(ImVec2 size, ImVec2 position, float width, ImU32 color, float transparency, float rounding)
    {
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        // Apply transparency to the input color
        ImU32 colorWithAlpha = color & 0x00FFFFFF; // mask out existing alpha
        colorWithAlpha |= (ImU32)(transparency * 255.0f) << 24; // insert new alpha

        ImVec2 p_min = position - ImVec2(width, width);
        ImVec2 p_max = position + size + ImVec2(width, width);

        // Draw background rectangle with rounded corners
        drawList->AddRectFilled(
            p_min,
            p_max,
            colorWithAlpha,
            rounding,
            ImDrawFlags_RoundCornersAll // round all corners
        );
    }
    // Function:    BoxAroundWithStroke
    // --------------------------------
    // Draws a rectangular outline around a provided set of coordinates with a stroke outline
    //
    // ImVec2 size:                 size of the space being enclosed with a box
    // ImVec2 position:             coordinates to upper left corner of the space being enclosed
    // float width:                 width of the box in pixels
    // ImU32 color:                 color of the box
    // float transparency:          opacity of the box
    // float rounding:              filleting radius of the box edges
    // ImDrawFlags rectangleFlags:  ImGui-specific flags for rectangle formatting
    void BoxAroundWithStroke(ImVec2 size, ImVec2 offset, float width, ImU32 color, float strokeWidth, ImU32 strokeColor, float transparency, float rounding, ImDrawFlags rectangleFlags)
    {
        constexpr int segments = 32;
        float step = 2.0f * IM_PI / segments;

        for (int i = 0; i < segments; ++i) {
            float angle = step * i;
            ImVec2 strokeOffset = ImVec2(cosf(angle), sinf(angle)) * strokeWidth;
            BoxAround(size, offset + strokeOffset, width, strokeColor, transparency, rounding, rectangleFlags);
        }

        // Draw central rectangle
        BoxAround(
            size,
            offset,
            width,
            color,
            transparency,
            rounding,
            rectangleFlags
            );
    }

    // Function:        Sprite
    // -----------------------
    // Draws a texture 1:1 at a position with a set opacity
    //
    // Texture sprite:      a pre-rasterized texture
    // ImVec2 position:     coordinate location for upper-left-corner of the sprite
    // float transparency:  relative opacity of the rendered sprite
    void Sprite(TextureData sprite, ImVec2 position, float transparency)
    {
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        ImU32 tintColor = IM_COL32(255.0, 255.0, 255.0, transparency * 255.0);
        drawList->AddImage(
            (ImTextureID)(intptr_t)sprite.id,
            position,
            position + ImVec2(sprite.width, sprite.height),
                ImVec2(0.0f, 0.0f),
                ImVec2(1.0f, 1.0f),
                tintColor
                );

    }

    // Function:        TintedSprite
    // -----------------------------
    // Draws a sprite with a colored tint
    //
    // TextureData sprite:      a pre-rasterized texture
    // ImVec2 position:         coordinate location for upper-left-corner of the sprite
    // ImU32 tintColor:         Color of the tint
    // float transparency:      relative opacity of the rendered sprite
    void TintedSprite(TextureData sprite, ImVec2 position, ImU32 tintColor, float transparency)
    {
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        ImU32 colorWithAlpha = Color::WithAlpha(tintColor, transparency); // mask out existing alpha

        drawList->AddImage(
            (ImTextureID)(intptr_t)sprite.id,
            position,
            position + ImVec2(sprite.width, sprite.height),
                ImVec2(0.0f, 0.0f),
                ImVec2(1.0f, 1.0f),
                colorWithAlpha
                );
    }



    // Function:        SpriteSubsection
    // ---------------------------------
    // Draws a cross-section of a sprite from a particular starting fraction to an end fraction
    // The cross-section is positioned such that if the undivided sprite was rendered underneath,
    // the subsected sprite will align with its relative position within the undivided sprite
    // Used to draw active subsections of status indicator bars
    //
    // Texture sprite:      a pre-rasterized texture
    // ImVec2 position:     coordinate location for upper-left-corner of the sprite prior to subsection
    // float transparency:  relative opacity of the rendered sprite
    void SpriteSubsection(TextureData sprite, ImVec2 position, ImVec2 startFraction, ImVec2 endFraction)
    {
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        ImVec2 spriteSize(sprite.width, sprite.height);

        ImVec2 topLeft = position + ImVec2(startFraction.x * spriteSize.x, startFraction.y * spriteSize.y);
        ImVec2 bottomRight = position + ImVec2(endFraction.x * spriteSize.x, endFraction.y * spriteSize.y);

        drawList->AddImage(
            (ImTextureID)(intptr_t)sprite.id,
            topLeft,        // Screen-space top-left
            bottomRight,    // Screen-space bottom-right
            startFraction,  // UV start
            endFraction,    // UV end
            IM_COL32_WHITE
        );
    }

    // Function:        Image
    // ----------------------
    // Renders a sprite to scale into fixed dimensions at a set zoom level
    // This function is akin to adding and cropping an image into a document
    // The image is cropped to a specific zoom level and then scaled to a particular frame size
    //
    // Texture sprite:      a pre-rasterized texture
    // ImVec2 position:     coordinate location for upper-left-corner of the sprite
    // ImVec2 frameSize:    the size of the image as it is displayed
    // float scale:         zoom level
    void Image(TextureData sprite, ImVec2 position, ImVec2 frameSize, float scale)
    {
        float trueScale = std::pow(2.0f, scale * 4.0f); // Exponential scaling for even zoom
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        ImVec2 topLeft = position;
        ImVec2 bottomRight = position + frameSize;
        scale = ImClamp(trueScale, 1.001f, 100.0f);

        float margin = (1.0f - 1.0f / scale) / 2.0f; // normalized margin around the center

        ImVec2 startFraction = ImVec2(margin, margin);
        ImVec2 endFraction = ImVec2(1.0f - margin, 1.0f - margin);

        drawList->AddImage(
            (ImTextureID)(intptr_t)sprite.id,
            topLeft,
            bottomRight,
            startFraction,
            endFraction,
            IM_COL32_WHITE);
    }


    // Function:    Crop
    // -----------------
    // Renders a cropped subsection of an image within a specific frame
    void Crop(TextureData sprite, ImVec2 position, ImVec2 cropPosition, ImVec2 cropSize, ImVec2 frameSize)
    {
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        ImVec2 topLeft = position;
        ImVec2 bottomRight = position + frameSize;

        ImVec2 startFraction = ImVec2(cropPosition.x / sprite.width, cropPosition.y / sprite.height);
        ImVec2 endFraction = ImVec2((cropPosition.x + cropSize.x) / sprite.width,
                                    (cropPosition.y + cropSize.y) / sprite.height);  // Fixed!

        drawList->AddImage(
            (ImTextureID)(intptr_t)sprite.id,
            topLeft,
            bottomRight,
            startFraction,
            endFraction,
            IM_COL32_WHITE);
    }

    // Function:        RoundedImage
    // -----------------------------
    // Renders an image with rounded edges
    //
    // Texture sprite:      a pre-rasterized texture
    // ImVec2 position:     coordinate location for upper-left-corner of the sprite
    // ImVec2 frameSize:    the size of the image as it is displayed
    // float scale:         zoom level
    // float rouding:       the rounding radius of the corners
    void RoundedImage(TextureData sprite, ImVec2 position, ImVec2 frameSize, float scale, float rounding)
    {
        float trueScale = std::pow(2.0f, scale * 4.0f);
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        ImVec2 topLeft = position;
        ImVec2 bottomRight = position + frameSize;
        scale = ImClamp(trueScale, 1.001f, 100.0f);

        float margin = (1.0f - 1.0f / scale) / 2.0f;

        ImVec2 startFraction = ImVec2(margin, margin);
        ImVec2 endFraction   = ImVec2(1.0f - margin, 1.0f - margin);

        drawList->AddImageRounded(
            (ImTextureID)(intptr_t)sprite.id,
            topLeft,
            bottomRight,
            startFraction,
            endFraction,
            IM_COL32_WHITE,
            rounding  // radius for rounded corners
        );
    }
    // Function:        Grid
    // ---------------------
    // Generates an empty grid divided by solid rectangular gridlines
    // Gridlines divide each cell into rows and columns, as well as produce a border around the canvas
    // This is used to generate gallery displays
    //
    // ImVec2 origin:       coordinates of upper left corner of the canvas
    // int columns:         number of columns in the grid
    // int rows:            number of rows
    // float cellWidth:     width of each cell in pixels
    // float cellHeight:    height of each cell in pixels
    // float gridlineWidth: thickness of the gridlines in pixels
    // ImU32 gridlineColor: gridline color
    void Grid(ImVec2 origin, int columns, int rows, float cellWidth, float cellHeight, float gridlineWidth, ImU32 gridlineColor)
    {
        float documentWidth = (columns + 1) * gridlineWidth + cellWidth * columns;
        float documentHeight = (rows + 1) * gridlineWidth + cellHeight * rows;

        // Dimensions of individual gridlines
        ImVec2 horizontalGridlineSize = ImVec2(documentWidth, gridlineWidth);
        ImVec2 verticalGridlineSize = ImVec2(gridlineWidth, documentHeight);

        float horizontalCellDisplacement = cellWidth + gridlineWidth;
        float verticalCellDisplacement = cellHeight + gridlineWidth;

        // Draw the vertical gridlines
        for (int currentColumn = 0; currentColumn <= columns; currentColumn++)
        {
            ImVec2 anchor = origin + ImVec2(horizontalCellDisplacement * currentColumn, 0);
            FilledRectangle(gridlineColor, 1.0f, anchor, verticalGridlineSize);
        }

        // Draw the horizontal gridlines
        for (int currentRow = 0; currentRow <= rows; currentRow++)
        {
            ImVec2 anchor = origin + ImVec2(0, verticalCellDisplacement * currentRow);
            FilledRectangle(gridlineColor, 1.0f, anchor, horizontalGridlineSize);
        }
    }

    // Function:        PopulateGrid
    // -----------------------------
    // Scales and positions each image within a vector into a grid configuration
    // Takes a collection of textures and fills the grid up to the capacity of the vector
    // If the size of the grid exceeds the number of textures in the vector, the remaining cells are left empty
    // The gaps between the cells are indicated by the gridline thickness
    //
    // vector images:       textures used to populate the grid
    // ImVec2 origin:       coordinates of upper left corner of the canvas
    // int columns:         number of columns in the grid
    // int rows:            number of rows
    // float cellWidth:     width of each cell in pixels
    // float cellHeight:    height of each cell in pixels
    // float gridlineWidth: thickness of the gridlines in pixels
    void PopulateGrid(std::vector<TextureData> images, ImVec2 origin, int columns, int rows, float cellWidth, float cellHeight, float gridlineWidth)
    {
        origin = origin + ImVec2(gridlineWidth, gridlineWidth);

        float horizontalCellDisplacement = cellWidth + gridlineWidth;
        float verticalCellDisplacement = cellHeight + gridlineWidth;

        ImVec2 cellFrameSize = ImVec2(cellWidth, cellHeight);
        int imageCount = images.size();
        int cellIndex = 0;

        for (int currentRow = 0; currentRow < rows; currentRow++)
        {
            for (int currentColumn = 0; currentColumn < columns; currentColumn++)
            {
                if (cellIndex >= imageCount)
                    return;

                ImVec2 anchor = origin + ImVec2(currentColumn * horizontalCellDisplacement, currentRow * verticalCellDisplacement);
                Image(images[currentRow * columns + currentColumn], anchor, cellFrameSize, 0.0f);

                cellIndex++;
            }
        }
    }

    // Function:        PopulateGrid
    // -----------------------------
    // Scales and positions each image within a vector into a grid configuration
    // Takes a collection of textures and fills the grid up to the capacity of the vector
    // If the size of the grid exceeds the number of textures in the vector, the remaining cells are left empty
    // The gaps between the cells are indicated by the gridline thickness
    //
    // vector images:       textures used to populate the grid
    // ImVec2 origin:       coordinates of upper left corner of the canvas
    // int columns:         number of columns in the grid
    // int rows:            number of rows
    // float cellWidth:     width of each cell in pixels
    // float cellHeight:    height of each cell in pixels
    // float gridlineWidth: thickness of the gridlines in pixels
    void PopulateSparseRoundedGrid(std::vector<TextureData> images, ImVec2 origin, int columns, int rows, float cellWidth, float cellHeight, float spacing, float rounding)
    {
        origin = origin + ImVec2(spacing, spacing);

        float horizontalCellDisplacement = cellWidth + spacing;
        float verticalCellDisplacement = cellHeight + spacing;

        ImVec2 cellFrameSize = ImVec2(cellWidth, cellHeight);
        int imageCount = images.size();
        int cellIndex = 0;

        for (int currentRow = 0; currentRow < rows; currentRow++)
        {
            for (int currentColumn = 0; currentColumn < columns; currentColumn++)
            {
                if (cellIndex >= imageCount)
                    return;

                ImVec2 anchor = origin + ImVec2(currentColumn * horizontalCellDisplacement, currentRow * verticalCellDisplacement);
                RoundedImage(images[currentRow * columns + currentColumn], anchor, cellFrameSize, 0.0f, rounding);
                cellIndex++;
            }
        }
    }

    // Function:        PopulateGrid
    // -----------------------------
    // Scales and positions each image within a vector into a grid configuration
    // Takes a collection of textures and fills the grid up to the capacity of the vector
    // If the size of the grid exceeds the number of textures in the vector, the remaining cells are left empty
    // The gaps between the cells are indicated by the gridline thickness
    //
    // vector images:       textures used to populate the grid
    // ImVec2 origin:       coordinates of upper left corner of the canvas
    // int columns:         number of columns in the grid
    // int rows:            number of rows
    // float cellWidth:     width of each cell in pixels
    // float cellHeight:    height of each cell in pixels
    // float gridlineWidth: thickness of the gridlines in pixels
    void PopulateSparseRoundedGridWithDates(std::vector<TextureData> images, ImVec2 origin, int columns, int rows, float cellWidth, float cellHeight, float spacing, float rounding, std::vector<std::string> dates, ImFont* font, bool& exitSelected)
    {
        origin = origin + ImVec2(spacing, spacing);

        float horizontalCellDisplacement = cellWidth + spacing;
        float verticalCellDisplacement = cellHeight + spacing;

        ImVec2 cellFrameSize = ImVec2(cellWidth, cellHeight);
        int imageCount = images.size();
        int cellIndex = 0;

        for (int currentRow = 0; currentRow < rows; currentRow++)
        {
            for (int currentColumn = 0; currentColumn < columns; currentColumn++)
            {
                if (cellIndex >= imageCount)
                    return;

                int currentIndex = currentRow * columns + currentColumn;

                // Draw the font
                ImVec2 anchor = origin + ImVec2(currentColumn * horizontalCellDisplacement, currentRow * verticalCellDisplacement);

                // If the date indicates that the cell represents a screenshot
                if (dates[currentIndex] != "")
                {
                    Draw::RoundedImage(images[currentIndex], anchor, cellFrameSize, 0.0f, rounding);

                    ImGui::PushFont(font);
                    ImVec2 fontSize = ImGui::CalcTextSize(dates[currentIndex].c_str());
                    ImVec2 fontPosition = Position::InnerAlignBottomLeft(anchor, cellFrameSize, fontSize, DEFAULT_GRAPHICS_GAP);

                    TextWithRoundedHighlight(dates[currentIndex], font, DEFAULT_HIGHLIGHT_WIDTH, DEFAULT_FONT_COLOR, IM_COL32_WHITE, 1.0f, 1.0f, fontPosition, 0.0f, DEFAULT_WINDOW_ROUNDING);
                    ImGui::PopFont();
                }
                // If the cell represents an icon
                else
                {
                    ImVec2 iconSize = ImVec2(images[currentIndex].width, images[currentIndex].height);
                    ImVec2 iconPosition = Position::Center2D(
                        anchor,
                        cellFrameSize,
                        iconSize);

                    if (exitSelected)
                        Draw::Sprite(images[currentIndex], iconPosition);
                    else
                        Draw::TintedSprite(images[currentIndex], iconPosition, Color::RGBtoImU32(DEFAULT_UNSELECTED_ACTIVE_COLOR, 1.0f));
                }

                cellIndex++;
            }
        }
    }
} // Draw