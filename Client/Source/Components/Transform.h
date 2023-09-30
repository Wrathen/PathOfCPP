#pragma once
#pragma warning( disable : 4244 )
#include "Miscellaneous/Vector.h"
#include "Miscellaneous/Time.h"

class Transform {
private:
	Vector2 position = Vector2(0, 0);
	Vector2 velocity = Vector2(0, 0);
	Vector2 scale = Vector2(1, 1);

public:
	float rotation = 0;
	float scaleModifier = 1.0f;
	bool isAbsolutePositioned = false;

	// Getters
	const Vector2& GetPosition() const { return position; }
	const Vector2& GetVelocity() const { return velocity; }
	const Vector2 GetScreenPosition() const;
	Vector2 GetScale() { return Vector2(scale.x * scaleModifier, scale.y * scaleModifier); }

	// Setters
	void SetPosition(float x, float y) { position.x = x; position.y = y; }
	void SetScale(float x, float y) { scale.x = x; scale.y = y; }
	void SetScaleModifier(float value) { scaleModifier = value; }
	void SetVelocity(float x, float y) { if (isVelocityLocked) return; velocity.x = x; velocity.y = y; }
	void SetPosition(const Vector2& vec) { position.x = vec.x; position.y = vec.y; }
	void SetScale(const Vector2& vec) { scale.x = vec.x; scale.y = vec.y; }
	void SetVelocity(const Vector2& vec) { if (isVelocityLocked) return; velocity.x = vec.x; velocity.y = vec.y; }
	void LockVelocity(bool flag) { isVelocityLocked = flag; } // Locks velocity at it's current value so it can not be changed.
	void SetRotation(float x) { rotation = x; }

	// Transform Move
	Vector2 GetDeltaPosition(Vector2 dir, float spd) { return dir * (spd * Time::deltaTime); }
	Vector2 GetPositionNextFrame(Vector2 dir, float spd) { return position + GetDeltaPosition(dir, spd); }
	void Move(Vector2 dir, float spd) { position = GetPositionNextFrame(dir, spd); }
	void Move() { position += velocity * Time::deltaTime; }

private:
	bool isVelocityLocked = false; // Toggle to lock velocity at the current value and prevents changes.
};