/*
 * Window.cpp / Aureon 2D graphical user interface
 *
 * Ben Henshaw / Spatial Surgical, LLC.
 * 8/12/2025
 *
 * Source file implementation of abstract parent Window class
 * Includes logic for scaling images in debug mode
 */

#include "Window.h"

// Instantiates the window and generates dimension and position vectors
Window::Window(const std::string& t,
               float dWidth,
               float dHeight,
               float posX,
               float posY)
        : title(t),
        designedWidth(dWidth),
        designedHeight(dHeight),
        designedPositionX(posX),
        designedPositionY(posY),
        width(dWidth),
        height(dHeight)
{
    this->dimensions = ImVec2(width, height);
    this->position = ImVec2(posX, posY);
}

// Accessors
float Window::getWidth() const { return this->width; }
float Window::getHeight() const { return this->height; }
float Window::getScaleX() const { return this->scaleX; }
float Window::getScaleY() const { return this->scaleY; }
float Window::getScaleAvg() const { return this->scaleAvg; }
ImVec4 Window::getBackgroundColor() const { return this->backgroundColor; }

// Mutators
void Window::setBackgroundColor(const ImVec4& color) { this->backgroundColor = color; }
void Window::setBackgroundVisibility(bool visible) { this->hasBackground = visible; }

// Used to update scaling variables in debug mode
void Window::updateScale()
{
    // Grab the main viewport and pull its dimensions
    const ImGuiViewport* mainViewport = ImGui::GetMainViewport();
    const float viewportWidth = mainViewport->WorkSize.x;
    const float viewportHeight = mainViewport->WorkSize.y;

    // Flag to assess recalculation of scaling parameters
    bool altered = false;

    if (viewportWidth != previousViewportWidth)
    {
        scaleX = viewportWidth / DEFAULT_VIEWPORT_WIDTH;
        previousViewportWidth = viewportWidth;
        altered = true;
    }

    if (viewportHeight != previousViewportHeight)
    {
        scaleY = viewportHeight / DEFAULT_VIEWPORT_HEIGHT;
        previousViewportHeight = viewportHeight;
        altered = true;
    }

    // Update internal scaling parameters if either scales have been altered
    if (altered)
    {
        // Update average scale
        scaleAvg = (scaleX + scaleY) * 0.5f;

        // Update absolute height and width
        dimensions = ImVec2(designedWidth * scaleX, designedHeight * scaleY);
        position = ImVec2(designedPositionX * scaleX, designedPositionY * scaleY);
    }

}

// Lifecycle functions
// Initializes window parameters and begins ImGui window
void Window::buildStart()
{
#ifdef DEBUG
    // Allow scaling behavior if the GUI is in debug mode
    updateScale();
#endif
    // Flag the window as having no background if indicated by window params
    ImGuiWindowFlags currentFlags = this->flags;
    if (!this->hasBackground) currentFlags |= ImGuiWindowFlags_NoBackground;
    // Otherwise, push the background color to the rendering stack
    else ImGui::PushStyleColor(ImGuiCol_WindowBg, this->backgroundColor);

    // Specify position and dimensions
    ImGui::SetNextWindowPos(this->position, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(this->dimensions, ImGuiCond_FirstUseEver);

    // Open window with previously-defined options
    ImGui::Begin(this->title.c_str(), NULL, currentFlags);
    if (this->hasBackground) ImGui::PopStyleColor();
}

// Ends window in ImGui rendering stack
void Window::buildEnd()
{
    ImGui::End();
}

// Standard rendering lifecycle for a window
void Window::render()
{
    // Update time
    this->currentTime = ImGui::GetTime();

    this->buildStart();
    this->draw();
    this->buildEnd();
}