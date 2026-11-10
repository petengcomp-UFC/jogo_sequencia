# 🎮 Jogo da sequência

Um jogo de memória inspirado no clássico **Genius**, desenvolvido com Arduino e componentes eletrônicos. O objetivo é reproduzir corretamente sequências de cores apresentadas pelo dispositivo, utilizando diferentes formas de interação: sensores ultrassônicos, botão e sensor de som.

O projeto combina programação embarcada, sensores e componentes eletrônicos para criar uma experiência interativa e dinâmica.

## 📌 Funcionalidades

- **Geração aleatória de sequências:** a cada rodada, uma nova cor é adicionada à sequência anterior.
- **Indicação visual:** três LEDs (vermelho, verde e azul) apresentam a sequência que deve ser memorizada.
- **Interação por proximidade:** sensores ultrassônicos identificam a aproximação do jogador para selecionar as cores vermelha e azul.
- **Interação por botão:** um botão permite selecionar a cor verde.
- **Reconhecimento de palmas:** um sensor de som também permite selecionar a cor verde por meio de uma palma.
- **Feedback visual:** um display LCD informa a rodada atual, indica o momento de interação e apresenta mensagens de sucesso ou fim de jogo.
- **Monitoramento serial:** informações sobre as rodadas, sequências e interações são exibidas no Monitor Serial.

## 🛠️ Componentes utilizados

| Componente | Quantidade |
|---|---:|
| Arduino | 1 |
| LED vermelho | 1 |
| LED verde | 1 |
| LED azul | 1 |
| Sensor ultrassônico | 2 |
| Sensor de som | 1 |
| Botão | 1 |
| Display LCD 16x2 | 1 |
| Resistores e jumpers | Conforme necessidade |
| Protoboard | 1 |

## 🔌 Ligações dos componentes

A tabela apresenta os pinos utilizados no Arduino:

| Componente | Pino |
|---|---|
| LED vermelho | 4 |
| LED verde | 3 |
| LED azul | 2 |
| Ultrassônico vermelho (TRIG) | 9 |
| Ultrassônico vermelho (ECHO) | 8 |
| Ultrassônico azul (TRIG) | 7 |
| Ultrassônico azul (ECHO) | 5 |
| Botão | 10 |
| Sensor de som | A0 |
| LCD (RS, E, D4, D5, D6, D7) | 12, 13, A3, 11, A1, A2 |

**Observação:** o botão utiliza a configuração `INPUT_PULLUP`, portanto, seu acionamento é identificado quando o pino recebe nível lógico LOW.

## 🎯 Como funciona o jogo

O jogo possui três cores, cada uma associada a uma forma de interação:

| Cor | Forma de interação |
|---|---|
| 🔴 Vermelho | Aproximação de um objeto do sensor ultrassônico 1 |
| 🟢 Verde | Pressionamento do botão ou detecção de uma palma |
| 🔵 Azul | Aproximação de um objeto do sensor ultrassônico 2 |

### Etapas de uma rodada

1. **Apresentação da sequência:** o Arduino sorteia uma das três cores e a adiciona à sequência anterior.
2. **Memorização:** os LEDs acendem em ordem, apresentando a sequência completa ao jogador.
3. **Interação:** o jogador deve reproduzir a sequência utilizando os sensores e o botão.
4. **Verificação:** cada entrada é comparada com a sequência armazenada.
5. **Resultado:** se todas as entradas estiverem corretas, uma nova rodada é iniciada, adicionando mais uma cor à sequência.

### Fim de jogo

Caso o jogador selecione uma cor diferente da esperada, o jogo é encerrado. O display LCD apresenta uma mensagem de erro e os três LEDs piscam simultaneamente.

O desafio possui um limite de **10 rodadas**, aumentando progressivamente a dificuldade conforme a sequência cresce.

## ⚙️ Configurações principais

Alguns parâmetros podem ser ajustados diretamente no código:

| Parâmetro | Valor | Descrição |
|---|---:|---|
| `DISTANCIA` | 25 cm | Distância máxima para detectar proximidade |
| `LIMITE_SOM` | 250 | Amplitude mínima para detectar uma palma |
| `TEMPO_RESETE` | 500 ms | Intervalo mínimo entre detecções de som |
| `INTERVALO_MEDICAO` | 20 ms | Janela de leitura do sensor de som |
| `TAMANHO_MAX_SEQUENCIA` | 10 | Número máximo de rodadas |
| `tempoAceso` | 450 ms | Tempo que cada LED permanece aceso |
| `tempoPausa` | 350 ms | Intervalo entre os LEDs da sequência |

## 💻 Tecnologias utilizadas

- **C++:** linguagem utilizada na programação do Arduino.
- **Arduino:** plataforma de prototipagem eletrônica e execução do sistema.
- **LiquidCrystal:** biblioteca utilizada para controlar o display LCD.
- **Sensores ultrassônicos:** utilizados para detectar a proximidade do jogador.
- **Sensor de som:** utilizado para identificar palmas por meio da variação da amplitude do sinal sonoro.

## 🚀 Como executar

1. Monte o circuito seguindo as ligações apresentadas neste README.
2. Instale a IDE do Arduino.
3. Certifique-se de que a biblioteca `LiquidCrystal` esteja disponível.
4. Abra o arquivo `.ino` do projeto na IDE.
5. Selecione a placa Arduino e a porta correspondente.
6. Compile e envie o código para a placa.
7. Abra o Monitor Serial, configurado para **9600 baud**, para acompanhar as informações do jogo.
8. Inicie o desafio e tente memorizar as sequências!

## 👥 Autores

Projeto desenvolvido como atividade acadêmica.

**Integrantes:** 
- Maria Paula
- Marisa

---

<p align="center">
  Desenvolvido com Arduino e C++ ❤️
</p>
