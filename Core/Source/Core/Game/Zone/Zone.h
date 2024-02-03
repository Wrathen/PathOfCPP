#pragma once
#include <string>
#include <vector>
#include <json.hpp>
#include "Core/Miscellaneous/GUID.h"
#include "Core/Miscellaneous/Vector.h"

namespace Core {
	using json = nlohmann::json;

	#pragma region Zone Structs
	struct ZoneGeneralData {
		std::string name;
		int monsterLevel;
		Vector2 playerSpawnPosition;
	};
	struct ZoneBackgroundData {
		std::string bgPath;
	};
	struct ZoneColliderData {
		Vector2 position;
		uint32_t w, h;
	};
	struct ZoneEntityData {
		GUID ID;
		uint32_t type;
		Vector2 position;
	};
	struct ZoneSpawnZoneData {
		Vector2 position;
		uint32_t w, h, amount;
	};
	struct ZonePortalData {
		Vector2 position;
		uint32_t w, h;
		std::string nextZone;
	};
	#pragma endregion

	// Represents a Game Map.
	class Zone {
	protected:
		ZoneGeneralData generalData;
		ZoneBackgroundData bgData;
		std::vector<ZoneColliderData> colliderData;
		std::vector<ZoneEntityData> entityData;
		std::vector<ZoneSpawnZoneData> spawnZoneData;
		std::vector<ZonePortalData> portalData;

	public:
		// Constructor
		Zone() = delete;
		Zone(json data);

		// Main Methods
		const ZoneGeneralData& GetGeneralData() const { return generalData; };
		const ZoneBackgroundData& GetBackground() const { return bgData; };
		const std::vector<ZoneColliderData>& GetColliders() const { return colliderData; };
		const std::vector<ZoneEntityData>& GetEntities() const { return entityData; }
		const std::vector<ZoneSpawnZoneData>& GetSpawnZones() const { return spawnZoneData; };
		const std::vector<ZonePortalData>& GetPortals() const { return portalData; }

		// Static Methods
		// Reads a JSON Zone save file.
		static Zone FromSaveFile(std::string filePath);
	};
}