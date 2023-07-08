#pragma once
#include <string>
#include <vector>
#include "../../Miscellaneous/GUID.h"
#include "../../Miscellaneous/Vector.h"
#include "json.hpp"

using json = nlohmann::json;

#pragma region Zone Structs
	struct ZoneGeneralData {
		std::string name;
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
#pragma endregion

// Represents a Game Map.
class Zone {
protected:
	ZoneGeneralData generalData;
	ZoneBackgroundData bgData;
	std::vector<ZoneColliderData> colliderData;
	std::vector<ZoneEntityData> entityData;
	
public:
	// Constructor
	Zone() = delete;
	Zone(json data);

	// Main Methods
	const ZoneGeneralData& GetGeneralData() const { return generalData; };
	const ZoneBackgroundData& GetBackground() const { return bgData; };
	const std::vector<ZoneColliderData>& GetColliders() const { return colliderData; };
	const std::vector<ZoneEntityData>& GetEntities() const { return entityData; }
	
	// Static Methods
	// Reads a JSON Zone save file.
	static Zone FromSaveFile(std::string jsonPath);
};