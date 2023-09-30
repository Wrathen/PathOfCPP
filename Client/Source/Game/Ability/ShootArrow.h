#pragma once
#include "Ability.h"

class ShootArrow : public IAbility {
public:
	ShootArrow(Entity* _caster) : IAbility(_caster) {}
	
	virtual void Start() {}
	virtual void Update() {}
	virtual void Delete() {}
};