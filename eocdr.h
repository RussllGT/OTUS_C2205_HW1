#include <stdint.h> 

#ifndef EOCDR_H
#define EOCDR_H

#define EOCDR_BASE_SZ 22 // ������ ��������� � ������ ��� ����� ����������
#define EOCDR_SIGNATURE 0x06054b50 //���������

typedef struct
{
    uint32_t signature; // ������������ ���������, ����� 0x06054b50
    uint16_t diskNumber; // ����� �����
    uint16_t startDiskNumber; // ����� �����, ��� ��������� ������ Central Directory
    uint16_t numberCentralDirectoryRecord; // ���������� ������� � Central Directory � ������� �����
    uint16_t totalCentralDirectoryRecord; // ����� ������� � Central Directory
    uint32_t sizeOfCentralDirectory; // ������ Central Directory
    uint32_t centralDirectoryOffset; // �������� Central Directory
    uint16_t commentLength; // ����� �����������
    uint8_t* comment; // ����������� (������ commentLength)
} eocdr_t;

/// <summary>
/// ������� ������ ����� ������ ������������ ��������
/// </summary>
/// <param name="start_ptr">��������� �� ������ ������</param>
/// <param name="end_ptr">��������� �� ����� ������</param>
/// <returns>��������� �� ��������� ����� ������ ������������ ��������</returns>
eocdr_t* eocdr_find(const uint8_t* start_ptr, const uint8_t* end_ptr);

#endif