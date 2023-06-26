#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "generateNewEmail.h"


using namespace std;
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    //Проверка ввода файлов
    if (argc != 4)
    {
        std::cerr << "Неправильно указаны параметры для запуска. ";
        return 1;
    }

    //Объявление переменных
    string dataString, templateString;//Строки для записи данных из выходных файлов
    vector<string> tags;//массив для меток
    vector<string> values;//массив для значений для подстановки
    vector<string> strings;//массив для строк из входных данных для подстановки
    vector<string> templateStrings;//массив для строк из входных данных с шаблоном текста


    //Файлы с входными и выходными данными
    ifstream templateFile(argv[1]);                      //входной файл с шаблоном текста
    ifstream dataFile(argv[2]);                          //входной файл с данными для подстановки
    ofstream outputFile(argv[3]);                        //выходной файл

    //Проверка на открытие файла с входными данными с шаблоном текста
    if (!templateFile.is_open()) {
        cout << "Неверно указан входной файл c шаблоном текста. Возможно, файл не существует.\n";
        return 1;
    }

    //Проверка на пустой входной файл с шаблоном текста
    if (templateFile.peek() == EOF)
    {
        cout << "Входные данные c шаблоном текста некорректны.\n";
        return 1;
    }

    //Проверка на открытие файла с входными данными для подстановки
    if (!dataFile.is_open()) 
    {
        cout << "Неверно указан входной файл с входными данными для подстановки.Возможно, файл не существует.\n";
        return 1;
    }
    //Проверка на открытие файла с выходными данными
    if (!outputFile.is_open()) 
    {
        cout << "Не получается открыть файл для записи сгенерированного текста\n";
        return 1;
    }

    //Переписываем строки из файла для подстановки в строку
    getline(dataFile, dataString, '\0');
    //Если нет входных файлов для подстановки
    if (dataString == "п»ї\n")
    {
        cout << "Неверно указан файл для выходных данных.Возможно указанного расположения не существует или нет прав на запись.\n";
        return 1;
    }
    //Проверка на длину строки
    if ((dataString.length()) > 2000)
    {
        cout << "Cлишком большая строка\n";
        return 1;
    }

    //Переписываем строки из файла с шаблоном текста в массив 
    while (templateFile)
    {
        getline(templateFile, templateString);
        templateStrings.push_back(templateString);
        //Проверка на длину строки
        if ((templateString.length()) > 2000)
        {
            cout << "Cлишком большая строка\n";
            return 1;
        }
    }
    templateStrings.pop_back();

    //Вызов главной функции 
    int indexError = generateNewEmail(&templateStrings, values, tags, dataString, strings);
    switch (indexError)
    {
    case 0:
        cout << "Входные данные для подстановки не соответствуют меткам в шаблоне текста\n";
        return 1;
    case -1:
        cout << "Входные данные для подстановки некорректны.\n";
        return 1;
    default:

        //Записываем новую строку в файл
        for (int i = 0; i < templateStrings.size(); i++)
        {
            outputFile << templateStrings[i] << "\n";
        }

        //Закрываем файлы
        templateFile.close();
        dataFile.close();
        outputFile.close();
        break;
    }
    return 0;
}

vector<string> highlightLines(string dataString, vector<string> strings)
{
    int pos;//позиция "#" в строк

    //Ищем "#"
    pos = dataString.find("#");
    //Если до начала метки есть символы,то удаляем их
    if (pos > 1)
    {
        dataString.erase(0, pos);
    }

    int posSlash;//позиция переноса строки
    //Пока в строке есть текст
    while (dataString.length() != 0)
    {
       posSlash = dataString.find("\n");//ищем перенос строки
       if (posSlash == 0)//Если строка пустая
       {
           dataString.erase(0, posSlash + 1);
       }
       else //Если перенос строки отсутствует
       {
           if (posSlash > 2000)
           {
               string line = dataString.substr(0, dataString.length());
               strings.push_back(line);
               dataString.erase(0, dataString.length());
           }
           //Разделяем текст по переносу строки и записываем в массив
           string line = dataString.substr(0, posSlash + 1);
           strings.push_back(line);
           dataString.erase(0, posSlash + 1);
       }
    }
    return strings;//возвращаем получившийся массив
}
int distributeInputData(string dataString, vector<string>* values, vector<string>* tags, vector<string> strings) 
{
    strings = highlightLines(dataString, strings);
    int index = -1;//индекс счета значений для подстановки
    for (int i = 0; i < strings.size(); i++)
    {
        string tag;//строка для записи тегов
        string value;//строка для записи значений для подстановки
        int pos = strings[i].find("#");//позиция первого символа "#" в строке
        int endTag = strings[i].find("#", pos + 1);//конец тега
        int endValue = strings[i].length();//конец значения
        
        //Проверка на корректность входных данных
        int errorPos1 = strings[i].find("#",endTag+1);
        int errorPos2;
        if (errorPos1 > 0)
        {
           errorPos2 = strings[i].find("#", errorPos1 + 1);
           if (errorPos2 > errorPos1)
           {
               return 1;
           }
        }

        if (pos == 1)
        {
            //записываем тег в массив
            tag = strings[i].substr(pos, endTag);
            tags->push_back(tag);
            //записываем значение в массив
            value = strings[i].substr(endTag + 1, endValue);
            values->push_back(value);
            index++;//увеличиваем индекс
        }
        if (pos == 0)
        {
            //записываем тег в массив
            tag = strings[i].substr(pos, endTag + 1);
            tags->push_back(tag);
            //записываем значение в массив
            value = strings[i].substr(endTag + 1, endValue);
            values->push_back(value);
            index++;//увеличиваем индекс
        }
        if (pos < 0)//тега нет в строке
        {
            endValue = strings[i].find('\"');//конец значения
            if (endValue <= 2000)
            {
                //записываем значение в массив
                string cpy = values->at(index) + strings[i].substr(0, endValue);
                values->at(index) = cpy;
            }
            else {
                //записываем значение в массив
                string cpy = values->at(index) + strings[i].substr(0, strings[i].length());
                values->at(index) = cpy;
            }
        }
    }
    //убираем лишние переносы строк
    for (int i = 0; i < values->size(); i++)
    {
        int indexSlash = (*values)[i].find('\n');
        int endValue = (*values)[i].length();
        if (indexSlash == endValue - 1)
        {
            (*values)[i].pop_back();
        }
        
    }
    return 0;
}
int generateNewEmail(vector<string>* templateStrings, vector<string>values, vector<string>tags, string dataString, vector<string> strings)
{
    if (distributeInputData(dataString, &values, &tags, strings) == 1)
    {
        return -1;
    }
    int index = 0;//Индекс замены меток
    //Для каждой строки шаблона текста
    for (int k = 0; k < templateStrings->size(); k++)
    {
        //Для каждого значения для подстановки
        for (int i = 0; i < values.size(); i++)
        {
            int positionTag;//Позиция метки
            while ((positionTag = (*templateStrings)[k].find(tags[i])) >= 0)
            {
                //Меняем метку на соответствующее значение
                if (positionTag >= 0 && positionTag < 2000)
                {
                    int endTag = (*templateStrings)[k].find("#", positionTag + 1);
                    (*templateStrings)[k].replace(positionTag, endTag - positionTag + 1, values[i]);
                    index++;
                }
            }
        }

    }
    if (index > 0)
    {
        return 1;
    }
    else 
    { 
        return 0;
    }
}