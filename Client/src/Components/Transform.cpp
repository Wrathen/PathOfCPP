#include "Transform.h"
#include "../Managers/CameraManager.h"

// I was returning a reference like (Vector2&). It should have give me errors/bugs because I'm allocating in Stack.
// Why did it work perfectly fine? I guess compiler did shady stuff behind my back. Even though the compile fixed
// the errors, I'd rather just get a bug/error instead of this. I am now just returning a new Vector2.
const Vector2 Transform::GetScreenPosition() const {
	Vector2 pos = GetPosition();
	return isAbsolutePositioned ? pos : pos - Camera.GetPosition();
}