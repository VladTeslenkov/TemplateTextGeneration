/*
 * \file
 * \brief Функции, необходимые для работы с выражениями программы
 * Данный файл содержит функции программы
*/

#pragma once
#include <vector>
#include <string>
using namespace std;
/*!
 * \brief Сгенерировать новое письмо
 * \param[in,out] templateString - строки с исходным/новым шаблоном письма
 * \param[in] values - значения для подстановки
 * \param[in] tags - метки для подстановки
 * \param[in] dataString - строка с входными данными из файла для подстановок
 * \param[in] strings - массив с обработанными строками из файла для подстановок
 * \return - индекс ошибки
*/
int generateNewEmail(vector <string> *templateString, vector<string>values, vector<string>tags, string dataString, vector<string> strings);

/*!
 * \brief Разделить входные данные по переносу строки
 * \param[in] dataString - строка с входными данными из файла для подстановок
 * \param[in,out] strings - массив с обработанными строками из файла для подстановок
 * \return - массив с обработанными строками из файла для подстановок
*/
vector<string> highlightLines(string dataString, vector<string> strings);

/*!
 * \brief Разделить метки от соответствующих значений
 * \param[in,out] values - значения для подстановки
 * \param[in,out] tags - метки для подстановки
 * \param[in] dataString - строка с входными данными из файла для подстановок
 * \param[in] strings - массив с обработанными строками из файла для подстановок
 * \return - индекс ошибки
*/
int distributeInputData(string dataString, vector<string>* values, vector<string>* tags, vector<string> strings);