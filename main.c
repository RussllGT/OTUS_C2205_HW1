#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <malloc.h>
#include <errno.h>
#include "zipreadmacro.h"
#include "eocdr.h"
#include "cdfh.h"
#include "lfh.h"
//1 3 5 a1

/// <summary>
/// Функция определяет размер файла
/// </summary>
/// <param name="file">Указатель на поток</param>
/// <returns>Размер фала в байтах</returns>
size_t get_file_size(FILE* file)
{
    size_t result = 0;
    while (getc(file) != EOF) result++; //Счетчик увеличивается при каждом считывании байта до тех пор пока не будет получено значение EOF
    return result;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Error: Target file not specified\n"); //Если менее 2 аргументов выдаём сообщение и закрываем программу
        return 0;
    }
    
    FILE* file = fopen(argv[1], "rb"); //Чтение файла из агрумента командной строки
    if (!file) //Если файл не существует
    {
        char* errorbuf = strerror(errno);
        fprintf(stderr, "Error: %s\n", errorbuf);
        errno = 0;
        return 0;
    }

    fpos_t start;
    fgetpos(file, &start); //Запоминаем стартовую позицию указателся на поток

    size_t len = get_file_size(file); //Находим длину файла
    uint8_t* buff = (uint8_t*)malloc(sizeof(uint8_t) * len); //Указатель на начало буфера
    uint8_t* endbuff = buff + len; //Указатель на конец буфера

    fsetpos(file, &start); //Возвращаем указатель на поток в стартовую позицию
    for (int i = 0; i < len; i++) *(buff + i) = getc(file); //Считываем байты из потока в буфер
    fclose(file); //Закрываем файл

    eocdr_t* eocdr = eocdr_find(buff, endbuff); // Указатель на конец записи центрального каталога
    if (!eocdr) // Если не удалось найти конец записи центрального каталога
    {
        printf("File isn't ZIP\n"); //Выводим на консоль сообщение
        return 0; // Выход из программы
    }

    uint8_t* zip_start = get_zip_start_ptr(buff, endbuff); // Указатель на начало архива
    if (!zip_start) // Если не удалось найти начало архива
    {
        printf("Can't find ZIP start position\n"); //Выводим на консоль сообщение
        return 0; // Выход из программы
    }

    uint8_t* cdfh_ptr = zip_start + eocdr->centralDirectoryOffset; // Указатель на начало центрального каталога в буфере
    cdfh_t* cdfh = (cdfh_t*)malloc(sizeof(cdfh_t)); // Указатель на начало текущего центрального загаловка
    for (size_t i = 0; i < eocdr->numberCentralDirectoryRecord; i++)
    {
        cdfh_ptr = cdfh_find(cdfh, cdfh_ptr); // Указатель на начало слудующего центрального загаловка
        if (!cdfh_ptr) break; // Если не удалось получить следующий центральный заголовок файла - выход из цикла
        uint16_t  len = cdfh->filenameLength;
        printf("%.*s\n", len, cdfh->filename); // Вывод на консоль информации о файле
    }

    free(cdfh); // Освобождение памяти начала текущего центрального загаловка
    free(eocdr); // Освобождение памяти записи центрального каталога
    free(buff); // Освобождение памяти буфера

	return 0;
}