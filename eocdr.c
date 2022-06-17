#include <malloc.h>
#include "eocdr.h"
#include "zipreadmacro.h"

eocdr_t* eocdr_find(const uint8_t* start_ptr, const uint8_t* end_ptr)
{
    size_t comment_len = 0; //Стартовая длина комментария
    end_ptr -= EOCDR_BASE_SZ; // Указатель на конец буфера смещается назад на базовый размер структуры
    uint32_t signature = 0;
    eocdr_t* result = (eocdr_t*)malloc(sizeof(eocdr_t)); // Выделение памяти для структуры конца записи центрального каталога

    while (start_ptr < end_ptr) // Выполняется пока указатель на конец буфера больше указателя на начало
    {
        if (comment_len > sizeof(uint16_t)) break; 
        READ32(signature, end_ptr);

        if (signature == EOCDR_SIGNATURE) // При совпадении сигнатуры данные последовательно читаются в структуру
        {
            READ32S(result->signature, end_ptr);
            READ16S(result->diskNumber, end_ptr);
            READ16S(result->startDiskNumber, end_ptr);
            READ16S(result->numberCentralDirectoryRecord, end_ptr);
            READ16S(result->totalCentralDirectoryRecord, end_ptr);
            READ32S(result->sizeOfCentralDirectory, end_ptr);
            READ32S(result->centralDirectoryOffset, end_ptr);
            READ16S(result->commentLength, end_ptr);
            READPTR(result->comment, end_ptr, result->commentLength);

            if (result->commentLength == comment_len) return result; // Проверка совпадения длины комментария с количеством смещений указателя 
            else break;
        }
        else end_ptr--; // При не совпадении сигнатуры указатель смещается назад на 1 байт
    }

    free(result); // Если сигнатура не была найдена пямять под структуру освобождается и
    return NULL; // Возвращается нулевой указатель 
}