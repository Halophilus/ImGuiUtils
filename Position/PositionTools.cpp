/*
 * PositionTools.cpp
 * Ben Henshaw
 * 7/29/2025
 *
 * Implementation source file for procedural helper functions used to calculate relative positional
 * vectors for aligning objects on a cartesian plane, relative to each other, a document or an
 * unstructured canvas.
 *
 * Diagrams created using ASCIIFlow by Lewish (2021)
 * https://github.com/lewish/asciiflow
 */
#include "PositionTools.h"
#include "ImVec2Operators.h"

namespace Position {

    // Function:    RightAlign
    // -----------------------
    // Right aligns text in the style of a document editor
    //                      documentWidth
    //         ◄─────────────────────────────────────►
    //   Origin*─────────────────────────────────────┐
    // *line 1*│                     content is lined│
    // *line 2*│                      up on a line by│
    // *line 3*│                           line basis│
    //         └─────────────────────────────────────┘
    //
    // ImVec2 origin:           coordinates to the upper-left corner of the document
    // float documentWidth:     the width of the canvas/document on which the object is being aligned
    // float lineHeight:        the distance between the start of each line in pixels
    // int line:                the line number where the object is being placed
    // ImVec2 objectDimensions: the size of the object being inserted at that line
    //
    // Returns the coordinates of the upper left corner of the aligned object
    ImVec2 RightAlign(ImVec2 origin, float documentWidth, float lineHeight, int line, ImVec2 objectDimensions)
    {
        return origin + ImVec2(documentWidth, line * lineHeight) - objectDimensions;
    }

    // Function:    LeftAlign
    // -----------------------
    // Right aligns text in the style of a document editor
    //                       documentWidth
    //          ◄─────────────────────────────────────►
    //    Origin*─────────────────────────────────────┐
    //  *line 1*│content is lined                     │
    //  *line 2*│up on a line by                      │
    //  *line 3*│line basis                           │
    //          └─────────────────────────────────────┘
    //
    // ImVec2 origin:           coordinates to the upper-left corner of the document
    // float documentWidth:     the width of the canvas/document on which the object is being aligned
    // float lineHeight:        the distance between the start of each line in pixels
    // int line:                the line number where the object is being placed
    // ImVec2 objectDimensions: the size of the object being inserted at that line
    //
    // Returns the coordinates of the upper left corner of the aligned object
    ImVec2 LeftAlign(ImVec2 origin, float lineHeight, int line, ImVec2 objectDimensions)
    {
        return origin - ImVec2(0, lineHeight * line) - ImVec2( 0, objectDimensions.y);
    }

    // Function:    CenterAlign
    // ------------------------
    // Center aligns text in the style of a document editor
    //                     documentWidth
    //         ◄─────────────────────────────────────►
    //   Origin*─────────────────────────────────────┐
    // *line 1*│         content is lined            │
    // *line 2*│          up on a line by            │
    // *line 3*│            line basis               │
    //         └─────────────────────────────────────┘
    // ImVec2 origin:           coordinates to the upper-left corner of the document
    // float documentWidth:     the width of the canvas/document on which the object is being aligned
    // float lineHeight:        the distance between the start of each line in pixels
    // int line:                the line number where the object is being placed
    // ImVec2 objectDimensions: the size of the object being inserted at that line
    //
    // Returns the coordinates of the upper left corner of the aligned object
    ImVec2 CenterAlign(ImVec2 origin, float documentWidth, float lineHeight, int line, ImVec2 objectDimensions)
    {
        float x = origin.x + ((documentWidth - objectDimensions.x) / 2) ;
        float y = origin.y + line * lineHeight;
        return ImVec2(x, y);
    }

    // Function:    Center2D
    // ---------------------
    // Centers an object two-dimensionally over another object
    // Origin*─────────────────────────────────────┐
    //       │            Target Object            │
    //       │   ┌─────────────────────────────┐   │
    //       │   │       Centered Object       │   │
    //       │   └─────────────────────────────┘   │
    //       │                                     │
    //       └─────────────────────────────────────┘
    //
    // ImVec2 origin:                   coordinates of the upper-left corner of the target object
    // ImVec2 targetObjectDimensions:   size of the target object
    // ImVec2 centeredObjectDimensions: size of the centered object
    //
    // Returns the coordinates of the upper left corner of the centered object
    ImVec2 Center2D(ImVec2 origin, ImVec2 targetObjectDimensions, ImVec2 centeredObjectDimensions)
    {
        return origin + ImVec2((targetObjectDimensions.x - centeredObjectDimensions.x) / 2,
                               (targetObjectDimensions.y - centeredObjectDimensions.y) / 2);
    }

    // Function:    CenterOnLeftSide
    // -----------------------------
    // Aligns a centered object to the left of the target object at the midpoint of its vertical dimension
    //        Target Origin*────────────────────┐
    // ┌─────────────────┐ │                    │
    // │ Centered Object ◄─►   Target Object    │
    // └─────────────────┘x│                    │
    //                    x└────────────────────┘
    //              Distance Apart
    //
    // ImVec2 targetObjectOrigin:       coordinates of the upper-left corner of the target object
    // ImVec2 targetObjectDimensions:   size of the target object
    // ImVec2 centeredObjectDimensions: size of the centered object
    // float distanceApart:             the distance between the centered object and the target object
    //
    // Returns the coordinates of the upper left corner of the centered object
    ImVec2 CenterOnLeftSide(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, ImVec2 centeredObjectDimensions, float distanceApart)
    {
        float x = targetObjectOrigin.x - distanceApart - centeredObjectDimensions.x;
        float y = targetObjectOrigin.y + (targetObjectDimensions.y - centeredObjectDimensions.y) / 2.0f;
        return ImVec2(x, y);
    }

    // Function:    CenterAbove
    // ------------------------
    // Aligns a centered object above a target object at the midpoint of its horizontal dimension
    //                ┌─────────────────┐
    //                │ Centered Object │
    //                └────────▲────────┘
    //                         │ xxxxxxxx Distance apart
    // Target Origin*──────────▼──────────┐
    //              │                     │
    //              │    Target Object    │
    //              │                     │
    //              └─────────────────────┘
    //
    // ImVec2 targetObjectOrigin:       coordinates of the upper-left corner of the target object
    // ImVec2 targetObjectDimensions:   size of the target object
    // ImVec2 centeredObjectDimensions: size of the centered object
    // float distanceApart:             the distance between the centered object and the target object
    //
    // Returns the coordinates of the upper left corner of the centered object
    ImVec2 CenterAbove(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, ImVec2 centeredObjectDimensions, float distanceApart)
    {
        ImVec2 absoluteCenter = Center2D(targetObjectOrigin, targetObjectDimensions, centeredObjectDimensions);
        return absoluteCenter - ImVec2(0, distanceApart + targetObjectDimensions.y / 2.0f);
    }

    // Function:    CenterOnRightSide
    // ------------------------------
    // Aligns a centered object to the right of the target at the midpoint of its vertical dimension
    // Target Origin*────────────────────┐
    //              │                    │ ┌─────────────────┐
    //              │   Target Object    ◄─► Centered Object │
    //              │                    │x└─────────────────┘
    //              └────────────────────┘x
    //                             Distance Apart
    //
    // ImVec2 targetObjectOrigin:       coordinates of the upper-left corner of the target object
    // ImVec2 targetObjectDimensions:   size of the target object
    // ImVec2 centeredObjectDimensions: size of the centered object
    // float distanceApart:             the distance between the centered object and the target object
    //
    // Returns the coordinates of the upper left corner of the centered object
    ImVec2 CenterOnRightSide(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, ImVec2 centeredObjectDimensions, float distanceApart)
    {
        float x = targetObjectOrigin.x + targetObjectDimensions.x + distanceApart ;
        float y = targetObjectOrigin.y + (targetObjectDimensions.y - centeredObjectDimensions.y) / 2.0f;
        return ImVec2(x, y);
    }


    // Function:    BottomAlignOnRightSide
    // -----------------------------------
    // Aligns a centered object along the bottom edge of the target object on the right side
    // Target Origin*───────────────────┐
    //              │                   │
    //              │   Target Object   │ ┌─────────────────┐
    //              │                   ◄─► Centered Object │
    //              └───────────────────┘x└─────────────────┘
    //                            Distance apart
    // ImVec2 targetObjectOrigin:       coordinates of the upper-left corner of the target object
    // ImVec2 targetObjectDimensions:   size of the target object
    // ImVec2 centeredObjectDimensions: size of the centered object
    // float distanceApart:             the distance between the centered object and the target object
    //
    // Returns the coordinates of the upper left corner of the centered object
    ImVec2 BottomAlignOnRightSide(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, ImVec2 alignedObjectDimensions, float distanceApart)
    {
        float x = targetObjectOrigin.x + targetObjectDimensions.x + distanceApart;
        float y = targetObjectOrigin.y + (targetObjectDimensions.y - alignedObjectDimensions.y);
        return ImVec2(x, y);
    }

    // Function:    TopAlignOnRightSide
    // --------------------------------
    // Aligns a centered object along the top edge of a target object on its right side
    // Target Origin*───────────────────┐ ┌─────────────────┐
    //              │                   ◄─► Centered Object │
    //              │   Target Object   │x└─────────────────┘
    //              │                   |Distance apart
    //              └───────────────────┘
    // ImVec2 targetObjectOrigin:       coordinates of the upper-left corner of the target object
    // ImVec2 targetObjectDimensions:   size of the target object
    // ImVec2 centeredObjectDimensions: size of the centered object
    // float distanceApart:             the distance between the centered object and the target object
    //
    // Returns the coordinates of the upper left corner of the centered object
    ImVec2 TopAlignOnRightSide(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, float distanceApart)
    {
        float x = targetObjectOrigin.x + targetObjectDimensions.x + distanceApart;
        float y = targetObjectOrigin.y;
        return ImVec2(x, y);
    }

    // Function:    InnerAlignCenterLeft
    // ---------------------------------
    // Aligns a centered object with the vertical dimension of the target object, and positions it on the left-hand side
    // of the inside of the target object, equidistant from the three nearest edges of the target object
    //     Target Origin*───────────────────────────────┐
    //                  │         Target Object         │
    //                  │ ┌───────────────┐             │
    //                  │ │Centered Object│             │
    //                  │ └───────────────┘             │
    //                  │                               │
    //                  └───────────────────────────────┘
    // ImVec2 targetObjectOrigin:       coordinates of the upper-left corner of the target object
    // ImVec2 targetObjectDimensions:   size of the target object
    // ImVec2 centeredObjectDimensions: size of the centered object
    //
    // Returns the coordinates of the upper left corner of the centered object
    ImVec2 InnerAlignCenterLeft(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, ImVec2 centeredObjectDimensions)
    {

        float centeringDisplacement = (targetObjectDimensions.y - centeredObjectDimensions.y) / 2;
        float y = targetObjectOrigin.y + centeringDisplacement;
        float x = targetObjectOrigin.x + centeringDisplacement;

        return ImVec2(x, y);
    }

    // Function:    InnerAlignCenterRight
    // ----------------------------------
    // Aligns a centered object with the vertical dimension of the target object, and positions it on the right-hand side
    // of the inside of the target object, equidistant from the three nearest edges of the target object
    //     Target Origin*───────────────────────────────┐
    //                  │         Target Object         │
    //                  │             ┌───────────────┐ │
    //                  │             │Centered Object│ │
    //                  │             └───────────────┘ │
    //                  │                               │
    //                  └───────────────────────────────┘
    // ImVec2 targetObjectOrigin:       coordinates of the upper-left corner of the target object
    // ImVec2 targetObjectDimensions:   size of the target object
    // ImVec2 centeredObjectDimensions: size of the centered object
    //
    // Returns the coordinates of the upper left corner of the centered object
    ImVec2 InnerAlignCenterRight(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, ImVec2 centeredObjectDimensions)
    {
        float centeringDisplacement = (targetObjectDimensions.y - centeredObjectDimensions.y) / 2;
        float y = targetObjectOrigin.y + centeringDisplacement;
        float x = targetObjectOrigin.x + targetObjectDimensions.x - centeredObjectDimensions.x - centeringDisplacement;

        return ImVec2(x, y);
    }

    // Function:    InnerAlignBottomRight
    // ----------------------------------
    // Aligns an object with the inner bottom right of a target object, separated from the edges of the target
    // object by a gap of a set width
    // Target Origin*──────────────────────────┐
    //              │      Target Object       │
    //              │         ┌──────────────┐ │
    //              │         │Aligned Object◄─► Gap
    //              │         └▲─────────────┘x│
    //              │      Gap │ xxxxxxxxxxxxxx│
    //              └──────────▼───────────────┘
    // ImVec2 targetObjectOrigin:       coordinates of the upper-left corner of the target object
    // ImVec2 targetObjectDimensions:   size of the target object
    // ImVec2 alignedObjectDimensions:  size of the aligned object
    // float gap:                       the distance between the aligned object and the closest two edges of the target object
    //
    // Returns the coordinates of the upper left corner of the aligned object
    ImVec2 InnerAlignBottomRight(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, ImVec2 alignedObjectDimensions, float gap)
    {
        float x = targetObjectOrigin.x + targetObjectDimensions.x - alignedObjectDimensions.x - gap;
        float y = targetObjectOrigin.y + targetObjectDimensions.y - gap - alignedObjectDimensions.y;

        return ImVec2(x, y);
    }

    // Function:    InnerAlignTopLeft
    // ------------------------------
    // Aligns an object with the inner top left of a target object, separated from the edges of the target
    // object by a gap of a set width
    // Target Origin*───────────────▲──────────┐
    //              │xxxxxxxxxxxxxxx│Gap       │
    //              │x┌─────────────▼┐         │
    //           Gap◄─►Aligned Object│         │
    //              │ └──────────────┘         │
    //              │      Target Object       │
    //              └──────────────────────────┘
    // ImVec2 targetObjectOrigin:       coordinates of the upper-left corner of the target object
    // float gap:                       the distance between the aligned object and the closest two edges of the target object
    //
    // Returns the coordinates of the upper left corner of the aligned object
    ImVec2 InnerAlignTopLeft(ImVec2 targetObjectOrigin, float gap)
    {
        float x = targetObjectOrigin.x + gap;
        float y = targetObjectOrigin.y + gap;

        return ImVec2(x, y);
    }

    // Function:    InnerAlignBottomLeft
    // ----------------------------------
    // Aligns an object with the inner bottom left of a target object, separated from the edges of the target
    // object by a gap of a set width
    // ImVec2 targetObjectOrigin:       coordinates of the upper-left corner of the target object
    // ImVec2 targetObjectDimensions:   size of the target object
    // ImVec2 alignedObjectDimensions:  size of the aligned object
    // float gap:                       the distance between the aligned object and the closest two edges of the target object
    //
    // Returns the coordinates of the upper left corner of the aligned object
    ImVec2 InnerAlignBottomLeft(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions, ImVec2 alignedObjectDimensions, float gap)
    {
        float x = targetObjectOrigin.x + gap;
        float y = targetObjectOrigin.y + targetObjectDimensions.y - gap - alignedObjectDimensions.y;

        return ImVec2(x, y);
    }

    // Function:    InnerAlignBottomCenter
    // -----------------------------------
    // Aligns an object along the X axis along the bottom of the target object, with a set Y offset equal to gap
    // Origin*────────────────────────────┐
    //       │       Target Object        │
    //       │  ┌──────────────────────┐  │
    //       │  │    Aligned Object    │  │
    //       │  └─▲────────────────────┘  │
    //       │    │ Gap                   │
    //       └────▼───────────────────────┘
    // ImVec2 targetObjectOrigin:       coordinates of the upper-left corner of the target object
    // ImVec2 targetObjectDimensions:   size of the target object
    // ImVec2 alignedObjectDimensions:  size of the aligned object
    // float gap:                       the distance between the aligned object and the closest two edges of the target object
    //
    // Returns the coordinates of the upper left corner of the aligned object
    ImVec2 InnerAlignBottomCenter(ImVec2 targetObjectOrigin, ImVec2 targetObjectDimensions,
                                  ImVec2 alignedObjectDimensions, float gap)
    {
        float x = targetObjectOrigin.x + (targetObjectDimensions.x - alignedObjectDimensions.x) / 2;
        float y = targetObjectOrigin.y + targetObjectDimensions.y - alignedObjectDimensions.y - gap;

        return ImVec2(x, y);
    }

    // Function:    GridTranslocatedOrigin
    // -----------------------------------
    // Generates the positional vector of any cell within a defined grid system
    // Origin*────────┬────────┬────────┐▲
    //       │*cell 1*│*cell 2*│*cell 3*││Cell Height
    //       ├────────┼────────┼────────┤▼
    //       │*cell 4*│*cell 5*│*cell 6*│
    //       ├────────┼────────┼────────┤
    //       │*cell 7*│*cell 8*│*cell 9*│
    //       └────────┴────────┴────────┘
    //                         ◄────────►
    //                         Cell Width
    // ImVec2 origin:       the upper left corner of the grid system
    // float cellWidth:     the width of a cell in pixels
    // float cellHeight:    the height of a cell in pixels
    // float gridlineWidth: the thickness of the gridlines in the grid system
    // int columns:         the number of columns in the grid system
    // int rows:            the number of columns in the grid system
    //
    // Returns the coordinates to the upper left corner of the chosen cell, just inside the gridline borders
    ImVec2 GridTranslocatedOrigin(ImVec2 origin, float cellWidth, float cellHeight, float gridlineWidth, int columns, int rows, int cellNumber)
    {
        origin = origin + ImVec2(gridlineWidth, gridlineWidth);

        float horizontalDisplacement = cellWidth + gridlineWidth;
        float verticalDisplacement = cellHeight + gridlineWidth;

        int row = cellNumber / rows;
        int col = cellNumber % columns;

        float x = origin.x + col * horizontalDisplacement;
        float y = origin.y + row * verticalDisplacement;

        return ImVec2(x, y);
    }

    // Function:    FrameWithin
    // ------------------------
    // Finds the best fit
    ImVec2 FrameWithin(ImVec2 outerFrame, ImVec2 innerFrame, float padding)
    {
        float innerAspectRatio = innerFrame.x / innerFrame.y;
        float outerAspectRatio = outerFrame.x / outerFrame.y;

        float x, y;

        if (innerAspectRatio > outerAspectRatio)
        {
            // Fit width, adjust height to preserve aspect ratio
            x = outerFrame.x - 2 * padding;
            y = x / innerAspectRatio;
        }
        else
        {
            // Fit height, adjust width to preserve aspect ratio
            y = outerFrame.y - 2 * padding;
            x = y * innerAspectRatio;
        }

        return ImVec2(x, y);
    }

} // Position