#pragma once
#include "NPC.h"
#include "../../Game/Zone/Zone.h"

class Portal: public NPC {
public:
	const ZonePortalData data;
	Portal(const ZonePortalData& _data);

	void Update() override;
	void OnPlayerNearby() override;
	void OnPlayerAway() override;

	void TeleportToNextMap();
};