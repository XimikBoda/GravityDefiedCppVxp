#pragma once
#include <filesystem>

namespace FileSystem {
	bool exists(const std::filesystem::path& path);

	bool create_directories(const std::filesystem::path& path);
}