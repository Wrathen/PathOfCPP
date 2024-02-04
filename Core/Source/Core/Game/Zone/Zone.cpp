#include "Zone.h"
#include <fstream>

namespace Core {
	Zone::Zone(json data) {
		// Parse general information about the Zone from the JSON.
		generalData = { data["General"]["Name"],
						data["General"]["MonsterLevel"],
						Vector2(data["General"]["PlayerSpawnPosition"]["x"],
								data["General"]["PlayerSpawnPosition"]["y"]) };
		bgData = { data["BGData"]["Path"] };

		// Parse each Collider data from the JSON.
		auto colliderCount = data["ColliderData"].size();
		for (size_t i = 0; i < colliderCount; ++i) {
			auto& col = data["ColliderData"][i];
			Vector2 pos = Vector2{ col["PosX"], col["PosY"] };

			colliderData.push_back({ pos, col["Width"], col["Height"] });
		}

		// Parse each Entity data from the JSON.
		auto entityCount = data["EntityData"].size();
		for (size_t i = 0; i < entityCount; ++i) {
			auto& ent = data["EntityData"][i];
			Vector2 pos = Vector2{ ent["PosX"], ent["PosY"] };

			entityData.push_back({ ent["ID"], ent["Type"], pos });
		}

		// Parse each Spawn Zone data from the JSON.
		auto spawnZoneCount = data["SpawnZoneData"].size();
		for (size_t i = 0; i < spawnZoneCount; ++i) {
			auto& sz = data["SpawnZoneData"][i];
			Vector2 pos = Vector2{ sz["PosX"], sz["PosY"] };

			spawnZoneData.push_back({ pos, sz["Width"], sz["Height"], sz["Amount"] });
		}

		// Parse each Portal data from the JSON.
		auto portalCount = data["PortalData"].size();
		for (size_t i = 0; i < portalCount; ++i) {
			auto& p = data["PortalData"][i];
			Vector2 pos = Vector2{ p["PosX"], p["PosY"] };

			portalData.push_back({ pos, p["Width"], p["Height"], p["NextZone"] });
		}
	}

	// Create a Zone from a Save File (.PSD).
	Zone Zone::FromSaveFile(std::string filePath) {
		// Read json file and parse the raw data to JSON.
		std::ifstream jsonRawData("../Assets/Zones/" + filePath);
		json data = json::parse(jsonRawData);

		return Zone(data);
	}
}