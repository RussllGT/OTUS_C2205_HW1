#include <malloc.h>
#include "eocdr.h"
#include "zipreadmacro.h"

eocdr_t* eocdr_find(const uint8_t* start_ptr, const uint8_t* end_ptr)
{
    size_t comment_len = 0; //��������� ����� �����������
    end_ptr -= EOCDR_BASE_SZ; // ��������� �� ����� ������ ��������� ����� �� ������� ������ ���������
    uint32_t signature = 0;
    eocdr_t* result = (eocdr_t*)malloc(sizeof(eocdr_t)); // ��������� ������ ��� ��������� ����� ������ ������������ ��������

    while (start_ptr < end_ptr) // ����������� ���� ��������� �� ����� ������ ������ ��������� �� ������
    {
        if (comment_len > sizeof(uint16_t)) break; 
        READ32(signature, end_ptr);

        if (signature == EOCDR_SIGNATURE) // ��� ���������� ��������� ������ ��������������� �������� � ���������
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

            if (result->commentLength == comment_len) return result; // �������� ���������� ����� ����������� � ����������� �������� ��������� 
            else break;
        }
        else end_ptr--; // ��� �� ���������� ��������� ��������� ��������� ����� �� 1 ����
    }

    free(result); // ���� ��������� �� ���� ������� ������ ��� ��������� ������������� �
    return NULL; // ������������ ������� ��������� 
}