#include "cdfh.h"
#include "zipreadmacro.h"


uint8_t* cdfh_find(cdfh_t* cdfh, uint8_t* ptr)
{
    uint32_t signature = 0;
    READ32(signature, ptr); // Чтение сигнатуры

    if (signature == CDFH_SIGNATURE) // При совпадении сигнатуры данные последовательно читаются в структуру
    {
        READ32S(cdfh->signature, ptr);
        READ16S(cdfh->versionMadeBy, ptr);
        READ16S(cdfh->versionToExtract, ptr);
        READ16S(cdfh->generalPurposeBitFlag, ptr);
        READ16S(cdfh->compressionMethod, ptr);
        READ16S(cdfh->modificationTime, ptr);
        READ16S(cdfh->modificationDate, ptr);
        READ32S(cdfh->crc32, ptr);
        READ32S(cdfh->compressedSize, ptr);
        READ32S(cdfh->uncompressedSize, ptr);
        READ16S(cdfh->filenameLength, ptr);
        READ16S(cdfh->extraFieldLength, ptr);
        READ16S(cdfh->fileCommentLength, ptr);
        READ16S(cdfh->diskNumber, ptr);
        READ16S(cdfh->internalFileAttributes, ptr);
        READ32S(cdfh->externalFileAttributes, ptr);
        READ32S(cdfh->localFileHeaderOffset, ptr);
        READPTR(cdfh->filename, ptr, cdfh->filenameLength);
        READPTR(cdfh->extraField, ptr, cdfh->extraFieldLength);
        READPTR(cdfh->fileComment, ptr, cdfh->fileCommentLength);

        return ptr; // Возврат указателся смещенного к области после прочитанных данных
    }

    return NULL; // При несовпадении сигнатуры возврат нулевого указателя
}