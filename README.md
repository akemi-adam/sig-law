# sig-law
Projeto da disciplina de Programação UFRN: SIG-Law: Um Sistema de Agendamento para Escritórios de Advocacia.

# Módulos

O sistema contempla os seguintes módulos: clientes, advogados, escritórios e agendamentos.

# Entidades
Lista das entidades que o sistema salva

## Persons
```c
struct Person {
    int id;
    char[55] name;
    char[55] email;
    char[10] telephone;
    char[12] cpf;
}
```

## Laywers
```c
struct Laywer {
    // Mesmos atributos de Person
    cna char[12];
}
```

## Appointments
```c
struct Appointment {
    int id;
    int clientId;
    int lawyerId;
    int officeId;
    // Campo de data ainda a ser pensado na melhor estratégia
}
```

## Offices
```c
struct Office {
    int id;
    char[] address;
}
```
