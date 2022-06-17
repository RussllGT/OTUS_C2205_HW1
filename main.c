#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <malloc.h>
#include <errno.h>
#include <sys\stat.h>
//#include <unistd.h>
#include "zipreadmacro.h"
#include "eocdr.h"
#include "cdfh.h"
#include "lfh.h"

int main(int argc, char* argv[])
{
    //Если менее 2 аргументов выдаём сообщение и закрываем программу
    if (argc < 2)
    {
        printf("Error: Target file not specified\n"); 
        return 0;
    }
    
    //Чтение файла из агрумента командной строки. В случае ошибки - выводим сообщение и закрываем программу
    FILE* file = fopen(argv[1], "rb"); 
    if (!file)
    {
        char* errorbuf = strerror(errno);
        fprintf(stderr, "Error: %s\n", errorbuf);
        errno = 0;
        return 0;
    }

    //Получаем размер файла через структуру данных о файле
    struct stat filestat; 
    stat(argv[1], &filestat);
    size_t len = filestat.st_size;  

    //Проверяем, что переданная сущност ьявляется файлом
    /*if (S_ISREG(filestat.st_mode) == 0)
    {
        printf("Error: Target path is not a file\n");
        return 0;
    }*/


    //Читаем файл в буфер и закрываем файл
    uint8_t* buff = (uint8_t*)malloc(sizeof(uint8_t)*len);
    uint8_t* endbuff = buff + len;
    for (int i = 0; i < len; i++) *(buff + i) = getc(file);
    fclose(file);

    //Получаем структуру конца записи центрального каталога
    //Если не удалось найти конец записи центрального каталога - сообщение и выход
    eocdr_t eocdr; 
    if (!eocdr_find(&eocdr, buff, endbuff)) 
    {
        printf("File isn't ZIP\n");
        return 0;
    }

    //Получаем указатель на начало архива
    //Если не удалось найти начало архива - сообщение и выход
    uint8_t* zip_start = get_zip_start_ptr(buff, endbuff);
    if (!zip_start) 
    {
        printf("Can't find ZIP start position\n");
        return 0;
    }

    //Получаем указатель на начало центрального каталога в буфере
    uint8_t* cdfh_ptr = zip_start + eocdr.centralDirectoryOffset;

    //Последовательно выводим данные о каждом центральном каталоге
    for (size_t i = 0; i < eocdr.numberCentralDirectoryRecord; i++)
    {
        cdfh_t cdfh;
        cdfh_ptr = cdfh_find(&cdfh, cdfh_ptr); // Указатель на начало слудующего центрального загаловка
        if (!cdfh_ptr) break; // Если не удалось получить следующий центральный заголовок файла - выход из цикла
        printf("%.*s\n", cdfh.filenameLength, cdfh.filename);
    }

    //Освобождение памяти буфера
    free(buff); 

	return 0;
}