#include <stdio.h>
#include <stdint.h> 
#include <malloc.h>
#include "zipreadmacro.h"
#include "eocdr.h"
#include "cdfh.h"
#include "lfh.h"


/// <summary>
/// ������� ���������� ������ �����
/// </summary>
/// <param name="file">��������� �� �����</param>
/// <returns>������ ���� � ������</returns>
size_t get_file_size(FILE* file)
{
    size_t result = 0;
    while (getc(file) != EOF) result++; //������� ������������� ��� ������ ���������� ����� �� ��� ��� ���� �� ����� �������� �������� EOF
    return result;
}

int main(int argc, char* argv[])
{
    FILE* file = fopen(argv[1], "rb"); //������ ����� �� ��������� ��������� ������
    if (!file) //���� ���� �� ����������
    {
        printf("File doesn't exists\n"); // ������� �� ������� ���������
        return 0; // ����� �� ���������
    }

    fpos_t start;
    fgetpos(file, &start); //���������� ��������� ������� ���������� �� �����

    size_t len = get_file_size(file); //������� ����� �����
    uint8_t* buff = (uint8_t*)malloc(sizeof(uint8_t) * len); //��������� �� ������ ������
    uint8_t* endbuff = buff + len; //��������� �� ����� ������

    fsetpos(file, &start); //���������� ��������� �� ����� � ��������� �������
    for (int i = 0; i < len; i++) *(buff + i) = getc(file); //��������� ����� �� ������ � �����
    fclose(file); //��������� ����

    eocdr_t* eocdr = eocdr_find(buff, endbuff); // ��������� �� ����� ������ ������������ ��������
    if (!eocdr) // ���� �� ������� ����� ����� ������ ������������ ��������
    {
        printf("File isn't ZIP\n"); //������� �� ������� ���������
        return 0; // ����� �� ���������
    }

    uint8_t* zip_start = get_zip_start_ptr(buff, endbuff); // ��������� �� ������ ������
    if (!zip_start) // ���� �� ������� ����� ������ ������
    {
        printf("Can't find ZIP start position\n"); //������� �� ������� ���������
        return 0; // ����� �� ���������
    }

    uint8_t* cdfh_ptr = zip_start + eocdr->centralDirectoryOffset; // ��������� �� ������ ������������ �������� � ������
    cdfh_t* cdfh = (cdfh_t*)malloc(sizeof(cdfh_t)); // ��������� �� ������ �������� ������������ ���������
    for (size_t i = 0; i < eocdr->numberCentralDirectoryRecord; i++)
    {
        cdfh_ptr = cdfh_find(cdfh, cdfh_ptr); // ��������� �� ������ ���������� ������������ ���������
        if (!cdfh_ptr) break; // ���� �� ������� �������� ��������� ����������� ��������� ����� - ����� �� �����
        printf("%s\n", cdfh->filename); // ����� �� ������� ���������� � �����
    }

    free(cdfh); // ������������ ������ ������ �������� ������������ ���������
    free(eocdr); // ������������ ������ ������ ������������ ��������
    free(buff); // ������������ ������ ������

	return 0;
}