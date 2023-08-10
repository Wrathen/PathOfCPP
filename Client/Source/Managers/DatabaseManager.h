#pragma once
#include "sqlite3.h"
#include <vector>
#include "../Miscellaneous/Singleton.h"

#define DB Database::DatabaseManager::GetInstance()
namespace Database {
	class DatabaseManager : public Singleton<DatabaseManager> {
		friend class Singleton;
		friend class GameManager;

	public:
		// Main Functions
		void PrintTable(const char* tableName);
		bool ExecuteQuery(const char* query, int (*callback)(void*, int, char**, char**), void* data = nullptr);

	protected:
		void Init();

	private:
		// Database Connection Variable.
		sqlite3* db = nullptr;

		// Ctor & Dtor
		DatabaseManager() {}
		~DatabaseManager();
		DatabaseManager(DatabaseManager const&) = delete;
		void operator=(DatabaseManager const&) = delete;
	};
}

// Namespace Global Functions -- It's like a glance of potential functions available.
// Function bodies are located within their appropriate .cpp files.
namespace Database {
	struct ItemModifier;
	enum class ItemModPoolTypes;

	std::vector<ItemModifier> GetAllItemModifiers(ItemModPoolTypes modPoolType, uint32_t itemLevel);
	ItemModifier GetRandomItemModifier(ItemModPoolTypes modPoolType, uint32_t itemLevel);
}