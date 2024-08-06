#include "pch.h"
#include "CppUnitTest.h"
#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
extern int APIENTRY IsModuleLoaded(char*);


BEGIN_TEST_MODULE_ATTRIBUTE()
TEST_MODULE_ATTRIBUTE(L"Date", L"2014/6/21")
END_TEST_MODULE_ATTRIBUTE()


namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(Test_IsModuleLoaded)
		{
			IsModuleLoaded("adb.exe");
			IsModuleLoaded("C:\\Program Files\\Simple\\Bin\\platform-tools\\adb.exe");
		}
	};
}
