/*
 * TextureLoader.cpp
 * Ben Henshaw
 * 7/23/2025
 * Source file implementation of a simple procedural texture loading utility that loads
 * image files into OpenGL textures. It supports reading from both files and in-memory
 * buffers using the stb_image library. It automatically converts images to RGBA, creates
 * an OpenGL texture object with common filtering settings, uploads the pixel data,
 * and returns a Texture struct containing the texture ID and dimensions.
 */
#include "TextureTools.h"
#include "imgui.h"
#include "stb_image.h"
#include <iostream>

namespace Texture
{
    // Helper Function:    LoadTextureFromMemory
    // -----------------------------------------
    // Loads an image from a block of memory into an OpenGL texture for rendering.
    //
    // const void* data:     pointer to the raw image data in memory
    // size_t data_size:     size of the image data in bytes
    // GLuint* out_texture:  pointer to store the generated OpenGL texture ID
    // int* out_width:       pointer to store the loaded image's width in pixels
    // int* out_height:      pointer to store the loaded image's height in pixels
    //
    // Returns true if the image was successfully loaded and converted into a texture, false otherwise.
    bool LoadTextureFromMemory(const void* data, size_t data_size, GLuint* out_texture, int* out_width, int* out_height)
    {
        // Load from file
        int image_width = 0;
        int image_height = 0;
        unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, NULL, 4);
        if (image_data == NULL)
            return false;

        // Create a OpenGL texture identifier
        GLuint image_texture;
        glGenTextures(1, &image_texture);
        glBindTexture(GL_TEXTURE_2D, image_texture);

        // Setup filtering parameters for display
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Upload pixels into texture
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
        stbi_image_free(image_data);

        *out_texture = image_texture;
        *out_width = image_width;
        *out_height = image_height;

        return true;
    }

    // Helper Function:    LoadTextureFromFile
    // ---------------------------------------
    // Loads an image from a file on disk into an OpenGL texture for rendering.
    //
    // const char* file_name:  path to the image file to load
    // GLuint* out_texture:    pointer to store the generated OpenGL texture ID
    // int* out_width:         pointer to store the loaded image's width in pixels
    // int* out_height:        pointer to store the loaded image's height in pixels
    //
    // Reads the file into memory, then calls LoadTextureFromMemory() to decode and
    // create the texture. Frees the file data after texture creation.
    //
    // Returns true if the image was successfully loaded and converted into a texture, false otherwise.
    bool LoadTextureFromFile(const char* file_name, GLuint* out_texture, int* out_width, int* out_height)
    {
        FILE* f = fopen(file_name, "rb");
        if (f == NULL)
            return false;
        fseek(f, 0, SEEK_END);
        size_t file_size = (size_t)ftell(f);
        if (file_size == -1)
            return false;
        fseek(f, 0, SEEK_SET);
        void* file_data = IM_ALLOC(file_size);
        fread(file_data, 1, file_size, f);
        fclose(f);
        bool ret = LoadTextureFromMemory(file_data, file_size, out_texture, out_width, out_height);
        IM_FREE(file_data);
        return ret;
    }

    // Function:    Load
    // -----------------
    // Loads a .png image file from a disk, converts it into an OpenGL texture, and
    // returns it as a texture object
    //
    // string path: path to the image file to load
    //
    // Returns TextureData struct containing information necessary for rendering
    TextureData Load(const std::string& path)
    {
        GLuint texture_id = 0;
        int width = 0, height = 0;

        if (!LoadTextureFromFile(path.c_str(), &texture_id, &width, &height))
        {
            std::cerr << "TextureLoader.LoadTexture: Failed to load texture: " << path << std::endl;
            throw std::runtime_error("TextureLoader.LoadTexture: Failed to load texture"); // Throw a standard exception
        }

        return TextureData
        {
            .id = texture_id,
            .width = width,
            .height = height,
        };
    }

}
