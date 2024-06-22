#pragma once
#include <vector>

template <typename T>
class SpatialHash {
	// The size of each cell in the hash
	int m_cellSize;

	// The number of cells in the x and y directions
	int m_width, m_height;
	int m_halfWidth, m_halfHeight;
	int m_quarterWidth, m_quarterHeight;
	int m_threeQuartersWidth, m_threeQuartersHeight;

	int m_numCellsX, m_numCellsY;
	int m_quarterNumCellsX, m_quarterNumCellsY;

	// The hash table, mapping cell indices to lists of entity pointers
	std::vector<std::vector<T>> m_hash;
	std::vector<T> result;

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

	// -960, -540                            2880, -540
	//
	//          0, 0             1920, 0
	//       
	//       
	//       
	//          0, 1080         1920, 1080
	//
	// -960, 1620                            2880, 1620
	bool IsPositionValid(int posX, int posY) {
		if (posX <= -m_quarterWidth) return false;
		else if (posX >= m_threeQuartersWidth) return false;
		else if (posY <= -m_quarterHeight) return false;
		else if (posY >= m_threeQuartersHeight) return false;

		return true;
	}

	// Insert an entity into the hash
	void Insert(T entity, int posX, int posY) {
		if (!IsPositionValid(posX, posY)) 
			return;

		int cellX = posX / m_cellSize + m_quarterNumCellsX;
		int cellY = posY / m_cellSize + m_quarterNumCellsY;

		size_t cellIndex = cellY * m_numCellsX + cellX;
		m_hash[cellIndex].insert(m_hash[cellIndex].end(), entity);

		//Debug("Pushed " + std::to_string(cellX) + ", " + std::to_string(cellY) + " into the index: " + std::to_string(cellIndex));
	}

	// Remove an entity from the hash
	void Remove(T entity, int posX, int posY) {
		if (!IsPositionValid(posX, posY))
			return;

		int cellX = posX / m_cellSize + m_quarterNumCellsX;
		int cellY = posY / m_cellSize + m_quarterNumCellsY;

		size_t cellIndex = cellY * m_numCellsX + cellX;
		if (cellIndex >= m_hash.size()) return;

		auto& cell = m_hash[cellIndex];
		cell.erase(std::remove(cell.begin(), cell.end(), entity), cell.end());
	}

	// Query the hash for all entities within a certain rectangle
	std::vector<T>& Query(int x, int y, int width, int height) {
		if (!IsPositionValid(x, y)) {
			result.clear();
			return result;
		}

		// Calculate the indices of the cells in the region and also
		// Shift the cell indices by the number of cells in the negative direction
		// to ensure that they are always positive
		int minCellX = x / m_cellSize + m_quarterNumCellsX;
		int minCellY = y / m_cellSize + m_quarterNumCellsY;
		int maxCellX = (x + width) / m_cellSize + m_quarterNumCellsX;
		int maxCellY = (y + height) / m_cellSize + m_quarterNumCellsY;

		maxCellX = min(m_numCellsX - 1, maxCellX);
		maxCellY = min(m_numCellsY - 1, maxCellY);

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

	// Clear the hash table
	void Clear() { for (auto& cell : m_hash) cell.clear(); }

	// Get all the entities in the hash table
	std::vector<T> GetAll() {
		std::vector<T> result;
		result.reserve(m_cellSize); // Pre-allocate enough space for all the entities
		for (auto& cell : m_hash)
			result.insert(result.end(), cell.begin(), cell.end());
		return result;
	}
};