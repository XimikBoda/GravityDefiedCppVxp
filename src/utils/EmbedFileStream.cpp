#include "EmbedFileStream.h"

#include <cstring>
#include <exception>

#include "vmres.h"

EmbedFileStream::EmbedFileStream(const std::string& embedFileName)
    : FileStream()
{
    VMINT size = 0;
    VMUINT8* res = vm_load_resource((char*)embedFileName.c_str(), &size);

    fileData.resize(size);
    std::memcpy(fileData.data(), res, size);

    vm_free(res);

    buffPos = 0;
}

void EmbedFileStream::setPos(std::streampos pos)
{
    buffPos = pos;
}

void EmbedFileStream::read_impl(char* s, std::streamsize n)
{
    std::memcpy(s, fileData.data() + buffPos, n);
    buffPos += n;
}

void EmbedFileStream::write_impl([[maybe_unused]] char* s, [[maybe_unused]] std::streamsize n)
{
    throw std::runtime_error("Write to buffer no supported!");
}

bool EmbedFileStream::isOpen()
{
    return true;
}
