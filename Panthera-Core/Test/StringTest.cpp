#include <gtest/gtest.h>

#include "Panthera/Core/StringBase.hpp"

using namespace Panthera;

TEST(StringAssignTest, StringTest)
{
    String str = "Hello World!";
    String str2 = "Hello World!";
    ASSERT_EQ(str.GetLength(), 12);
    ASSERT_TRUE(str == str2);
}

TEST(StringAppendTest, StringTest)
{
    String str = "Hello";
    str += " World!";
    ASSERT_TRUE(str == "Hello World!");
}

TEST(StringAppendTest, StringTest2)
{
    String str = "Hello";
    str += " World!";
    str += " This is a test!";
    ASSERT_TRUE(str == "Hello World! This is a test!");
}

TEST(StringAppendTest, StringTest3)
{
    String str = "Hello";
    str.Append(" World!");
    str.Append(" This is a test!");
    ASSERT_TRUE(str == "Hello World! This is a test!");
}

TEST(StringWCharTest, StringTest)
{
    WString str = L"Hello World!";
    ASSERT_TRUE(str == L"Hello World!");
}

TEST(StringWCharAppendTest, StringTest)
{
    WString str = L"Hello World!";
    str += L" This is a test!";
    ASSERT_TRUE(str == L"Hello World! This is a test!");
}

TEST(StringWCharAppendTest, StringTest2)
{
    WString str = L"Hello World!";
    str.Append(L" This is a test!");
    ASSERT_TRUE(str == L"Hello World! This is a test!");
}

TEST(StringFindTest, StringTest)
{
    String str = "Hello World!";
    ASSERT_EQ(str.Find("World"), 6);
}

TEST(StringFindTest, StringTest2)
{
    String str = "Hello World!";
    ASSERT_EQ(str.Find("World_"), -1);
}

TEST(StringFindTest, StringTest3)
{
    String str = "Hello World!";
    ASSERT_EQ(str.Find("Hello"), 0);
}

TEST(StringFindTest, StringTest4)
{
    String str = "Hello World! World!";
    ASSERT_EQ(str.FindLast("World!"), 13);
}

TEST(StringFindTest, StringTest6)
{
    String str = "Hello World! World!";
    ASSERT_EQ(str.FindLast("Hello"), 0);
}

TEST(StringFindTest, StringTest7)
{
    String str = "Hello World! World!";
    ASSERT_EQ(str.Find("World"), 6);
}

TEST(StringReplaceTest, StringTest)
{
    String str = "Hello World!";
    str.Replace("World", "Panthera");
    ASSERT_TRUE(str == "Hello Panthera!");
}

TEST(StringReplaceTest, StringTest2)
{
    String str = "Hello World!";
    str.Replace("World", "Panthera");
    str.Replace("Panthera", "World");
    ASSERT_TRUE(str == "Hello World!");
}

TEST(StringReplaceTest, StringTest3)
{
    String str = "Hello World!";
    str.Replace("World", "Panthera");
    str.Replace("Panthera", "World");
    str.Replace("World", "Panthera");
    ASSERT_TRUE(str == "Hello Panthera!");
}

TEST(StringSubStringTest, StringTest)
{
    String str = "Hello World!";
    ASSERT_TRUE(str.Substring(6, 5) == "World");
}

TEST(StringSubStringTest, StringTest2)
{
    String str = "Hello World!";
    ASSERT_TRUE(str.Substring(0, 5) == "Hello");
}

TEST(StringSubStringTest, StringTest3)
{
    String str = "Hello World!";
    ASSERT_TRUE(str.Substring(6, 11) == "World!");
}

TEST(StringSubStringTest, StringTest4)
{
    String str = "Hello Hello Hello Hello";
    String str2 = str.SubstringLast("Hello");
    ASSERT_TRUE(str2 == "Hello Hello Hello ");
}