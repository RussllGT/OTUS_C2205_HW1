#include <stdint.h> 

#ifndef EOCDR_H
#define EOCDR_H

#define EOCDR_BASE_SZ 22 // Размер структуры в байтах без учета указателей
#define EOCDR_SIGNATURE 0x06054b50 //Сигнатура

typedef struct
{
    uint32_t signature; // Обязательная сигнатура, равна 0x06054b50
    uint16_t diskNumber; // Номер диска
    uint16_t startDiskNumber; // Номер диска, где находится начало Central Directory
    uint16_t numberCentralDirectoryRecord; // Количество записей в Central Directory в текущем диске
    uint16_t totalCentralDirectoryRecord; // Всего записей в Central Directory
    uint32_t sizeOfCentralDirectory; // Размер Central Directory
    uint32_t centralDirectoryOffset; // Смещение Central Directory
    uint16_t commentLength; // Длина комментария
    uint8_t* comment; // Комментарий (длиной commentLength)
} eocdr_t;

/// <summary>
/// Функция поиска конца записи центрального каталога
/// </summary>
/// <param name="start_ptr">Указатель на начало буфера</param>
/// <param name="end_ptr">Указатель на конец буфера</param>
/// <returns>Указатель на структуру конца записи центрального каталога</returns>
eocdr_t* eocdr_find(const uint8_t* start_ptr, const uint8_t* end_ptr);

#endif