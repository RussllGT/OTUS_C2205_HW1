#include <stdint.h> 

#ifndef LFH_H
#define LFH_H

#define LFH_BASE_SZ 30 // Размер структуры в байтах без учета указателей
#define LFH_SIGNATURE 0x04034b50 //Сигнатура

typedef struct
{
    uint32_t signature; // Обязательная сигнатура, равна 0x04034b50
    uint16_t versionToExtract; // Минимальная версия для распаковки
    uint16_t generalPurposeBitFlag; // Битовый флаг
    uint16_t compressionMethod; // Метод сжатия (0 - без сжатия, 8 - deflate)
    uint16_t modificationTime; // Время модификации файла
    uint16_t modificationDate; // Дата модификации файла
    uint32_t crc32; // Контрольная сумма
    uint32_t compressedSize; // Сжатый размер
    uint32_t uncompressedSize; // Несжатый размер
    uint16_t filenameLength; // Длина название файла
    uint16_t extraFieldLength; // Длина поля с дополнительными данными
    uint8_t* filename; // Название файла (размером filenameLength)
    uint8_t* extraField; // Дополнительные данные (размером extraFieldLength)
} lfh_t;

/// <summary>
/// Функция поиска начала архива
/// </summary>
/// <param name="start_ptr">Указатель на начало буфера</param>
/// <param name="end_ptr">Указатель на конец буфера</param>
/// <returns>Указатель на начало архива</returns>
uint8_t* get_zip_start_ptr(uint8_t* start_ptr, uint8_t* end_ptr);

#endif