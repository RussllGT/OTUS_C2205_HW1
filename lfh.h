#include <stdint.h> 

#ifndef LFH_H
#define LFH_H

#define LFH_BASE_SZ 30 // ������ ��������� � ������ ��� ����� ����������
#define LFH_SIGNATURE 0x04034b50 //���������

typedef struct
{
    uint32_t signature; // ������������ ���������, ����� 0x04034b50
    uint16_t versionToExtract; // ����������� ������ ��� ����������
    uint16_t generalPurposeBitFlag; // ������� ����
    uint16_t compressionMethod; // ����� ������ (0 - ��� ������, 8 - deflate)
    uint16_t modificationTime; // ����� ����������� �����
    uint16_t modificationDate; // ���� ����������� �����
    uint32_t crc32; // ����������� �����
    uint32_t compressedSize; // ������ ������
    uint32_t uncompressedSize; // �������� ������
    uint16_t filenameLength; // ����� �������� �����
    uint16_t extraFieldLength; // ����� ���� � ��������������� �������
    uint8_t* filename; // �������� ����� (�������� filenameLength)
    uint8_t* extraField; // �������������� ������ (�������� extraFieldLength)
} lfh_t;

/// <summary>
/// ������� ������ ������ ������
/// </summary>
/// <param name="start_ptr">��������� �� ������ ������</param>
/// <param name="end_ptr">��������� �� ����� ������</param>
/// <returns>��������� �� ������ ������</returns>
uint8_t* get_zip_start_ptr(uint8_t* start_ptr, uint8_t* end_ptr);

#endif