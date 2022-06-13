#include <stdint.h> 

#ifndef CDFH_H
#define CDFH_H

#define CDFH_BASE_SZ 46 // Размер структуры в байтах без учета указателей
#define CDFH_SIGNATURE 0x02014b50 //Сигнатура

typedef struct
{
    uint32_t signature; // Обязательная сигнатура, равна 0x02014b50 
    uint16_t versionMadeBy; // Версия для создания
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
    uint16_t fileCommentLength; // Длина комментариев к файлу
    uint16_t diskNumber; // Номер диска
    uint16_t internalFileAttributes; // Внутренние аттрибуты файла
    uint32_t externalFileAttributes; // Внешние аттрибуты файла
    uint32_t localFileHeaderOffset; // Смещение до структуры LocalFileHeader
    uint8_t* filename; // Имя файла (длиной filenameLength)
    uint8_t* extraField; // Дополнительные данные (длиной extraFieldLength)
    uint8_t* fileComment; // Комментарий к файла (длиной fileCommentLength)
} cdfh_t;

/// <summary>
/// Извлечение структуры центрального каталога
/// </summary>
/// <param name="cdfh">Указатель на структуру центрального каталога в которой будет сохранена информация</param>
/// <param name="ptr">Указатель на начало данных в буфере, откуда будет читаться структура</param>
/// <returns>Указатель на область после окончания данных в буфере</returns>
uint8_t* cdfh_find(cdfh_t* cdfh, uint8_t* ptr);

#endif