#pragma once
#include <iostream>
#include <vector>

template <typename T>
struct NewSpatialHash {
	std::vector<std::vector<T>> objects;
	size_t cellSize;
	size_t worldSize;

	NewSpatialHash(size_t _worldSize, size_t _cellSize) {
		cellSize = _cellSize;
		worldSize = _worldSize;

		objects = std::vector<std::vector<T>>((worldSize / cellSize) * (worldSize / cellSize), std::vector<T>());
	}

	size_t ToIndex(int x, int y) { return (y / cellSize) * (worldSize / cellSize) + x / cellSize; }
	bool IsPositionValid(int x, int y, float radius = 0) {
		if (x < 0 || y < 0 || x > (int)worldSize || y > (int)worldSize || radius < 0) {
			std::cout << "[Error] NewSpatialHash received faulty parameters. " << x << " , " << y << " , " << radius << "\n";
			return false;
		}

		return true;
	}

	void Add(T object, int x, int y) {
		if (!IsPositionValid(x, y))
			return;

		objects[ToIndex(x, y)].push_back(object);
	}
	void Add(T object, int x, int y, int w, int h) {
		if (!IsPositionValid(x, y))
			return;

		if (x + w >= (int)worldSize || y + h >= (int)worldSize || w < 0 || h < 0) {
			std::cout << "[Error] NewSpatialHash::Add(w, h) received faulty parameters." << x << " , " << y << " , " << w << " , " << h << " , " << "\n";
			return;
		}

		for (int i = x; i <= x + w; i = ((i / cellSize) + 1) * cellSize + 1)
			for (int j = y; j <= y + h; j = ((j / cellSize) + 1) * cellSize + 1)
				Add(object, i, j);
	}
	void Remove(T object, int x, int y) {
		if (!IsPositionValid(x, y))
			return;

		auto& arr = objects[ToIndex(x, y)];
		for (auto it = arr.rbegin(); it != arr.rend(); ++it)
			if (*it == object)
				arr.erase(it);
	}
	std::vector<T> Query(int x, int y, float radius) {
		std::vector<T> result = std::vector<T>();

		if (!IsPositionValid(x, y, radius))
			return result;

		for (size_t i = x - (size_t)radius; i <= x + (size_t)radius; i += cellSize)
			for (size_t j = y - (size_t)radius; j <= y + (size_t)radius; j += cellSize)
				result.insert(result.end(), objects[ToIndex(i, j)].begin(), objects[ToIndex(i, j)].end());

		return result;
	}

	void Clear() {
		objects.clear();
		objects = std::vector<std::vector<T>>((worldSize / cellSize) * (worldSize / cellSize), std::vector<T>());
	}
};