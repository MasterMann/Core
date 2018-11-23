#include "Precompile.h"

#include "Platform/Console.h"
#include "Platform/Assert.h"

#include "gtest/gtest.h"

#include <fstream>
#include <iostream>
//#include <sstream>
#include <stdio.h>

using namespace Helium;

TEST( PlatformConsoleTest, Scan )
{
	// ToDo: Think of a way to redirect the stdcin in this test

	//std::istringstream ss("test");
	//std::cin.rdbuf(ss.rdbuf());

	/*std::stringbuf s;
	const char *userInput = "10 1 2 3 4 5 6 7 8 9 10 3 7";
	s.sputn(userInput, strlen(userInput));
	std::cin.rdbuf(&s);

	int i;
	std::cin >> i;

	std::cout << "out put " << i << "\n";

	char str [80];
	Scan("%s",str); 
	scanf("%79s", str);
	printf("You entered %s", str);*/

	ASSERT_FALSE( false);
}

 TEST(PlatformConsoleTest, CheckScanFromFile )
 {
	 const char* const fileName = "scan_test1.txt";
	 std::ofstream fileToCheck(fileName);
	 const char* const testString = "testing123";
	 const char* const testString2 = " 54321";
	 fileToCheck << testString << testString2;
	 fileToCheck.close();

	 FILE* fileToScan = fopen(fileName, "r");
	 char scanedText[64];
	 int res = FileScan(fileToScan, "%s", scanedText);

	 remove(fileName);

 	 ASSERT_TRUE(res == 1);
	 ASSERT_TRUE(strcmp(testString, scanedText) == 0);
 }

 TEST(PlatformConsoleTest, CheckScanFromFile2)
 {
	 /*const char* const fileName = "scan_test1.txt";
	 std::ofstream fileToCheck(fileName);
	 const char* const testString = "testing123";
	 const char* const testString2 = " 54321";
	 fileToCheck << testString << testString2;
	 fileToCheck.close();

	 FILE* fileToScan = fopen(fileName, "r");
	 char scanedText[64];
	 int res = FileScan(fileToScan, "%s", scanedText);

	 remove(fileName);

	 ASSERT_TRUE(res == 1);
	 ASSERT_TRUE(strcmp(testString, scanedText) == 0);*/
 }

#if HELIUM_ASSERT_ENABLED 
TEST(PlatformConsoleTest, FailOnWCharScan)
{
	ASSERT_DEATH(Scan(L""), "");
}
#endif