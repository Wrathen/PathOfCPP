#pragma once
#include "Ability.h"
#include "Miscellaneous/Timer.h"
#include "Miscellaneous/Vector.h"
#include "Components/Stats.h"

class Dash : public IAbility {
public:
	Stats* casterStats = nullptr;
	Timer lifetimeTimer;

	Dash(Entity* _caster) : IAbility(_caster, "Dash") {}

	virtual void Start() override;
	virtual void Update() override;
	virtual void Delete() override;
};