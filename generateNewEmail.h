/*
 * \file
 * \brief �������, ����������� ��� ������ � ����������� ���������
 * ������ ���� �������� ������� ���������
*/

#pragma once
#include <vector>
#include <string>
using namespace std;
/*!
 * \brief ������������� ����� ������
 * \param[in,out] templateString - ������ � ��������/����� �������� ������
 * \param[in] values - �������� ��� �����������
 * \param[in] tags - ����� ��� �����������
 * \param[in] dataString - ������ � �������� ������� �� ����� ��� �����������
 * \param[in] strings - ������ � ������������� �������� �� ����� ��� �����������
 * \return - ������ ������
*/
int generateNewEmail(vector <string> *templateString, vector<string>values, vector<string>tags, string dataString, vector<string> strings);

/*!
 * \brief ��������� ������� ������ �� �������� ������
 * \param[in] dataString - ������ � �������� ������� �� ����� ��� �����������
 * \param[in,out] strings - ������ � ������������� �������� �� ����� ��� �����������
 * \return - ������ � ������������� �������� �� ����� ��� �����������
*/
vector<string> highlightLines(string dataString, vector<string> strings);

/*!
 * \brief ��������� ����� �� ��������������� ��������
 * \param[in,out] values - �������� ��� �����������
 * \param[in,out] tags - ����� ��� �����������
 * \param[in] dataString - ������ � �������� ������� �� ����� ��� �����������
 * \param[in] strings - ������ � ������������� �������� �� ����� ��� �����������
 * \return - ������ ������
*/
int distributeInputData(string dataString, vector<string>* values, vector<string>* tags, vector<string> strings);