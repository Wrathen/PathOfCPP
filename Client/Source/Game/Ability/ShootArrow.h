#pragma once
#include "Ability.h"
#include "Miscellaneous/Vector.h"

class ShootArrow : public IAbility {
public:
	ShootArrow(Entity* _caster) : IAbility(_caster, "ShootArrow") {}
	
	virtual void Start() override;
	virtual void Update() override;
	virtual void Delete() override;

	void Shoot(const Vector2& targetPos);
};