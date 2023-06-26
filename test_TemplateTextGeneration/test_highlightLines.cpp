#include "pch.h"
#include "CppUnitTest.h"
#include "../TemplateTextGeneration/generateNewEmail.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test_highlightLines
{
	TEST_CLASS(test_highlightLines)
	{
	public:
		
		TEST_METHOD(test_allNormal)
		{
			string  testString = "#NAME#Ivan\nIvanov\n#AGE#18 years\n#LIVE#Russia,Volgograd\n#LOVE#Mom\n";
			vector<string> result = { "#NAME#Ivan\n","Ivanov\n","#AGE#18 years\n","#LIVE#Russia,Volgograd\n","#LOVE#Mom\n" };
			vector <string> test;
			test=highlightLines(testString, test);
			for (int i = 0; i < test.size(); i++)
			{
				Assert::AreEqual(test[i], result[i]);
			}
		}	
		TEST_METHOD(test_veryMultilineText)
		{
			string  testString = "#PERSON#Ivan\nIvanov\nIvanovich\nFrom\nV\nO\nL\nG\nO\nG\nR\nA\nD\n#AGE#18 years\n#LIVE#Russia,Volgograd\n#LOVE#Mom\n";
			vector<string> result = { "#PERSON#Ivan\n","Ivanov\n","Ivanovich\n","From\n","V\n","O\n","L\n","G\n","O\n","G\n","R\n","A\n","D\n",
				"#AGE#18 years\n","#LIVE#Russia,Volgograd\n","#LOVE#Mom\n" };
			vector <string> test;
			test = highlightLines(testString, test);
			for (int i = 0; i < test.size(); i++)
			{
				Assert::AreEqual(test[i], result[i]);
			}
		}
		TEST_METHOD(test_firstStringInInputDataEmpty)
		{
			string  testString = "﻿\n#AGE#18 years\n#LIVE#Russia,Volgograd\n#LOVE#Mom\n";
			vector<string> result = { "#AGE#18 years\n","#LIVE#Russia,Volgograd\n","#LOVE#Mom\n" };
			vector <string> test;
			test = highlightLines(testString, test);
			for (int i = 0; i < test.size(); i++)
			{
				Assert::AreEqual(test[i], result[i]);
			}
		}
		TEST_METHOD(test_StringInInputDataEmpty)
		{
			string  testString = "﻿#AGE#18 years\n\n\n\n\n\n\n\n\n\n\n\n\n#LIVE#Russia,Volgograd\n\n\n\n\n\n\n\n\n\n\n\n#LOVE#Mom\n";
			vector<string> result = { "#AGE#18 years\n","#LIVE#Russia,Volgograd\n","#LOVE#Mom\n" };
			vector <string> test;
			test = highlightLines(testString, test);
			for (int i = 0; i < test.size(); i++)
			{
				Assert::AreEqual(test[i], result[i]);
			}
		}
		TEST_METHOD(test_dataWithSlashN)
		{
			string  testString = "#USE#I always use \\n in my work\n#AGE#18 years\n#LIVE#Russia,Volgograd\n#LOVE#Mom\n";
			vector<string> result = { "#USE#I always use \\n in my work\n","#AGE#18 years\n","#LIVE#Russia,Volgograd\n","#LOVE#Mom\n" };
			vector <string> test;
			test = highlightLines(testString, test);
			for (int i = 0; i < test.size(); i++)
			{
				Assert::AreEqual(test[i], result[i]);
			}
		}
		
	};

}
