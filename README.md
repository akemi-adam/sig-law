# Sig Law
O projeto desenvolvido é um sistema de agendamento para uma advocacia, criado em linguagem C. Ele tem como principal funcionalidade o agendamento de reuniões entre clientes e advogados, facilitando a organização dos atendimentos. Este trabalho é uma tarefa realizada para a disciplina de Programação do curso de Bacharelado em Sistemas de Informação na UFRN.

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