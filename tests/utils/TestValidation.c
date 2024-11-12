#include "./../../unity/unity.h"
#include "./../../unity/unity_internals.h"
#include "./../../src/utils/validation.h"


void setUp(void) {
    // Executado antes de cada teste, se necessário
}

void tearDown(void) {
    // Executado após cada teste, se necessário
}

void test_isString(void) {
    TEST_ASSERT_TRUE(isString("abc"));              // Apenas letras
    TEST_ASSERT_TRUE(isString("Teste"));            // Letras maiúsculas e minúsculas
    TEST_ASSERT_TRUE(isString("Isso é um teste"));            // Espaços entre as palavras
    TEST_ASSERT_FALSE(isString("Test123"));         // Contém números
    TEST_ASSERT_FALSE(isString("Test!"));           // Contém caracteres especiais
    TEST_ASSERT_FALSE(isString(" Test! "));           // Contém espaço no início e no fim
    TEST_ASSERT_FALSE(isString(" Test!"));           // Contém espaço no início
    TEST_ASSERT_FALSE(isString("Test! "));           // Contém espaço no fim
    TEST_ASSERT_FALSE(isString(""));           // String vazia
}

void test_isEmpty(void) {
    TEST_ASSERT_TRUE(isEmpty(""));
    TEST_ASSERT_FALSE(isEmpty("Teste"));
}

void test_isPositive(void) {
    TEST_ASSERT_TRUE(isPositive(1));                // Número positivo
    TEST_ASSERT_TRUE(isPositive(0));                // Zero (considerado positivo)
    TEST_ASSERT_FALSE(isPositive(-1));              // Número negativo
}

void test_isEmail(void) {
    TEST_ASSERT_TRUE(isEmail("email@dominio.com")); // E-mail válido
    TEST_ASSERT_TRUE(isEmail("teste@xyz.org"));     // E-mail com domínio diferente
    TEST_ASSERT_FALSE(isEmail("email.com"));        // Sem arroba
    TEST_ASSERT_FALSE(isEmail("email@.com"));       // Ponto logo após arroba
    TEST_ASSERT_FALSE(isEmail("email@dominio"));    // Sem ponto após domínio
    TEST_ASSERT_FALSE(isEmail(""));                 // String vazia
}

void test_isTelephone(void) {
    TEST_ASSERT_TRUE(isTelephone("11 91234-5678")); // Telefone válido
    TEST_ASSERT_FALSE(isTelephone("12 1234-5678")); // Não começa com 9
    TEST_ASSERT_FALSE(isTelephone("78 1234-5678")); // DDD inválido
    TEST_ASSERT_FALSE(isTelephone("05 1234-5678")); // DDD inválido
    TEST_ASSERT_FALSE(isTelephone("40 1234-5678")); // DDD inválido
    TEST_ASSERT_FALSE(isTelephone("11 91234-567")); // Número incompleto
    TEST_ASSERT_FALSE(isTelephone("11A91234-5678")); // Caractere não numérico
    TEST_ASSERT_FALSE(isTelephone(""));             // String vazia
}

void test_isCpf(void) {
    TEST_ASSERT_TRUE(isCpf("12345678909"));         // CPF válido
    TEST_ASSERT_FALSE(isCpf("12345678900"));        // CPF inválido
    TEST_ASSERT_FALSE(isCpf("12345678a09"));        // Contém caractere não numérico
    TEST_ASSERT_FALSE(isCpf("12345678"));           // CPF incompleto
    TEST_ASSERT_FALSE(isCpf(""));                   // String vazia
}

void test_isCna(void) {
    TEST_ASSERT_TRUE(isCna("123456789012"));        // CNA válido (máximo de 12 dígitos)
    TEST_ASSERT_FALSE(isCna("1234567890123"));      // CNA com mais de 12 dígitos
    TEST_ASSERT_FALSE(isCna("CNA123"));             // Contém letras
    TEST_ASSERT_FALSE(isCna(""));                   // String vazia
}

void test_isLeapYear(void) {
    TEST_ASSERT_TRUE(isLeapYear(2020));  // Ano bissexto divisível por 4
    TEST_ASSERT_FALSE(isLeapYear(1900)); // Ano não bissexto (divisível por 100 mas não por 400)
    TEST_ASSERT_TRUE(isLeapYear(2000));  // Ano bissexto (divisível por 400)
    TEST_ASSERT_FALSE(isLeapYear(2023)); // Ano não bissexto
}

void test_maxDaysInMonth(void) {
    TEST_ASSERT_EQUAL(31, maxDaysInMonth(1, 2023)); // Janeiro, 31 dias
    TEST_ASSERT_EQUAL(28, maxDaysInMonth(2, 2023)); // Fevereiro, ano não bissexto
    TEST_ASSERT_EQUAL(29, maxDaysInMonth(2, 2024)); // Fevereiro, ano bissexto
    TEST_ASSERT_EQUAL(30, maxDaysInMonth(4, 2023)); // Abril, 30 dias
    TEST_ASSERT_EQUAL(0, maxDaysInMonth(13, 2023)); // Mês inválido
}

void test_isDay(void) {
    // Janeiro com 31 dias
    TEST_ASSERT_TRUE(isDay(1, 1, 2023));  // Limite inferior
    TEST_ASSERT_TRUE(isDay(31, 1, 2023)); // Limite superior
    TEST_ASSERT_FALSE(isDay(0, 1, 2023)); // Abaixo do limite
    TEST_ASSERT_FALSE(isDay(32, 1, 2023));// Acima do limite

    // Fevereiro em ano não bissexto (28 dias)
    TEST_ASSERT_TRUE(isDay(28, 2, 2023)); // Último dia de fevereiro
    TEST_ASSERT_FALSE(isDay(29, 2, 2023));// Excesso de dias em ano não bissexto

    // Fevereiro em ano bissexto (29 dias)
    TEST_ASSERT_TRUE(isDay(29, 2, 2024)); // Último dia em ano bissexto
    TEST_ASSERT_FALSE(isDay(30, 2, 2024));// Excesso de dias em ano bissexto

    // Abril com 30 dias
    TEST_ASSERT_TRUE(isDay(30, 4, 2023)); // Último dia de abril
    TEST_ASSERT_FALSE(isDay(31, 4, 2023));// Excesso de dias para abril
}



void test_isMonth(void) {
    TEST_ASSERT_TRUE(isMonth(1));                   // Janeiro
    TEST_ASSERT_TRUE(isMonth(12));                  // Dezembro
    TEST_ASSERT_FALSE(isMonth(0));                  // Abaixo do limite
    TEST_ASSERT_FALSE(isMonth(13));                 // Acima do limite
}

void test_isYear(void) {
    TEST_ASSERT_TRUE(isYear(1));                    // Ano mínimo válido
    TEST_ASSERT_TRUE(isYear(2024));                 // Ano corrente
    TEST_ASSERT_FALSE(isYear(0));                   // Ano inválido
    TEST_ASSERT_FALSE(isYear(-1));                  // Ano negativo
}

void test_isDate(void) {
    TEST_ASSERT_TRUE(isDate("01/01/2023"));         // Data válida
    TEST_ASSERT_TRUE(isDate("31/12/2023"));         // Data válida
    TEST_ASSERT_FALSE(isDate("32/01/2023"));        // Dia inválido
    TEST_ASSERT_FALSE(isDate("01/13/2023"));        // Mês inválido
    TEST_ASSERT_FALSE(isDate("00/12/2023"));        // Dia zero
    TEST_ASSERT_FALSE(isDate("01/00/2023"));        // Mês zero
    TEST_ASSERT_FALSE(isDate("01/01/-1"));          // Ano inválido
    TEST_ASSERT_FALSE(isDate("01012023"));          // Formato incorreto
    TEST_ASSERT_FALSE(isDate(""));                  // String vazia
}

void test_isHour(void) {
    TEST_ASSERT_TRUE(isHour("14:12"));
    TEST_ASSERT_FALSE(isHour("25:00"));
    TEST_ASSERT_FALSE(isHour(" 15:00"));
    TEST_ASSERT_FALSE(isHour("15:00 "));
    TEST_ASSERT_FALSE(isHour(" 15:00 "));
    TEST_ASSERT_FALSE(isHour("05:71"));
}


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_isString);
    RUN_TEST(test_isEmpty);
    RUN_TEST(test_isPositive);
    RUN_TEST(test_isEmail);
    RUN_TEST(test_isTelephone);
    RUN_TEST(test_isCpf);
    RUN_TEST(test_isCna);
    RUN_TEST(test_isLeapYear);
    RUN_TEST(test_maxDaysInMonth);
    RUN_TEST(test_isDay);
    RUN_TEST(test_isMonth);
    RUN_TEST(test_isYear);
    RUN_TEST(test_isDate);
    RUN_TEST(test_isHour);

    return UNITY_END();
}
