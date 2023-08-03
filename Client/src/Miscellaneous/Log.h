#pragma once
#include <iostream>
#include <string>

class Log {
public:
	template <typename T>
	static void Print(T msg) { std::cout << msg << std::endl; }
	template <typename T>
	static void Error(T msg) { std::cout << "[ERROR] " << msg << std::endl; }
	template <typename T>
	static void Warn(T msg) { std::cout << "[WARNING] " << msg << std::endl; }
	template <typename T>
	static void Debug(T msg) { std::cout << "[DEBUG] " << msg << std::endl; }

	Log() = delete;
};

#define Print Log::Print
#define Error Log::Error
#define Warn Log::Warn
#define Debug Log::Debug