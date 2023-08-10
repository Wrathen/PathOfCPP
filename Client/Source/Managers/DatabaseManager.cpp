#include "DatabaseManager.h"
#include "../Miscellaneous/ErrorHandler.h"
#include "../Miscellaneous/Log.h"

namespace Database {
	// Ctor & Dtor ~~ Handle opening&closing of the Database Connection.
	void DatabaseManager::Init() {
		if (sqlite3_open("Assets/Databases/PoC.db", &db) != SQLITE_OK)
			Abort("Couldn't connect to the Database.\n\nDatabase file might be corrupt.", "Runtime Error");
	}
	DatabaseManager::~DatabaseManager() { if (db) sqlite3_close(db); }

	// Main Functions
	bool DatabaseManager::ExecuteQuery(const char* query, int (*callback)(void*, int, char**, char**), void* data) {
		printf("Executing Query: '%s'\n", query);

		// Execute the Query.
		char* errorMsg;
		int resultCode = sqlite3_exec(db, query, callback, data, &errorMsg);

		// Error handling
		if (resultCode != SQLITE_OK) {
			Error("Requested database query responded with an error.");
			Error(query);
			Error(errorMsg);
			return false;
		}

		return true;
	}
	void DatabaseManager::PrintTable(const char* tableName) {
		ExecuteQuery((std::string("SELECT * FROM ") + tableName + ";").c_str(), [](void* data, int argc, char** argv, char** azColName)
		{
			for (int i = 0; i < argc; i++)
				printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

			return 0;
		});
	}
}