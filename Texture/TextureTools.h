/*
 * TextureLoader.cpp
 * Ben Henshaw
 * 7/23/2025
 *
 * Header file of a simple procedural texture loading utility that loads
 * image files into OpenGL textures. It supports reading from both files and in-memory
 * buffers using the stb_image library. It automatically converts images to RGBA, creates
 * an OpenGL texture object with common filtering settings, uploads the pixel data,
 * and returns a Texture struct containing the texture ID and dimensions.
 */
#pragma once
#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#include <string>
#include <GL/gl.h>

// Structure:   Texture
// --------------------
// Represents a texture, sprite, or image; used by DrawTools to draw
// pre-rasterized images to an ImGui canvas
//
// GLuint id:   pointer to texture in GPU memory
// int width:   width of the texture in pixels
// in height:   height of the texture in pixels
struct TextureData
{
    GLuint id = 0;
    int width = 0;
    int height = 0;
};

namespace Texture
{
    // Load a Texture from a .png image's filepath
    TextureData Load(const std::string& path);
}

#endif //TEXTURELOADER_H
