#include "./../../unity/unity.h"
#include "./../../unity/unity_internals.h"
#include "./../../src/utils/interfaces.h"
#ifdef __unix__
    #include <termios.h>
    #include <unistd.h>
#endif

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
    tcgetattr(STDIN_FILENO, &raw);
    if (originalTerminal.c_lflag != raw.c_lflag) {
        disableRawMode(&originalTerminal);
        TEST_PASS();
    } else TEST_FAIL();
}

/**
 * Testa se a função disableRawMode desabilita o raw mode
 * 
 * O teste simula a situação onde a configuração original do terminal é preservada, o raw mode é habilitado e depois desabilitado. Após tal, o teste pega a configuração atual do terminal e verifica a igualdade do atributo c_lflag de ambas configurações.
 */
void test_DisableRawMode_Works(void) {
    struct termios originalTerminal, current;
    tcgetattr(STDIN_FILENO, &originalTerminal);
    enableRawMode();
    disableRawMode(&originalTerminal);
    tcgetattr(STDIN_FILENO, &current);
    if (originalTerminal.c_lflag == current.c_lflag) {
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
        CYAN_STYLE,
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
    RUN_TEST(test_DisableRawMode_Works);
    return UNITY_END();
}