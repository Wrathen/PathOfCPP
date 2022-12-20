#pragma once

template <typename T>
class Singleton {
public:
	static T& GetInstance() {
		static T instance;
		return instance;
	}
};