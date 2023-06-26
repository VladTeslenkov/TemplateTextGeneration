#include "pch.h"
#include "CppUnitTest.h"
#include "../TemplateTextGeneration/generateNewEmail.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testgenerateNewEmail
{
	TEST_CLASS(testgenerateNewEmail)
	{
	public:
		
		TEST_METHOD(test_allNormal)
		{
			vector<string> testTemplate = { "Hello my name is #NAME#, I am #AGE# old.", "I come from #LIVE#.","I really love my #LOVE#" };
			vector<string> testValues;
			vector<string> testTags;
			vector<string> testStrings;
			string testDataString= "\"#NAME#Ivan\nIvanov\"\n\"#AGE#18\nyears\"\n#LIVE#Russia,Volgograd\n#LOVE#Mom\n";
			vector<string>result= { "Hello my name is Ivan\nIvanov, I am 18\nyears old.", "I come from Russia,Volgograd.","I really love my Mom" };
			generateNewEmail(&testTemplate, testValues, testTags, testDataString, testStrings);
			for (int i = 0; i < testTemplate.size(); i++)
			{
				Assert::AreEqual(testTemplate[i], result[i]);
			}
		}
		TEST_METHOD(test_noTagsInTemplate)
		{
			vector<string> testTemplate = { "Hello my name is Ivan Ivanov, I am 20 years old.", "I come from Volgograd.","I really love my mom" };
			vector<string> testValues;
			vector<string> testTags;
			vector<string> testStrings;
			string testDataString = "\"#NAME#Ivan\nIvanov\"\n\"#AGE#18\nyears\"\n#LIVE#Russia,Volgograd\n#LOVE#Mom\n";
			vector<string>result = { "Hello my name is Ivan Ivanov, I am 20 years old.", "I come from Volgograd.","I really love my mom" };
			generateNewEmail(&testTemplate, testValues, testTags, testDataString, testStrings);
			for (int i = 0; i < testTemplate.size(); i++)
			{
				Assert::AreEqual(testTemplate[i], result[i]);
			}
		}
		TEST_METHOD(test_valuesMoreThenTags)
		{
			vector<string> testTemplate = { "Hello my name is #NAME#, I am #AGE# old.", "I come from #LIVE#.","I really love my #LOVE#" };
			vector<string> testValues;
			vector<string> testTags;
			vector<string> testStrings;
			string testDataString = "\"#NAME#Ivan\nIvanov\"\n\"#AGE#18\nyears\"\n#LIVE#Russia,Volgograd\n#LOVE#Mom\n#DAY#22 june\n#SONG#Eminem\n";
			vector<string>result = { "Hello my name is Ivan\nIvanov, I am 18\nyears old.", "I come from Russia,Volgograd.","I really love my Mom" };
			generateNewEmail(&testTemplate, testValues, testTags, testDataString, testStrings);
			for (int i = 0; i < testTemplate.size(); i++)
			{
				Assert::AreEqual(testTemplate[i], result[i]);
			}
		}
		TEST_METHOD(test_templateOnlyTags)
		{
			vector<string> testTemplate = { "#NAME##AGE#", "#LIVE#","#LOVE#" };
			vector<string> testValues;
			vector<string> testTags;
			vector<string> testStrings;
			string testDataString = "\"#NAME#Ivan\nIvanov\"\n\"#AGE#18\nyears\"\n#LIVE#Russia,Volgograd\n#LOVE#Mom\n";
			vector<string>result = { "Ivan\nIvanov18\nyears", "Russia,Volgograd","Mom" };
			generateNewEmail(&testTemplate, testValues, testTags, testDataString, testStrings);
			for (int i = 0; i < testTemplate.size(); i++)
			{
				Assert::AreEqual(testTemplate[i], result[i]);
			}
		}
		TEST_METHOD(test_manyValuesToOneTag)
		{
			vector<string> testTemplate = { "Hello my name is #NAME#, I am #AGE# old.", "I come from #LIVE#.","I really love my #LOVE#" };
			vector<string> testValues;
			vector<string> testTags;
			vector<string> testStrings;
			string testDataString = "\"#NAME#Ivan\nIvanov\"\n\"#AGE#18\nyears\"\n#AGE#15 YEARS\n#LIVE#Russia,Volgograd\n#LOVE#Mom\n#NAME#Ignat Igorevich\n";
			vector<string>result = { "Hello my name is Ivan\nIvanov, I am 18\nyears old.", "I come from Russia,Volgograd.","I really love my Mom" };
			generateNewEmail(&testTemplate, testValues, testTags, testDataString, testStrings);
			for (int i = 0; i < testTemplate.size(); i++)
			{
				Assert::AreEqual(testTemplate[i], result[i]);
			}
		}
		TEST_METHOD(test_anotherTagsInTemplate)
		{
			vector<string> testTemplate = { "Hello my name is #»Ãﬂ#, I am #¬Œ«–¿—“# old.", "I come from #∆»¬”#.","I really love my #Àﬁ¡Àﬁ#" };
			vector<string> testValues;
			vector<string> testTags;
			vector<string> testStrings;
			string testDataString = "\"#NAME#Ivan\nIvanov\"\n\"#AGE#18\nyears\"\n#LIVE#Russia,Volgograd\n#LOVE#Mom\n";
			int result = 0;
			int testFunction=generateNewEmail(&testTemplate, testValues, testTags, testDataString, testStrings);
			
			Assert::AreEqual(testFunction, result);
		}
		
		TEST_METHOD(test_incorrectValues)
		{
			vector<string> testTemplate = { "Hello my name is #NAME#, I am #AGE# old.", "I come from #LIVE#.","I really love my #LOVE#" };
			vector<string> testValues;
			vector<string> testTags;
			vector<string> testStrings;
			string testDataString = "\"#NAME##Ivan\nIvanov#\"\n\"#AGE##18\nyears#\"\n#LIVE##Russia,Volgograd#\n#LOVE#Mom\n";
			int result = -1;
			int testFunction = generateNewEmail(&testTemplate, testValues, testTags, testDataString, testStrings);

			Assert::AreEqual(testFunction, result);
		}
		TEST_METHOD(test_valuesWithOctothorpe)
		{
			vector<string> testTemplate = { "Hello my name is #NAME#, I am #AGE# old.", "I come from #LIVE#.","I really love my #LOVE#" };
			vector<string> testValues;
			vector<string> testTags;
			vector<string> testStrings;
			string testDataString = "\"#NAME##Ivan\nIvanov\"\n\"#AGE#1#8\nyears\"\n#LIVE#Russia#,Volgograd\n#LOVE#Mom\n";
			int result = 1;
			int testFunction = generateNewEmail(&testTemplate, testValues, testTags, testDataString, testStrings);

			Assert::AreEqual(testFunction, result);
		}


	};
}
