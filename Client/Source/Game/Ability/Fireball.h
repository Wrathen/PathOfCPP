#pragma once
#include "Ability.h"

class Fireball : public IAbility {
public:
	Fireball(Entity* _caster) : IAbility(_caster) {}

	virtual void Start() {}
	virtual void Update() {}
	virtual void Delete() {}
};