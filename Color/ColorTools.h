/*
 * ColorTools.h
 * Ben Henshaw
 * 7/29/2025
 *
 * Header for set of procedural helper functions in producing
 * color objects specific to Dear ImGui. These tools include interpolating colors
 * between two points on a gradient as a function of percentage and fetching
 * ImVec4 and ImU32 objects.
 */
#ifndef COLORTOOLS_H
#define COLORTOOLS_H
#include "imgui.h"

namespace Color {
        // Interpolate between two RGBA colors (ImVec4)
        ImVec4 LerpRGBA(const ImVec4& start, const ImVec4& end, float t);

        // Interpolate between two RGB values, returning ImVec4
        ImVec4 GetInterpolatedColor(float percentage, float r1, float g1, float b1, float r2, float g2, float b2);

        // Interpolate between two RGB values, returning ImU32
        ImU32 GetInterpolatedColorU32(float percentage, float r1, float g1, float b1, float r2, float g2, float b2);

        // Convenience overloads using default hardcoded colors
        ImVec4 GetInterpolatedColor(float percentage);
        ImU32  GetInterpolatedColorU32(float percentage);

        // Create a pulsing color between two RGB colors over time
        ImU32 PulseColor(float r1, float g1, float b1, float r2, float g2, float b2, float frequency = 1.0f);

        // Apply a new alpha to an existing ImU32 color
        ImU32 RGBtoImU32(float r, float g, float b, float a);
        ImU32 WithAlpha(ImU32 color, float alpha);

        // Convert to different types
        ImVec4 RGBtoImVec4(float r, float g, float b, float a);
} // Color

#endif //COLORTOOLS_H
