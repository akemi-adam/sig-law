#include "./../unity/unity.h"
#include "./../unity/unity_internals.h"
#include "./../src/interfaces.h"

void setUp(void) {

}

void tearDown(void) {

}

#ifdef __unix__

/**
 * Testa se a função enableRawMode habilita o raw mode do terminal
 * 
 * O teste preserva a configuração original do terminal, habilita o raw mode, pega a configuração atual e verifica a diferença entre o atributo c_lflag de ambas configurações.
 * 
 * Obs.: disableRawMode é chamado para desabilitar o raw mode do terminal.
 */
void test_EnableRawMode_Works(void) {
    struct termios originalTerminal, raw;
    tcgetattr(STDIN_FILENO, &originalTerminal);
    enableRawMode();
    // struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    if (originalTerminal.c_lflag != raw.c_lflag) {
        disableRawMode(&originalTerminal);
        TEST_PASS();
    } else TEST_FAIL();
}

#endif

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
    RUN_TEST(test_EnableRawMode_Works);
    return UNITY_END();
}