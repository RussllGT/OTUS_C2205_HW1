#include <stdbool.h>
#include <malloc.h>
#include "eocdr.h"
#include "zipreadmacro.h"

bool eocdr_find(eocdr_t* eocdr, const uint8_t* start_ptr, const uint8_t* end_ptr)
{
    size_t comment_len = 0; //Стартовая длина комментария
    end_ptr -= EOCDR_BASE_SZ; // Указатель на конец буфера смещается назад на базовый размер структуры
    uint32_t signature = 0;

    while (start_ptr < end_ptr) // Выполняется пока указатель на конец буфера больше указателя на начало
    {
        if (comment_len > sizeof(uint16_t)) break;
        READ32(signature, end_ptr);

        if (signature == EOCDR_SIGNATURE) // При совпадении сигнатуры данные последовательно читаются в структуру
        {
            READ32S(eocdr->signature, end_ptr);
            READ16S(eocdr->diskNumber, end_ptr);
            READ16S(eocdr->startDiskNumber, end_ptr);
            READ16S(eocdr->numberCentralDirectoryRecord, end_ptr);
            READ16S(eocdr->totalCentralDirectoryRecord, end_ptr);
            READ32S(eocdr->sizeOfCentralDirectory, end_ptr);
            READ32S(eocdr->centralDirectoryOffset, end_ptr);
            READ16S(eocdr->commentLength, end_ptr);
            READPTR(eocdr->comment, end_ptr, eocdr->commentLength);

            if (eocdr->commentLength == comment_len) return true; // Проверка совпадения длины комментария с количеством смещений указателя 
            else return false;
        }
        else end_ptr--; // При не совпадении сигнатуры указатель смещается назад на 1 байт
    }

    return false; // Возвращается нулевой указатель 
}