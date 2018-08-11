#include "unity.h"
#include "getCMD.h"
#include "string.h"
#include "stdio.h"
#include "stdint.h"
#include "InfoVerifier.h"

void setUp(void){}
void tearDown(void){}

void test_getCMD(void)
{
    char buffer[30] = {0};
    uint8_t *Buf = "G90 X";
    uint8_t *Buf1 = "10Y";
    uint8_t *Buf2 = "20 Z30\n ";
    int a = getcommand(buffer,Buf,strlen(Buf));
    TEST_ASSERT_EQUAL(0,a);
    TEST_ASSERT_EQUAL_ARRAY(buffer,0,Buf);
    a = getcommand(buffer,Buf1,strlen(Buf1));
    TEST_ASSERT_EQUAL(0,a);
    TEST_ASSERT_EQUAL_ARRAY(buffer,strlen(Buf),Buf1);
    a = getcommand(buffer,Buf2,strlen(Buf2));
    TEST_ASSERT_EQUAL(1,a);
    TEST_ASSERT_EQUAL_ARRAY(buffer,strlen(Buf)+strlen(Buf1),Buf2);
}

void test_getCMD_with_Longest_CMD(void)
{
    char buffer[30] = {0};
    uint8_t *Buf = "G01X";
    uint8_t *Buf1 = " 10Y40 Z30";
    uint8_t *Buf2 = " F200 \r";
    int a = getcommand(buffer,Buf,strlen(Buf));
    TEST_ASSERT_EQUAL(0,a);
    TEST_ASSERT_EQUAL_ARRAY(buffer,0,Buf);
    a = getcommand(buffer,Buf1,strlen(Buf1));
    TEST_ASSERT_EQUAL(0,a);
    TEST_ASSERT_EQUAL_ARRAY(buffer,strlen(Buf),Buf1);
    a = getcommand(buffer,Buf2,strlen(Buf2));
    TEST_ASSERT_EQUAL(1,a);
    TEST_ASSERT_EQUAL_ARRAY(buffer,strlen(Buf)+strlen(Buf1),Buf2);
}

void test_getCMD_with_Long_Buf(void)
{
    char buffer[30] = {0};
    uint8_t *Buf = "G01X10 Y40.56789 Z30 F300\n\r";
    int a = getcommand(buffer,Buf,strlen(Buf));
    TEST_ASSERT_EQUAL(1,a);
    TEST_ASSERT_EQUAL_ARRAY(buffer,0,Buf);

}
