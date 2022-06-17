#include "lfh.h"
#include "zipreadmacro.h"

uint8_t* get_zip_start_ptr(const uint8_t* start_ptr, uint8_t* end_ptr)
{
    uint32_t signature; //Переменная для хранениия прочитанных данных
    do 
    {
        READ32(signature, start_ptr); //Считываем данные в текущей позиции указателя
        if (signature == LFH_SIGNATURE) return start_ptr; //Возвращаем текущий указатель, если данные соответствуют сигнатуре локального заголовка файла
    }
    while (++start_ptr != end_ptr); // Выполняется, пока указатель на начало файла не совпадёт с конечным

    return NULL; //Если при прохождении файла сигнатура не была обнаружена - возврат нулевого указателя
}