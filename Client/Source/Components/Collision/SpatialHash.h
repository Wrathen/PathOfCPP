// Shout-out to https://chat.openai.com
// So the code here is awful. Many hours wasted with the openai, but it was fun.
// After all, I'm doing this for fun&education. Fun makes me keep going.
// Had to fix a lot of stuff that the AI gave me initially, but it was like
// Looking at someone else's code, trying to understand what's going on.
// Then spotting the issue that causing the stuff not doing what you want
// Was a nice experience. I'll never rely on the AI though, it took WAAAAY longer than it should have :D
// Instead, I can use the AI to learn or ask how to approach certain topics.
// Or even, ask whether there's some room for improvement on the code, both in style and optimization stuff.
// The suggestions it provides are INSANE. Loving it!
// #notsponsored

// Will tidy this in the future.
// I don't like the style below nor the code repeats. Looks clean, but overclustered, if that's a word.

#pragma once
#include <vector>
#include "../../Entities/Entity.h"

class SpatialHash {
public:
	// Constructor
	SpatialHash(int width, int height, int cellSize) :
		m_cellSize(cellSize),
		m_width(width),
		m_height(height),
		m_halfWidth(width / 2),
		m_halfHeight(height / 2),
		m_quarterWidth(width / 4),
		m_quarterHeight(height / 4),
		m_threeQuartersWidth(m_quarterWidth * 3),
		m_threeQuartersHeight(m_quarterHeight * 3),
		m_numCellsX(static_cast<int>(width / cellSize)),
		m_numCellsY(static_cast<int>(height / cellSize)),
		m_quarterNumCellsX(m_numCellsX / 4),
		m_quarterNumCellsY(m_numCellsY / 4),
		m_hash(m_numCellsX* m_numCellsY) {
		result.reserve(100);
	}

	void RenderDebug() {
		for (int i = 0; i < m_numCellsX; ++i)
			for (int j = 0; j < m_numCellsY; ++j)
				GAME.DrawRect(i * m_cellSize, j * m_cellSize, m_width, m_height);
	}

	// Insert an entity into the hash
	void Insert(Entity* entity) {
		auto entityPos = entity->transform.GetScreenPosition();

		// -960, -540                            2880, -540
		//
		//          0, 0             1920, 0
		//       
		//       
		//       
		//          0, 1080         1920, 1080
		//
		// -960, 1620                            2880, 1620

		if (entityPos.x <= -m_quarterWidth) return;
		else if (entityPos.x >= m_threeQuartersWidth) return;
		else if (entityPos.y <= -m_quarterHeight) return;
		else if (entityPos.y >= m_threeQuartersHeight) return;

		int cellX = entityPos.x / m_cellSize + m_quarterNumCellsX;
		int cellY = entityPos.y / m_cellSize + m_quarterNumCellsY;

		int cellIndex = cellY * m_numCellsX + cellX;
		m_hash[cellIndex].insert(m_hash[cellIndex].end(), entity);

		//Debug("Pushed " + std::to_string(cellX) + ", " + std::to_string(cellY) + " into the index: " + std::to_string(cellIndex));
	}

	// Remove an entity from the hash
	void Remove(Entity* entity) {
		auto entityPos = entity->transform.GetScreenPosition();

		if (entityPos.x <= -m_quarterWidth) return;
		else if (entityPos.x >= m_threeQuartersWidth) return;
		else if (entityPos.y <= -m_quarterHeight) return;
		else if (entityPos.y >= m_threeQuartersHeight) return;

		int cellX = entityPos.x / m_cellSize + m_quarterNumCellsX;
		int cellY = entityPos.y / m_cellSize + m_quarterNumCellsY;

		//if (cellX < 0 || cellX >= m_numCellsX) return; these shouldnt happen 'cuz we already return
		//else if (cellY < 0 || cellY >= m_numCellsY) return;

		size_t cellIndex = cellY * m_numCellsX + cellX;
		if (cellIndex >= m_hash.size()) return;
		
		auto& cell = m_hash[cellIndex];
		cell.erase(std::remove(cell.begin(), cell.end(), entity), cell.end());
	}

	// Query the hash for all entities within a certain rectangle
	std::vector<Entity*>& Query(int x, int y, int width, int height) {
		if (x <= -m_quarterWidth) return result;
		else if (x >= m_threeQuartersWidth) return result;
		else if (y <= -m_quarterHeight) return result;
		else if (y >= m_threeQuartersHeight) return result;

		// Calculate the indices of the cells in the region and also
		// Shift the cell indices by the number of cells in the negative direction
		// to ensure that they are always positive
		int minCellX = x / m_cellSize + m_quarterNumCellsX;
		int minCellY = y / m_cellSize + m_quarterNumCellsY;
		int maxCellX = (x + width) / m_cellSize + m_quarterNumCellsX;
		int maxCellY = (y + height) / m_cellSize + m_quarterNumCellsY;

		maxCellX = std::min(m_numCellsX - 1, maxCellX);
		maxCellY = std::min(m_numCellsY - 1, maxCellY);

		// Let's do some caching so we don't calculate everything from ground-up for the same requests.
		static int cachedMinCellX;
		static int cachedMaxCellX;
		static int cachedMinCellY;
		static int cachedMaxCellY;

		// Determine whether to use cached result.
		bool returnCache = (cachedMinCellX == minCellX && cachedMaxCellX == maxCellX &&
							cachedMinCellY == minCellY && cachedMaxCellY == maxCellY);

		// Update cache values.
		cachedMinCellX = minCellX;
		cachedMaxCellX = maxCellX;
		cachedMinCellY = minCellY;
		cachedMaxCellY = maxCellY;

		// If the caches are somewhat nearby the request, let's just return the cached result.
		if (returnCache)
			return result;

		// Refresh the result vector and let's build it once again from scratch.
		result.clear();

		// Iterate over the cells in the region
		for (int i = minCellX; i <= maxCellX; i++) {
			for (int j = minCellY; j <= maxCellY; j++) {
				auto& cell = m_hash[i + j * m_numCellsX];
				result.insert(result.end(), cell.begin(), cell.end());
			}
		}

		return result;
	}

	// Query the hash for all entities within a certain distance of a point
	std::vector<Entity*>& QueryRange(int x, int y, float radius) {
		result.clear();

		if (x <= -m_quarterWidth) return result;
		else if (x >= m_threeQuartersWidth) return result;
		else if (y <= -m_quarterHeight) return result;
		else if (y >= m_threeQuartersHeight) return result;

		// Determine the min and max cell indices to search
		int minCellX = (x - radius) / m_cellSize;
		int maxCellX = (x + radius) / m_cellSize;
		int minCellY = (y - radius) / m_cellSize;
		int maxCellY = (y + radius) / m_cellSize;

		// Shift the cell indices by the number of cells in the negative direction
		// to ensure that they are always positive
		minCellX += m_quarterNumCellsX;
		maxCellX += m_quarterNumCellsX;
		minCellY += m_quarterNumCellsY;
		maxCellY += m_quarterNumCellsY;

		maxCellX = std::min(m_numCellsX - 1, maxCellX);
		maxCellY = std::min(m_numCellsY - 1, maxCellY);

		// Search the cells for entities within the range
		for (int cellY = minCellY; cellY <= maxCellY; cellY++) {
			for (int cellX = minCellX; cellX <= maxCellX; cellX++) {
				int cellIndex = cellY * m_numCellsX + cellX;
				auto& cell = m_hash[cellIndex];

				for (Entity* entity : cell) {
					auto entityPos = entity->transform.GetScreenPosition();
					float dx = std::abs(entityPos.x - x);
					float dy = std::abs(entityPos.y - y);
					if (dy - dx <= radius) result.insert(result.end(), entity); // I WAS DOING PUSH_BACK [GIGA BIG ISSUE]
				}
			}
		}

		return result;
	}

	// Clear the hash table
	void Clear() { for (auto& cell : m_hash) cell.clear(); }

	// Get all the entities in the hash table
	std::vector<Entity*> GetAll() {
		std::vector<Entity*> result;
		result.reserve(m_cellSize); // Pre-allocate enough space for all the entities
		for (auto& cell : m_hash)
			result.insert(result.end(), cell.begin(), cell.end());
		return result;
	}

private:
	// The size of each cell in the hash
	int m_cellSize;

	// The number of cells in the x and y directions
	int m_width;
	int m_height;
	int m_halfWidth;
	int m_halfHeight;
	int m_quarterWidth;
	int m_quarterHeight;
	int m_threeQuartersWidth;
	int m_threeQuartersHeight;

	int m_numCellsX;
	int m_numCellsY;
	int m_quarterNumCellsX;
	int m_quarterNumCellsY;

	// The hash table, mapping cell indices to lists of entity pointers
	std::vector<std::vector<Entity*>> m_hash;
	std::vector<Entity*> result;
};