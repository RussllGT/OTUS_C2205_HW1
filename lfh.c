#include "lfh.h"
#include "zipreadmacro.h"

uint8_t* get_zip_start_ptr(const uint8_t* start_ptr, uint8_t* end_ptr)
{
    uint32_t signature; //���������� ��� ��������� ����������� ������
    do 
    {
        READ32(signature, start_ptr); //��������� ������ � ������� ������� ���������
        if (signature == LFH_SIGNATURE) return start_ptr; //���������� ������� ���������, ���� ������ ������������� ��������� ���������� ��������� �����
    }
    while (++start_ptr != end_ptr); // �����������, ���� ��������� �� ������ ����� �� ������� � ��������

    return NULL; //���� ��� ����������� ����� ��������� �� ���� ���������� - ������� �������� ���������
}