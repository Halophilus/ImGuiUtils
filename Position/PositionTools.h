/*
 * PositionTools.h
 * Ben Henshaw
 * 7/29/2025
 *
 * Header file for procedural helper functions used to calculate relative positional
 * vectors for aligning objects on a cartesian plane, relative to each other a document or an
 * unstructured canvas.
 */
#ifndef POSITIONTOOLS_H
#define POSITIONTOOLS_H
#include "imgui.h"

namespace Position {

    // Document alignment, uses line number and document size to determine relative coordinates
    ImVec2 RightAlign(ImVec2 origin, float documentWidth, float lineHeight, int line, ImVec2 objectDimensions);
    ImVec2 CenterAlign(ImVec2 origin, float documentWidth, float lineHeight, int line, ImVec2 objectDimensions);
    ImVec2 LeftAlign(ImVec2 origin, float lineHeight, int line, ImVec2 objectDimensions);
    ImVec2 Center2D(ImVec2 origin, ImVec2 targetObjectDimensions, ImVec2 centeredObjectDimensions);

    // Outside alignment, aligns objects with other objects along their outer edges
    ImVec2 TopAlignOnRightSide(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, float distanceApart);
    ImVec2 BottomAlignOnRightSide(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, ImVec2 alignedObjectDimensions, float distanceApart);
    ImVec2 CenterOnLeftSide(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, ImVec2 centeredObjectDimensions, float distanceApart);
    ImVec2 CenterOnRightSide(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, ImVec2 centeredObjectDimensions, float distanceApart);
    ImVec2 CenterAbove(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, ImVec2 centeredObjectDimensions, float distanceApart);

    // Inner alignment, aligns an overlain object onto a 2D plane
    ImVec2 InnerAlignCenterLeft(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, ImVec2 centeredObjectDimensions);
    ImVec2 InnerAlignCenterRight(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, ImVec2 centeredObjectDimensions);
    ImVec2 InnerAlignBottomRight(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, ImVec2 alignedObjectDimensions, float gap);
    ImVec2 InnerAlignBottomLeft(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, ImVec2 alignedObjectDimensions, float gap);
    ImVec2 InnerAlignTopLeft(ImVec2 targetObjectOrigin, float gap);
    ImVec2 InnerAlignBottomCenter(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, ImVec2 alignedObjectDimensions, float gap);

    // Grid alignment
    ImVec2 GridTranslocatedOrigin(ImVec2 origin, float cellWidth, float cellHeight, float gridlineWidth, int columns, int rows, int cellNumber);

    // Frame size calculation
    ImVec2 FrameWithin(ImVec2 outerFrame, ImVec2 innerFrame, float padding);
} // Position

#endif //POSITIONTOOLS_H
