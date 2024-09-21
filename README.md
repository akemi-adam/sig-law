# Sig Law
Projeto da disciplina de Programação UFRN: SIG-Law: Um Sistema de Agendamento para Escritórios de Advocacia.

# Módulos

O sistema contempla os seguintes módulos: clientes, advogados, escritórios e agendamentos.

# Modelo Físico

```mermaid
erDiagram

CLIENT ||--|{ APPOINTMENT : contains
CLIENT {
    int id
    char[55] name
    char[55] email
    char[10] telephone
    char[12] cpf
}

LAWYER ||--|{ APPOINTMENT : contains
LAWYER {
    int id
    char[55] name
    char[55] email
    char[10] telephone
    char[12] cpf
    cna char[12]
}

APPOINTMENT {
    int id
    int clientId
    int lawyerId
    int officeId
    Datetime date
}

OFFICE ||--|{ APPOINTMENT : contains
OFFICE {
    int id
    char[] address
}
```

# Testes

Os testes unitários foram feitos com o Framework <a href="https://github.com/ThrowTheSwitch/Unity">Unity</a>. São executados ao rodar o `makefile`:

```bash
make
```