#pragma once
#include "sqlite3.h"
#include "../Miscellaneous/Singleton.h"

#define DB DatabaseManager::GetInstance()
class DatabaseManager : public Singleton<DatabaseManager> {
	friend class Singleton;
	friend class GameManager;

public:
	// Main Functions
	void PrintTable(const char* tableName);

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