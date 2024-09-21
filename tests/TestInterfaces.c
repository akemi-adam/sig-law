#include "./../unity/unity.h"
#include "./../unity/unity_internals.h"
#include "./../src/interfaces.h"

void setUp(void) {

}

void tearDown(void) {

}

/**
 * Testa se a função setOptions de interfaces.c guarda os códigos das cores ciano (primeiro item) e reset (demais items) em um array
 */
void test_SetOptionStylesFunction_StoresCyanAndResetCodesInArray(void) {
    char optionsStyle[6][11];
    char expected[6][11] = {
        CYAN_UNDERLINE_TEXT,
        RESET_STYLE,
        RESET_STYLE,
        RESET_STYLE,
        RESET_STYLE,
        RESET_STYLE
    };
    setOptionsStyle(optionsStyle, 6);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(expected, optionsStyle, 6);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_SetOptionStylesFunction_StoresCyanAndResetCodesInArray);
    return UNITY_END();
}