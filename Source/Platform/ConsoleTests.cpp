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

void setupFileScanTest(const char* const fileName, const char* strings[], size_t stringCount)
{
	std::ofstream fileToCheck(fileName);
	
	for (size_t i = 0; i < stringCount; i++)
	{
		fileToCheck << strings[i];
	}

	fileToCheck.close();
}

 TEST(PlatformConsoleTest, CheckScanFromFile )
 {
	 const char* const fileName = "scan_test1.txt";
	 const char* strings[] = { "testing123", "\n", "54321" };
	 setupFileScanTest(fileName, strings, 3);

	 FILE* fileToScan = fopen(fileName, "r");

	 char scanedText[64];
	 int res = FileScan(fileToScan, "%s", scanedText);
	 ASSERT_TRUE(res == 1);
	 ASSERT_TRUE(strcmp(strings[0], scanedText) == 0);

	 int num = 0;
	 res = FileScan(fileToScan, "%d", &num);
	 ASSERT_TRUE(res == 1);
	 ASSERT_TRUE(num == 54321);
	 fclose(fileToScan);

	 remove(fileName);
 }

 TEST(PlatformConsoleTest, CheckScanFromFile2)
 {
	 const char* const fileName = "scan_test2.txt";

	 // the only diferentce between CheckScanFromFile test
	 const char* strings[] = { "testing123", " " /*no new line*/, "54321" };
	 setupFileScanTest(fileName, strings, 3);

	 FILE* fileToScan = fopen(fileName, "r");

	 char scanedText[64];
	 int res = FileScan(fileToScan, "%s", scanedText);
	 ASSERT_TRUE(res == 1);
	 ASSERT_TRUE(strcmp(strings[0], scanedText) == 0);

	 int num = 0;
	 res = FileScan(fileToScan, "%d", &num);
	 ASSERT_TRUE(res == 0);
	 ASSERT_TRUE(num == 0);
	 fclose(fileToScan);

	 remove(fileName);
 }

 TEST(PlatformConsoleTest, CheckScanFromFile3)
 {
	 const char* const fileName = "scan_test2.txt";

	 // the only diferentce between CheckScanFromFile test
	 const char* strings[] = { "testing123", " " /*no new line*/, "54321" };
	 setupFileScanTest(fileName, strings, 3);

	 FILE* fileToScan = fopen(fileName, "r");

	 char scanedText[64];
	 int res = FileScan(fileToScan, "", scanedText);
	 fclose(fileToScan);

	 remove(fileName);
 }

 TEST(PlatformConsoleTest, CheckStringScan)
 {
	 int num = 0;
	 char str[10];
	 StringScan("9876 foobar", "%d %s", &num, str);

	 ASSERT_TRUE(num == 9876);
	 ASSERT_TRUE(strcmp(str, "foobar") == 0);
 }

#if HELIUM_ASSERT_ENABLED 
TEST(PlatformConsoleTest, FailOnWCharScan)
{
	ASSERT_DEATH(Scan(L""), "");
}

TEST(PlatformConsoleTest, CheckScanFromNullFile)
{
	FILE* fileToScan = nullptr;
	char scanedText[64];
	ASSERT_DEATH(FileScan(fileToScan, "%s", scanedText), "");
}

TEST(PlatformConsoleTest, FailOnWCharFileScan)
{
	ASSERT_DEATH(FileScan(nullptr, L""), "");
}
#endif