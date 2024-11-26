#include "./../../unity/unity.h"
#include "./../../unity/unity_internals.h"
#include "./../../src/utils/date.h"

void setUp(void) {

}

void tearDown(void) {

}

/**
 * Verifica se a função loadDatetime consegue armazenar os valores corretos em datetime
 */
void test_loadDatetime_should_ParseDateAndTimeCorrectly(void) {
    Datetime datetime;
    const char *date = "25/12/2024";
    const char *time = "18:30";

    loadDatetime(&datetime, date, time);

    TEST_ASSERT_EQUAL_INT(2024, datetime.year);
    TEST_ASSERT_EQUAL_INT(12, datetime.month);
    TEST_ASSERT_EQUAL_INT(25, datetime.day);
    TEST_ASSERT_EQUAL_INT(18, datetime.hour);
    TEST_ASSERT_EQUAL_INT(30, datetime.minute);
    TEST_ASSERT_EQUAL_STRING("25/12/2024 18:30", datetime.date);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_loadDatetime_should_ParseDateAndTimeCorrectly);
    return UNITY_END();
}
