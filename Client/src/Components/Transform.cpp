#include "Transform.h"
#include "../Managers/CameraManager.h"

const Vector2& Transform::GetScreenPosition() const { return GetPosition() - Camera.GetPosition(); }