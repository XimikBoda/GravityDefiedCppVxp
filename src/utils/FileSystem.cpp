#include "FileSystem.h"
#include <vmio.h>

namespace FileSystem {
	bool exists(const std::filesystem::path& path) {
		//int atr = vm_file_get_attributes((VMWSTR)path.u16string().c_str());
		//return atr >= 0;
		return 0;
	}

	static bool create_directorie(const std::filesystem::path& path) {
		//return !vm_file_mkdir((VMWSTR)path.u16string().c_str());
	}

	bool create_directories(const std::filesystem::path& path) {
		/*bool is_exist = FileSystem::exists(path);
		if (is_exist)
			return true;

		std::filesystem::path ppath = path.parent_path();
		if (ppath == path)
			return true;

		bool is_parent_exist = FileSystem::exists(ppath);
		if (!is_parent_exist)
			if (!FileSystem::create_directories(ppath))
				return false;

		return create_directorie(path);*/
		return false;
	}
}