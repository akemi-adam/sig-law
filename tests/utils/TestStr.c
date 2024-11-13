#include "./../../unity/unity.h"
#include "./../../unity/unity_internals.h"
#include "./../../src/utils/str.h"
#include <stdbool.h>


void setUp(void) {
    // Executado antes de cada teste, se necessário
}

void tearDown(void) {
    // Executado após cada teste, se necessário
}

/* Testa se o caractere é identificado como acentuado
 *
 * Authors:
 * - ChatGPT
 */
void test_isAccentedChar_should_return_true_for_accented_chars(void) {
    const char* accented_char = "áçÔ";
    TEST_ASSERT_TRUE(isAccentedChar(accented_char[0]));
    TEST_ASSERT_TRUE(isAccentedChar(accented_char[1]));
    TEST_ASSERT_TRUE(isAccentedChar(accented_char[2]));
}

/* Testa se o caractere é identificado como não acentuado
 *
 * Authors:
 * - ChatGPT
 */
void test_isAccentedChar_should_return_false_for_non_accented_chars(void) {
    TEST_ASSERT_FALSE(isAccentedChar('a'));
    TEST_ASSERT_FALSE(isAccentedChar('C'));
    TEST_ASSERT_FALSE(isAccentedChar('X'));
}

/* Testa a contagem de acentos em uma string contendo caracteres acentuados
 *
 * Authors:
 * - ChatGPT
 */
void test_countAccents_should_count_accented_chars_correctly(void) {
    TEST_ASSERT_EQUAL_INT(3, countAccents("olááá")); 
    TEST_ASSERT_EQUAL_INT(2, countAccents("coração"));              
    TEST_ASSERT_EQUAL_INT(4, countAccents("ãéïü"));                 
}

/* Testa a contagem de acentos em uma string sem caracteres acentuados
 *
 * Authors:
 * - ChatGPT
 */
void test_countAccents_should_return_zero_for_non_accented_string(void) {
    TEST_ASSERT_EQUAL_INT(0, countAccents("hello"));
    TEST_ASSERT_EQUAL_INT(0, countAccents("abcdefg"));
    TEST_ASSERT_EQUAL_INT(0, countAccents("12345"));
}

/* Testa a conversão de string para int com valor válido
 *
 * Authors:
 * - ChatGPT
 */
void test_parseInt_should_convert_valid_string_to_int(void) {
    int result;
    TEST_ASSERT_TRUE(parseInt("123", &result));
    TEST_ASSERT_EQUAL_INT(123, result);

    TEST_ASSERT_TRUE(parseInt("012", &result));
    TEST_ASSERT_EQUAL_INT(12, result);

    TEST_ASSERT_TRUE(parseInt("-456", &result));
    TEST_ASSERT_EQUAL_INT(-456, result);
}

/* Testa a conversão de string para int com valor inválido
 *
 * Authors:
 * - ChatGPT
 */
void test_parseInt_should_return_false_for_invalid_string(void) {
    int result;
    TEST_ASSERT_FALSE(parseInt("abc", &result));
    TEST_ASSERT_FALSE(parseInt("123abc", &result));
    TEST_ASSERT_FALSE(parseInt("", &result));
}

/* Testa a conversão de string para double com valor válido
 *
 * Authors:
 * - ChatGPT
 */
void test_parseDouble_should_convert_valid_string_to_double(void) {
    double result;
    TEST_ASSERT_TRUE(parseDouble("123.45", &result));
    TEST_ASSERT(result == 123.45);

    TEST_ASSERT_TRUE(parseDouble("-678.90", &result));
    TEST_ASSERT(result == -678.90);
}

/* Testa a conversão de string para double com valor inválido
 *
 * Authors:
 * - ChatGPT
 */
void test_parseDouble_should_return_false_for_invalid_string(void) {
    double result;
    TEST_ASSERT_FALSE(parseDouble("abc", &result));
    TEST_ASSERT_FALSE(parseDouble("123.45abc", &result));
    TEST_ASSERT_FALSE(parseDouble("", &result));
}

/**
 * Testa a função que verifica se uma string começa ou termina com espaços
 * 
 * Authors:
 *  - https://github.com/akemi-adam
 */
void test_hasInvalidSpaces_function(void) {
    TEST_ASSERT_TRUE(hasInvalidSpaces(" Teste"));
    TEST_ASSERT_TRUE(hasInvalidSpaces("Teste "));
    TEST_ASSERT_TRUE(hasInvalidSpaces(" Teste "));
    TEST_ASSERT_FALSE(hasInvalidSpaces("Teste"));
}


int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_isAccentedChar_should_return_true_for_accented_chars);
    RUN_TEST(test_isAccentedChar_should_return_false_for_non_accented_chars);
    RUN_TEST(test_countAccents_should_count_accented_chars_correctly);
    RUN_TEST(test_countAccents_should_return_zero_for_non_accented_string);
    RUN_TEST(test_parseInt_should_convert_valid_string_to_int);
    RUN_TEST(test_parseInt_should_return_false_for_invalid_string);
    RUN_TEST(test_parseDouble_should_convert_valid_string_to_double);
    RUN_TEST(test_parseDouble_should_return_false_for_invalid_string);
    RUN_TEST(test_hasInvalidSpaces_function);
    
    return UNITY_END();
}
