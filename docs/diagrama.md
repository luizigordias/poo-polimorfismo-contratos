# Modelo a completar

Desenhe Sensor como classe abstrata, as três especializações e a dependência do painel em Sensor. Inclua as operações do contrato e marque as abstratas. O painel recebe uma referência; ele não possui os sensores.


```mermaid
classDiagram
    %% Definição da Classe Abstrata (Contrato)
    class Sensor {
        <<abstract>>
        -String tag_
        +tag() String
        +valor() double*
        +unidade() String*
        +atualizar(double leitura) bool*
        +emAlerta() bool*
    }

    %% Especializações
    class SensorNivel {
        -double valor_
        +valor() double
        +unidade() String
        +atualizar(double leitura) bool
        +emAlerta() bool
    }

    class SensorTemperatura {
        -double valor_
        +valor() double
        +unidade() String
        +atualizar(double leitura) bool
        +emAlerta() bool
    }

    class SensorPressao {
        -double valor_
        +valor() double
        +unidade() String
        +atualizar(double leitura) bool
        +emAlerta() bool
    }

    %% Função/Módulo do Painel
    class Painel {
        <<Módulo>>
        +linhaPainel(Sensor sensor) String
    }

    %% Relações de Herança (Realização do contrato)
    Sensor <|-- SensorNivel
    Sensor <|-- SensorTemperatura
    Sensor <|-- SensorPressao

    %% Relação de Dependência (Painel recebe referência de Sensor, sem possuí-lo)
    Painel ..> Sensor : depende de (via referência)