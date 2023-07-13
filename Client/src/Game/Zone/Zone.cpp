#include <fstream>
#include "Zone.h"

Zone::Zone(json data) {
	generalData = { data["General"]["Name"], data["General"]["MonsterLevel"] };
	bgData = { data["BGData"]["Path"] };

	auto colliderCount = data["ColliderData"].size();
	for (int i = 0; i < colliderCount; ++i) {
		auto col = data["ColliderData"][i];
		Vector2 pos = Vector2{ col["PosX"], col["PosY"] };

		colliderData.push_back({pos, col["Width"], col["Height"]});
	}

	auto entityCount = data["EntityData"].size();
	for (int i = 0; i < entityCount; ++i) {
		auto ent = data["EntityData"][i];
		Vector2 pos = Vector2{ ent["PosX"], ent["PosY"] };

		entityData.push_back({ent["ID"], ent["Type"], pos});
	}
}

Zone Zone::FromSaveFile(std::string filePath) {
	// Read json file and parse the raw data to JSON.
	std::ifstream jsonRawData(filePath);
	json data = json::parse(jsonRawData);

	return Zone(data);
}