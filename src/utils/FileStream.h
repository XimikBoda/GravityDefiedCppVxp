#pragma once
#include "FileSystem.h"

#include <fstream>
#include <algorithm>
#include <filesystem>

#include <vmio.h>

class FileStream {
public:
	FileStream() {
	}

	FileStream(const std::filesystem::path& file, std::ios::openmode mode)
	{
		int vmmode = 0;
		if (mode & std::ios::in)
			vmmode |= MODE_READ;
		if (mode & std::ios::out)
			vmmode |= MODE_WRITE;

		if (vmmode & MODE_WRITE && !FileSystem::exists(file))
			vmmode = MODE_CREATE_ALWAYS_WRITE;

		handle = vm_file_open((VMWSTR)file.u16string().c_str(), vmmode, 1);
	}

	~FileStream()
	{
		vm_file_close(handle);
	}

	template <class T>
	void readVariable(T* p, bool swapEndianness = false, std::size_t size = 0)
	{
		char* pChar = reinterpret_cast<char*>(p);
		if (!size) {
			size = sizeof(T);
		}
		read_impl(pChar, size);
		if (swapEndianness) {
			std::reverse(pChar, pChar + size);
		}
	}

	template <class T>
	void writeVariable(T* p, std::size_t size = 0)
	{
		char* pChar = reinterpret_cast<char*>(p);
		if (!size) {
			size = sizeof(T);
		}
		write_impl(pChar, size);
	}

	virtual bool isOpen()
	{
		return handle >= 0;
	}

	virtual void setPos(std::streampos pos)
	{
		vm_file_seek(handle, pos, BASE_BEGIN);
	}

private:
	VMFILE handle = -1;

	virtual void read_impl(char* s, std::streamsize n)
	{
		VMUINT nread = 0;
		vm_file_read(handle, s, n, &nread);
	}

	virtual void write_impl(char* s, std::streamsize n)
	{
		VMUINT written = 0;
		vm_file_write(handle, s, n, &written);
	}
};
