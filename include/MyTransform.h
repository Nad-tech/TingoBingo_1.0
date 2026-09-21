#pragma once

#include "raylib.h"
#include <cmath>

struct MyTransform
{
    Vector2 position = { 0.0f, 0.0f };
    Vector2 pivot = { 0.0f, 0.0f };
    float rotation = 0.0f;
    float scale = 1.0f;
};


// ------------------------------------------------------------
// Create a child transform from a parent's transform.
// ------------------------------------------------------------
//
// A child transform needs to know where it sits relative to
// its parent, while still following the parent's movement,
// rotation and scale.
//
// positionOffset describes the child's local position relative
// to the parent joint.
//
// For example:
//
//     PARENT JOINT
//          ●
//          │
//          │ positionOffset
//          │
//          ●
//     CHILD CENTRE
//
// The child's position must be calculated in world space so
// that it continues to follow the parent when the parent rotates.
//
inline MyTransform MakeChildTransform(
    const MyTransform& parentTransform,
    Vector2 positionOffset)
{
    MyTransform child;


    // ------------------------------------------------------------
    // 1. Convert the parent's rotation from degrees to radians.
    // ------------------------------------------------------------
    //
    // Our transforms store angles in degrees because that is
    // convenient for the rest of the robot.
    //
    // sinf() and cosf() expect radians.
    //
    float globalRadians = parentTransform.rotation * DEG2RAD;


    // ------------------------------------------------------------
    // 2. Find the vector from the parent's rotation centre
    //    to the parent joint.
    // ------------------------------------------------------------
    //
    // parentTransform.pivot points from the parent joint back
    // toward the parent's rotation centre.
    //
    // We need the opposite direction when calculating the
    // joint's offset from the parent's rotation centre.
    //
    // So we negate the pivot.
    //
    // Conceptually:
    //
    //     PARENT ROTATION CENTRE
    //             ●
    //             │
    //             │
    //             ▼
    //         PARENT JOINT
    //
    // parentTransform.pivot points toward the rotation centre.
    // Negating it gives the offset back to the parent joint.
    //
    Vector2 parentOffset =
    {
        -parentTransform.pivot.x,
        -parentTransform.pivot.y
    };


    // ------------------------------------------------------------
    // 3. Recover the parent's rotation centre.
    // ------------------------------------------------------------
    //
    // parentTransform.position is the centre of the parent.
    //
    // parentTransform.pivot points from the parent centre back
    // toward the parent's rotation centre.
    //
    // Therefore:
    //
    //     parent position + parent pivot
    //
    // gives us the parent's rotation centre.
    //
    // This is important because the parent joint must rotate
    // around the parent's rotation centre when the parent turns.
    //
    Vector2 parentPosition =
    {
        parentTransform.position.x + parentTransform.pivot.x,
        parentTransform.position.y + parentTransform.pivot.y
    };


    // ------------------------------------------------------------
    // 4. Rotate the parent's offset around the parent.
    // ------------------------------------------------------------
    //
    // At this point we know:
    //
    //     parentPosition
    //         = parent's rotation centre
    //
    //     parentOffset
    //         = vector from the parent's rotation centre
    //           to the parent joint
    //
    // When the parent rotates, that vector must rotate as well.
    //
    // This is the standard 2D rotation formula:
    //
    //     x' = x * cos(angle) - y * sin(angle)
    //     y' = x * sin(angle) + y * cos(angle)
    //
    // The result is the parent joint's new offset after the
    // parent has rotated.
    //
    Vector2 rotatedParentOffset =
    {
        parentOffset.x * cosf(globalRadians) -
        parentOffset.y * sinf(globalRadians),

        parentOffset.x * sinf(globalRadians) +
        parentOffset.y * cosf(globalRadians)
    };


    // ------------------------------------------------------------
    // 5. Convert the rotated offset back into a world position.
    // ------------------------------------------------------------
    //
    // rotatedParentOffset tells us where the parent joint is
    // relative to the parent's rotation centre.
    //
    // Add that offset to the parent's rotation centre to get
    // the joint's new world position.
    //
    Vector2 parentJointPosition =
    {
        parentPosition.x + rotatedParentOffset.x,
        parentPosition.y + rotatedParentOffset.y
    };


    // ------------------------------------------------------------
    // 6. Position the centre of the child.
    // ------------------------------------------------------------
    //
    // We now know where the parent joint is.
    //
    // positionOffset tells us where the centre of the child is
    // relative to that joint.
    //
    // So:
    //
    //     parent joint position
    //             +
    //     child position offset
    //             =
    //     child centre
    //
    // This keeps the child attached to the parent joint.
    //
    child.position =
    {
        parentJointPosition.x + positionOffset.x,
        parentJointPosition.y + positionOffset.y
    };


    // ------------------------------------------------------------
    // 7. Set the child's pivot to the parent joint.
    // ------------------------------------------------------------
    //
    // child.position is the centre of the child.
    //
    // We don't want the child to rotate around its centre.
    //
    // We want it to rotate around the parent joint.
    //
    // positionOffset points:
    //
    //     parent joint → child centre
    //
    // Therefore the negative of positionOffset points:
    //
    //     child centre → parent joint
    //
    // That is exactly the pivot we need.
    //
    // Example:
    //
    //     positionOffset = (0, -100)
    //
    // means:
    //
    //     child centre is 100 units below the parent joint.
    //
    // Therefore:
    //
    //     pivot = (0, +100)
    //
    // places the rotation point at the parent joint.
    //
    child.pivot =
    {
        -positionOffset.x,
        -positionOffset.y
    };


    // ------------------------------------------------------------
    // 8. Inherit the parent's rotation.
    // ------------------------------------------------------------
    //
    // The child is attached to the parent, so it follows the
    // parent's rotation.
    //
    // Any additional local rotation can be added by the child
    // after this transform has been created.
    //
    child.rotation = parentTransform.rotation;


    // ------------------------------------------------------------
    // 9. Inherit the parent's scale.
    // ------------------------------------------------------------
    //
    // All parts of the robot use the same scale so that the
    // hierarchy remains visually consistent.
    //
    child.scale = parentTransform.scale;


    // ------------------------------------------------------------
    // 10. Return the completed child transform.
    // ------------------------------------------------------------
    //
    // At this point we have calculated everything the child needs:
    //
    //     position -> where the child centre is
    //     pivot    -> where the parent joint is
    //     rotation -> inherited from the parent
    //     scale    -> inherited from the parent
    //
    return child;
}