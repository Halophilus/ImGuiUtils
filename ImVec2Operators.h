/*
 * ImVec2Operators.h
 * Ben Henshaw
 * 7/24/2025
 *
 * Operator overloads for operations dealing with ImVec2, allowing simple vector
 * addition and subtraction as well as scalar division and multiplication of vectors.
 * These overloads were designed to streamline the cartesian operations intrinsic to
 * Dear ImGui's coordinate system.
 */
#ifndef IMVEC2OPERATORS_H
#define IMVEC2OPERATORS_H
// imvec2_operators.h

#pragma once
#include <imgui.h>

// Overload:    + (addition)
// -------------------------
// Adds two ImVec2 objects together
// This is most often used to perform a translocation from one point to another point
// relative to the other,
inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) {
    return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

// Overload:    - (subtraction)
// ----------------------------
// Subtracts one ImVec2 object from another
// This can be thought as moving backwards to a relative point from the minuend point
inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) {
    return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y);
}

// Overload:    * (multiplication)
// -------------------------------
// The scalar multiplication of an ImVec2
// Can be thought of as scaling the vector by some factor
inline ImVec2 operator*(const ImVec2& lhs, float rhs) {
    return ImVec2(lhs.x * rhs, lhs.y * rhs);
}

// Overload:    / (division)
// -------------------------
// The scalar division of an ImVec2
// The inverse scaling of a vector by some factor
inline ImVec2 operator/(const ImVec2& lhs, float rhs) {
    return ImVec2(lhs.x / rhs, lhs.y / rhs);
}

#endif //IMVEC2OPERATORS_H
