# ImGuiUtils

A C++ utility library for Dear ImGui that simplifies common rendering, positioning, color manipulation, and texture loading tasks.
## Overview

ImGuiUtils is a collection of procedural helper functions organized into distinct namespaces that streamline ImGui development. The library provides high-level abstractions for drawing operations, color interpolation, object positioning, texture management, and vector mathematics.

**Author:** Ben Henshaw  
**Created:** July 2025

## Features

### DrawTools
Procedural drawing functions for rendering common UI elements:
- **Text Rendering:** Basic text, stroked text, and text with highlights
- **Shapes:** Filled rectangles, rounded rectangles, and stroked variants
- **Sprites & Images:** 1:1 sprite rendering, tinted sprites, subsections, cropping, and rounded images
- **Grids:** Empty grids, populated grids, and sparse rounded grids with optional date labels
- **Decorations:** Boxes, strokes, and highlights with customizable styling

### ColorTools
Color manipulation and interpolation utilities:
- Linear interpolation (lerp) between two RGBA colors
- RGB color interpolation returning both `ImVec4` and `ImU32` formats
- Pulsing color effects over time
- Alpha channel manipulation for existing colors
- Color format conversions (RGB → ImVec4, ImU32)

### PositionTools
Comprehensive positioning system for UI element alignment:
- **Document Alignment:** Left, right, and center alignment with line-based positioning
- **Outer Alignment:** Position objects relative to other objects' edges (top, bottom, sides)
- **Inner Alignment:** Overlay objects within containers (corners, centers, edges)
- **Grid Alignment:** Calculate cell positions in grid layouts
- **Frame Utilities:** Calculate nested frame dimensions with padding

### TextureLoader
Simple OpenGL texture loading system:
- Load PNG images from file paths
- Automatic RGBA conversion
- OpenGL texture object creation with standard filtering
- `TextureData` struct containing texture ID and dimensions

### ImVec2Operators
Mathematical operator overloads for `ImVec2`:
- **Addition (`+`):** Vector translation
- **Subtraction (`-`):** Relative positioning
- **Multiplication (`*`):** Scalar scaling
- **Division (`/`):** Inverse scaling

## Installation

1. Copy all header files to your project's include directory
2. Ensure Dear ImGui is properly integrated into your project
3. Link OpenGL (required for TextureLoader)
4. Include stb_image library (required for TextureLoader)

```cpp
#include "DrawTools.h"
#include "ColorTools.h"
#include "PositionTools.h"
#include "TextureLoader.h"
#include "ImVec2Operators.h"
```

## Usage Examples

### Drawing Text with Effects
```cpp
std::string text = "Hello ImGui!";
ImVec2 pos = {100.0f, 100.0f};

// Simple text
Draw::Text(text, IM_COL32(255, 255, 255, 255), 1.0f, pos, font);

// Text with stroke
Draw::TextWithStroke(text, IM_COL32(0, 0, 0, 255), IM_COL32(255, 255, 255, 255), 
                     1.0f, 2.0f, pos, font);

// Text with rounded highlight
Draw::TextWithRoundedHighlight(text, font, 10.0f, 
                               IM_COL32(255, 255, 255, 255), 
                               IM_COL32(50, 50, 200, 255), 
                               1.0f, 0.8f, pos, 18.0f, 5.0f);
```

### Color Interpolation
```cpp
// Interpolate between two colors
ImVec4 color = Color::LerpRGBA(startColor, endColor, 0.5f);

// Get interpolated color as ImU32
ImU32 gradientColor = Color::GetInterpolatedColorU32(0.75f, 
                                                     255, 0, 0,    // Start RGB
                                                     0, 0, 255);   // End RGB

// Pulsing effect
ImU32 pulse = Color::PulseColor(255, 0, 0, 0, 255, 0, 2.0f);
```

### Positioning Objects
```cpp
ImVec2 origin = {50.0f, 50.0f};
ImVec2 objectSize = {200.0f, 100.0f};

// Center align in document
ImVec2 centered = Position::CenterAlign(origin, 800.0f, 20.0f, 5, objectSize);

// Position to the right of another object
ImVec2 rightSide = Position::TopAlignOnRightSide(targetPos, targetSize, 10.0f);

// Inner alignment (bottom-right corner with gap)
ImVec2 corner = Position::InnerAlignBottomRight(containerPos, containerSize, 
                                                objectSize, 10.0f);
```

### Loading and Drawing Textures
```cpp
// Load texture
TextureData sprite = Texture::Load("path/to/image.png");

// Draw sprite
Draw::Sprite(sprite, {100.0f, 100.0f}, 1.0f);

// Draw tinted sprite
Draw::TintedSprite(sprite, {200.0f, 200.0f}, IM_COL32(255, 128, 128, 255));

// Draw rounded image
Draw::RoundedImage(sprite, {300.0f, 300.0f}, {150.0f, 150.0f}, 1.0f, 10.0f);
```

### Vector Mathematics
```cpp
ImVec2 pos = {100.0f, 100.0f};
ImVec2 offset = {50.0f, 25.0f};

ImVec2 newPos = pos + offset;           // Translation
ImVec2 scaled = pos * 2.0f;             // Scaling
ImVec2 halfSize = pos / 2.0f;           // Division
ImVec2 relative = newPos - pos;         // Relative vector
```

## API Structure

All functions are organized into namespaces matching their header files:
- `Draw::` - Drawing operations
- `Color::` - Color utilities
- `Position::` - Positioning calculations
- `Texture::` - Texture loading

## Dependencies

- **Dear ImGui** - Core GUI library
- **OpenGL** - Graphics API (for texture management)
- **stb_image** - Image loading library

## License

This is a personal utility library. Please verify licensing terms with the author before use in commercial projects.

---

**Note:** This library assumes familiarity with Dear ImGui's coordinate system and rendering paradigm. All positions use screen-space coordinates with origin at the top-left corner.
