#include "FileSystem.h"
#include <vmio.h>
namespace FileSystem {
	bool exists(const std::filesystem::path& path) {
		int atr = vm_file_get_attributes((VMWSTR)path.u16string().c_str());
		return atr >= 0;
	}

	static bool create_directorie(const std::filesystem::path& path) {
		return !vm_file_mkdir((VMWSTR)path.u16string().c_str());
	}

	bool create_directories(const std::filesystem::path& path) {
		bool is_exist = FileSystem::exists(path);
		if (is_exist)
			return true;

		bool is_parent_exist = FileSystem::exists(path.parent_path());
		if (!is_parent_exist)
			if (!FileSystem::create_directories(path.parent_path()))
				return false;

		return create_directorie(path);
	}
}