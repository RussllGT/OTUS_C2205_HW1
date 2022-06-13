#include "lfh.h"
#include "zipreadmacro.h"

uint8_t* get_zip_start_ptr(const uint8_t* start_ptr, uint8_t* end_ptr)
{
    uint32_t signature; //ѕеременна€ дл€ хранении€ прочитанных данных
    do 
    {
        READ32(signature, start_ptr); //—читываем данные в текущей позиции указател€
        if (signature == LFH_SIGNATURE) return start_ptr; //¬озвращаем текущий указатель, если данные соответствуют сигнатуре локального заголовка файла
    }
    while (++start_ptr != end_ptr); // ¬ыполн€етс€, пока указатель на начало файла не совпадЄт с конечным

    return NULL; //≈сли при прохождении файла сигнатура не была обнаружена - возврат нулевого указател€
}