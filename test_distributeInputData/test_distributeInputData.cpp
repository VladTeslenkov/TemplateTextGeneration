#include "pch.h"
#include "CppUnitTest.h"
#include "../TemplateTextGeneration/generateNewEmail.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testdistributeInputData
{
	TEST_CLASS(testdistributeInputData)
	{
	public:
		
		TEST_METHOD(test_allNormal)
		{
			string  testString = "#NAME#Ivan\nIvanov\n#AGE#18 years\n#LIVE#Russia,Volgograd\n#LOVE#Mom\n";
			vector<string> test;
			vector<string> resultTags = { "#NAME#","#AGE#","#LIVE#","#LOVE#" };
			vector <string> resultValues = { "Ivan\nIvanov\n","18 years","Russia,Volgograd","Mom" };
			vector<string>tags;
			vector<string>values;
			distributeInputData(testString, &values, &tags, test);
			for (int i = 0; i < values.size(); i++)
			{
				Assert::AreEqual(values[i], resultValues[i]);
				Assert::AreEqual(tags[i], resultTags[i]);
			}
		}
		TEST_METHOD(test_veryMultilineText)
		{
			string  testString = "#PERSON#Ivan\nIvanov\nIvanovich\nFrom\nV\nO\nL\nG\nO\nG\nR\nA\nD\n#AGE#18 years\n#LIVE#Russia,Volgograd\n#LOVE#Mom\n";
			vector<string> test;
			vector<string> resultTags = { "#PERSON#","#AGE#","#LIVE#","#LOVE#" };
			vector <string> resultValues = { "Ivan\nIvanov\nIvanovich\nFrom\nV\nO\nL\nG\nO\nG\nR\nA\nD\n","18 years","Russia,Volgograd","Mom" };
			vector<string>tags;
			vector<string>values;
			distributeInputData(testString, &values, &tags, test);
			for (int i = 0; i < values.size(); i++)
			{
				Assert::AreEqual(values[i], resultValues[i]);
				Assert::AreEqual(tags[i], resultTags[i]);
			}
		}
		TEST_METHOD(test_incorrectReturnValue)
		{
			string  testString = "#NAME#Ivan\nIvanov\n#AGE##18 years#\n#LIVE#Russia,Volgograd\n#LOVE#Mom\n";//#18 years#
			vector<string> test;
			vector<string> resultTags = { "#NAME#","#AGE#","#LIVE#","#LOVE#" };
			vector <string> resultValues = { "Ivan\nIvanov\n","18 years","Russia,Volgograd","Mom" };
			vector<string>tags;
			vector<string>values;
			int errorIndex= distributeInputData(testString, &values, &tags, test);
			//Функция возвращает 1,если данные неправильно введены
			int result = 1;
				Assert::AreEqual(errorIndex, result);
		}
		TEST_METHOD(test_returnValueOk)
		{
			string  testString = "#NAME#Ivan\nIvanov\n#AGE#18 years\n#LIVE#Russia,Volgograd\n#LOVE#Mom\n";
			vector<string> test;
			vector<string> resultTags = { "#NAME#","#AGE#","#LIVE#","#LOVE#" };
			vector <string> resultValues = { "Ivan\nIvanov\n","18 years","Russia,Volgograd","Mom" };
			vector<string>tags;
			vector<string>values;
			int errorIndex = distributeInputData(testString, &values, &tags, test);
			//Функция возвращает 1,если данные неправильно введены
			int result = 0;
			Assert::AreEqual(errorIndex, result);
		}
		TEST_METHOD(test_symbolOctothorpeInData)
		{
			string  testString = "#NAME##Ivan\nIvanov\n#AGE#18 years\n#LIVE#Russia,Volgograd\n#LOVE#Mom\n";
			vector<string> test;
			vector<string> resultTags = { "#NAME#","#AGE#","#LIVE#","#LOVE#" };
			vector <string> resultValues = { "#Ivan\nIvanov\n","18 years","Russia,Volgograd","Mom" };
			vector<string>tags;
			vector<string>values;
			int errorIndex = distributeInputData(testString, &values, &tags, test);
			//Функция возвращает 1,если данные неправильно введены
			int result = 0;
			Assert::AreEqual(errorIndex, result);
			for (int i = 0; i < values.size(); i++)
			{
				Assert::AreEqual(values[i], resultValues[i]);
				Assert::AreEqual(tags[i], resultTags[i]);
			}
		}
	};
}
