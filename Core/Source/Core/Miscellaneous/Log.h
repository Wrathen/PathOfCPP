#pragma once
#include <iostream>
#include <string>

namespace {
	template <typename T>
	static void Print(T msg) { std::cout << msg << std::endl; }
	template <typename T>
	static void Warn(T msg) { std::cout << "[WARNING] " << msg << std::endl; }
	template <typename T>
	static void Debug(T msg) { std::cout << "[DEBUG] " << msg << std::endl; }
	template <typename T>
	static void Error(T msg) { std::cout << "[Error] " << msg << std::endl; }
}