#include <malloc.h>
#include "eocdr.h"
#include "zipreadmacro.h"

eocdr_t* eocdr_find(const uint8_t* start_ptr, const uint8_t* end_ptr)
{
    size_t comment_len = 0; //—тартова€ длина комментари€
    end_ptr -= EOCDR_BASE_SZ; // ”казатель на конец буфера смещаетс€ назад на базовый размер структуры
    uint32_t signature = 0;
    eocdr_t* result = (eocdr_t*)malloc(sizeof(eocdr_t)); // ¬ыделение пам€ти дл€ структуры конца записи центрального каталога

    while (start_ptr < end_ptr) // ¬ыполн€етс€ пока указатель на конец буфера больше указател€ на начало
    {
        if (comment_len > sizeof(uint16_t)) break; 
        READ32(signature, end_ptr);

        if (signature == EOCDR_SIGNATURE) // ѕри совпадении сигнатуры данные последовательно читаютс€ в структуру
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

            if (result->commentLength == comment_len) return result; // ѕроверка совпадени€ длины комментари€ с количеством смещений указател€ 
            else break;
        }
        else end_ptr--; // ѕри не совпадении сигнатуры указатель смещаетс€ назад на 1 байт
    }

    free(result); // ≈сли сигнатура не была найдена п€м€ть под структуру освобождаетс€ и
    return NULL; // ¬озвращаетс€ нулевой указатель 
}