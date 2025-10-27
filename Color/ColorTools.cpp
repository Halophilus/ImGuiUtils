/*
 * ColorTools.cpp
 * Ben Henshaw
 * 7/29/2025
 *
 * Source file implementation of set of procedural helper functions in producing
 * color objects specific to Dear ImGui. These tools include interpolating colors
 * between two points on a gradient as a function of percentage and fetching
 * ImVec4 and ImU32 objects.
 */

#include "ColorTools.h"

#include <algorithm>

#include "imgui_internal.h"

namespace Color {
    // Function:    LerpRGB
    // --------------------
    // Linearly interpolates between two solid ImVec4 colors as a function of some percentage
    //
    // ImVec4 start:    the initial color in the gradient function
    // ImVec4 end:      the terminal color in the gradient function
    // float t:         a percentage value indicating position on gradient
    //
    // Returns a solid ImVec4 hsl color
    ImVec4 LerpRGB(const ImVec4& start, const ImVec4& end, float t)
    {
        return ImVec4(
            start.x + (end.x - start.x) * t,
            start.y + (end.y - start.y) * t,
            start.z + (end.z - start.z) * t,
            1.0f
        );
    }

    // Function:    GetInterpolatedColor
    // ---------------------------------
    // Linearly interpolates between the two default colors to indicate percentage
    //
    // float percentage:      relative progress through the gradient of set colors
    //
    // Returns a solid ImVec4 hsl color
    ImVec4 GetInterpolatedColor(float percentage)
    {
        percentage = std::clamp(percentage, 0.0f, 1.0f);

        ImVec4 lowColor  = RGBtoImVec4(102.0f, 110.0f, 255.0f, 1.0f); // Indigo
        ImVec4 highColor = RGBtoImVec4( 45.0f, 199.0f, 163.0f, 1.0f); // Blue-green

        return LerpRGB(lowColor, highColor, percentage);
    }

    // Function:    GetInterpolatedColorU32
    // ------------------------------------
    // Utilizes GetInterpolatedColor to interpolate default colors and converts it to ImU32
    // for font color applications
    //
    // float percentage:    relative progress through the gradient of default colors
    //
    // Returns a solid ImU32 color
    ImU32 GetInterpolatedColorU32(float percentage) {
        return ImGui::ColorConvertFloat4ToU32(GetInterpolatedColor(percentage));
    }

    // Function:    GetInterpolatedColor
    // ---------------------------------
    // Relative gradient interpolation taking any RGB parameters as input
    //
    // float r1, g1, b1:    RGB values for initial color in gradient
    // float r2, g2, b2:    RGB values for terminal color in gradient
    // float percentage:    relative progress through the gradient
    //
    // Returns solid ImVec4
    ImVec4 GetInterpolatedColor(float percentage, float r1, float g1, float b1, float r2, float g2, float b2)
    {
        percentage = std::clamp(percentage, 0.0f, 1.0f);

        ImVec4 lowColor  = RGBtoImVec4(r1, g1, b1, 1); // Indigo
        ImVec4 highColor = RGBtoImVec4(r2, g2, b2, 1); // Blue-green

        return LerpRGB(lowColor, highColor, percentage);
    }

    // Function:    GetInterpolatedColorU32
    // ------------------------------------
    // Interpolates color given an RGB gradient for text color applications
    //
    // float r1, g1, b1:    RGB values for initial color in gradient
    // float r2, g2, b2:    RGB values for terminal color in gradient
    // float percentage:    relative progress through the gradient
    //
    // Returns solid ImU32 color
    ImU32 GetInterpolatedColorU32(float percentage, float r1, float g1, float b1, float r2, float g2, float b2) {
        return ImGui::ColorConvertFloat4ToU32(GetInterpolatedColor(percentage, r1, g1, b1, r2, g2, b2));
    }

    // Function:    PulseColor
    // -----------------------
    // Time-based function that uses oscillation interpolation to pulse between two colors
    // Used for text color applications
    //
    // float r1, g1, b1:    RGB values for initial color in gradient
    // float r2, g2, b2:    RGB values for terminal color in gradient
    // float frequency:     Periodic frequency of pulse in seconds
    //
    // Returns a solid ImU32 color
    ImU32 PulseColor(float r1, float g1, float b1, float r2, float g2, float b2, float frequency)
    {
        auto percentageBasedOnTime = (sinf(ImGui::GetTime() * frequency) + 1.0f) * 0.5f;
        return GetInterpolatedColorU32(percentageBasedOnTime, r1, g1, b1, r2, g2, b2);
    }

    // Function:    RGBtoImU32
    // -----------------------
    // Converts RGB values into an ImU32 color for text applications
    //
    // float r, g, b:   RGB values
    // float a:         alpha, or transparency value
    //
    // Returns an ImU32 color with set transparency
    ImU32 RGBtoImU32(float r, float g, float b, float a)
    {
        return ImGui::ColorConvertFloat4ToU32(ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f));
    }

    // Function:    WithAlpha
    // ----------------------
    // Takes an ImU32 and applies an alpha to it, resulting in a certain transparency
    //
    // ImU32 color:     input color
    // float a:         alpha, or transparency value
    //
    // Returns an ImU32 color with set transparency
    ImU32 WithAlpha(ImU32 color, float alpha)
    {
        ImU32 colorWithAlpha = color & 0x00FFFFFF; // mask out existing alpha
        colorWithAlpha |= (ImU32)(alpha * 255.0f) << 24; // insert new alpha
        return colorWithAlpha;
    }

    // Function:   RGBtoImVec4
    // -----------------------
    // Converts RGB values into an ImVec4 color for ImGui element color applications
    //
    // float r, g, b:   RGB values
    // float a:         alpha, or transparency value
    //
    // Returns an ImU32 color with set transparency
    ImVec4 RGBtoImVec4(float r, float g, float b, float a)
    {
        return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a);
    }

} // Color
