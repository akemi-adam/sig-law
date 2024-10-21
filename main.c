#include "src/utils/interfaces.h"
#include <locale.h>

int main(void)
{
    setlocale(LC_ALL, "Portuguese_Brazil");

    showMainMenu();

    return 0;
}
