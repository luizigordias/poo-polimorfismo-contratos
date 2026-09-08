# Um painel para os sensores da estação

Starter da aula 07: polimorfismo e contratos em C++ e Python.
Guia: https://rafaelrezo.github.io/curso-poo/fundamentos_poo_cpp_python/07_polimorfismo/

Faça fork de https://github.com/rafaelrezo/poo-polimorfismo-contratos e clone **seu fork**.
Mantenha somente `origin` apontando para ele. Não configure `upstream`.
Este é um recorte do domínio da aula 06: nível e temperatura preservam leitura, unidade e validação; os TODOs introduzem alerta e painel. Ele não importa os testes nem substitui o controlador da aula anterior.

## Requisitos e primeiro resultado

GNU Make, g++ com C++17 e Python 3.10 ou superior. Sem pacotes Python adicionais.

```bash
make run
```

Cada linguagem imprime `LT-101: PENDENTE`, `TT-201: PENDENTE` e `PT-301: PENDENTE`.
O código compila; os testes funcionais falham intencionalmente até completar os TODOs.

## Contrato

- `tag`: identificação estável, fornecida pelo chamador, não vazia neste exercício.
- `valor()` e `unidade()`: última leitura válida e unidade da especialização.
- `atualizar(leitura)`: entrada numérica; retorna bool. Aceita somente valor finito na faixa inclusiva. Rejeita sem alterar estado. Tipos não numéricos estão fora do escopo.
- `emAlerta()` / `em_alerta()`: bool, sem alterar estado, regra da tabela.
- Painel: `TAG: VALOR UNIDADE | ESTADO`, uma casa decimal, ponto decimal; estado `OK` ou `ALERTA`.

| Sensor | Inicial | Faixa válida | Unidade | Alerta |
|---|---:|---|---|---|
| Nível | 50 | 0..100 | % | valor < 20 |
| Temperatura | 25 | -40..125 | C | valor > 45 |
| Pressão | 1 | 0..10 | bar | valor > 8 |

Limites definidos para simulação didática, sem histerese e sem acionamento de equipamento.

## Etapas cumulativas

1. `git switch -c pratica/01-painel`: complete alerta de nível e temperatura em `include/sensores.hpp` e `src/sensores.py`, depois o cliente em `src/painel.cpp` e `src/painel.py`. Siga o exemplo guiado no site. Execute `make test ETAPA=01`.
2. Faça commit, `git push -u origin pratica/01-painel` e PR para a `main` do próprio fork. Confira a CI no commit e integre quando passar.
3. `git switch main`, `git pull --ff-only` e `git switch -c pratica/02-pressao`: complete atualização e alerta de pressão nas duas linguagens, sem mudar painel. Execute `make test ETAPA=02`: repete etapa 01 e acrescenta pressão. Atualize `docs/diagrama.md`.
4. Commit, `git push -u origin pratica/02-pressao`, novo PR para `main` do próprio fork e integração após revisão e CI verde.

Não envie PR ao repositório do professor. Na tela de criação, confira **base repository = seu fork**, **base = main**, **compare = branch da etapa**.

O painel só pode depender de Sensor. Condições sobre resultados (alerta) são permitidas; seleção por nome de classe, `isinstance`, casts ou `switch` de tipo não é permitida. A criação dos concretos fica em `main`.
Não altere testes, contrato base, Makefile ou workflow para obter aprovação. Alterações legítimas no contrato devem ser discutidas e justificadas.

## Evidências no PR

- Saída de `make test ETAPA=NN` e link da execução remota associada ao commit.
- Saída do painel e explicação da chamada que escolhe a implementação concreta.
- UML e justificativa de por que a pressão não exigiu mudar o cliente.
- `AI_LOG.md`: pedido, aceites/rejeições e justificativa técnica; escreva “não utilizada” quando aplicável.

## Limites dos testes

Testes visíveis verificam comportamento público, fronteiras, erros e um subtipo desconhecido do painel. Não provam correção para todas as entradas nem impedem adulteração no fork. Revisão de diff, explicação e defesa oral complementam a CI.
