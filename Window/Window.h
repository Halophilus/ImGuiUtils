/*
 * Window.h / Aureon 2D graphical user interface
 *
 * Ben Henshaw / Spatial Surgical, LLC.
 * 8/12/2025
 *
 * Header for abstract parent class encapsulating Dear ImGui window behavior
 * The final version of this script will have a fixed viewport size (3840 × 2160)
 * Debug mode will permit resizing of the main viewport.
 */

#pragma once
#ifndef WINDOW_H
#define WINDOW_H
#include "imgui.h"
#include "ColorTools.h"
#include <string>

// Default value macros
#define DEFAULT_BG Color::RGBtoImVec4(40, 40, 40, 1.0f)
#define DEFAULT_SELECTION_HIGHLIGHT_COLOR 139, 198, 63
#define DEFAULT_UNSELECTED_ACTIVE_COLOR 9, 174, 214
#define DEFAULT_INERT_SELECTION_OR_FONT_COLOR 144, 146, 148
#define DEFAULT_VIEWPORT_WIDTH 3840.0f
#define DEFAULT_VIEWPORT_HEIGHT 2160.0f

// Style headers
#define DEFAULT_STROKE_WIDTH 2.0f
#define DEFAULT_FONT_COLOR Color::RGBtoImU32(DEFAULT_INERT_SELECTION_OR_FONT_COLOR, 1.0f)
#define DEFAULT_STROKE_COLOR IM_COL32_BLACK
#define DEFAULT_HIGHLIGHT_COLOR DEFAULT_BG;
#define DEFAULT_HIGHLIGHT_WIDTH 8.0f
#define DEFAULT_TOOLBAR_WIDTH 247.0f
#define DEFAULT_DUMMY_SIZE ImVec2(0, 0)
#define DEFAULT_GRAPHICS_GAP 32.0f // The set distance between related graphics
#define DEFAULT_WINDOW_ROUNDING 48.0f // Radius of rounded corners on windows

class Window {
protected:
    // Title of window (not displayed by default)
    std::string title;

    // Dimensions of the window in native mode
    // Native viewport: 4K, (3840 × 2160)
    float designedWidth;
    float designedHeight;

    // Position
    float designedPositionX;
    float designedPositionY;

    // Instantaneous dimensions and position subject to relative scaling
    float width;
    float height;
    ImVec2 dimensions;
    ImVec2 position;

    // Internal scaling variables, 1.0f by default
    float scaleX = 1.0f;   // Current width : designed width
    float scaleY = 1.0f;   // Current height : designed height
    float scaleAvg = 1.0f; // Arithmetic mean of X and Y scales
    float previousViewportWidth = DEFAULT_VIEWPORT_WIDTH;
    float previousViewportHeight = DEFAULT_VIEWPORT_HEIGHT;

    // ImGui values
    float currentTime = 0.0f;

    // Background parameters
    bool hasBackground = true; // Visible by default for contrast
    ImVec4 backgroundColor = DEFAULT_BG;
    ImGuiWindowFlags flags = 0;

    // Internal helper functions
    virtual void updateScale();

    // Internal lifecycle functions
    virtual void buildStart();  // Initializes window

    virtual void buildEnd();    // Handles ImGui display stack logic

public:
    virtual void draw() = 0;    // Draws content
    // Default constructor
    Window(const std::string& title,
        float designedWidth,
        float designedHeight,
        float posX,
        float posY);

    // Virtual destructor
    virtual ~Window() = default;

    // Width
    float getWidth() const; // Current width of the window as it appears on the viewport
    float getScaleX() const;

    // Height
    float getHeight() const;
    float getScaleY() const;
    float getScaleAvg() const;

    // Background
    ImVec4 getBackgroundColor() const;
    void setBackgroundColor(const ImVec4& color);
    void setBackgroundVisibility(bool visible);

    // Lifecycle functions
    virtual void render();      // Calls all the internal lifecycle functions
    virtual void init() = 0;    // Initializes any context-specific variables
    virtual void reset() = 0;   // Resets window data to system defaults
};



#endif //WINDOW_H
