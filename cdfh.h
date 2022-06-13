#include <stdint.h> 

#ifndef CDFH_H
#define CDFH_H

#define CDFH_BASE_SZ 46 // ������ ��������� � ������ ��� ����� ����������
#define CDFH_SIGNATURE 0x02014b50 //���������

typedef struct
{
    uint32_t signature; // ������������ ���������, ����� 0x02014b50 
    uint16_t versionMadeBy; // ������ ��� ��������
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
    uint16_t fileCommentLength; // ����� ������������ � �����
    uint16_t diskNumber; // ����� �����
    uint16_t internalFileAttributes; // ���������� ��������� �����
    uint32_t externalFileAttributes; // ������� ��������� �����
    uint32_t localFileHeaderOffset; // �������� �� ��������� LocalFileHeader
    uint8_t* filename; // ��� ����� (������ filenameLength)
    uint8_t* extraField; // �������������� ������ (������ extraFieldLength)
    uint8_t* fileComment; // ����������� � ����� (������ fileCommentLength)
} cdfh_t;

/// <summary>
/// ���������� ��������� ������������ ��������
/// </summary>
/// <param name="cdfh">��������� �� ��������� ������������ �������� � ������� ����� ��������� ����������</param>
/// <param name="ptr">��������� �� ������ ������ � ������, ������ ����� �������� ���������</param>
/// <returns>��������� �� ������� ����� ��������� ������ � ������</returns>
uint8_t* cdfh_find(cdfh_t* cdfh, uint8_t* ptr);

#endif