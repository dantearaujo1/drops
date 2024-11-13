![Universidade](https://badgen.net/badge/Univesidade/Universidade%20Federal%20do%20Ceará/blue)
![Cadeira](https://badgen.net/badge/Cadeira/Projeto%20Integrado%20II/red)
![Professor](https://badgen.net/badge/Professor/Windson&Georgia/red)
![Semestre](https://badgen.net/badge/Semestre/7/red)

![MIT](https://img.shields.io/github/license/drops/Front.svg)
![issues](https://img.shields.io/github/issues/drops/Front.svg)
![Esp32](https://img.shields.io/badge/espressif-E7352C?style=for-the-badge&logo=espressif&logoColor=white)

# Drops

Projeto para cadeira de Projeto Integrado II

Integrantes:

- Dante de Araújo
- Drielle Furtado
- Filipe Cavalcante
- Luís Eduardo
- Paulo Victor

# Hardware - Protótipo

- 1x Esp32 DevKit V1
- 1x Cabo Usb Tipo Micro B
- 1x Push Button
- 1x Cap Azul
- 1x LED RGB
- 4x Cabos Macho-Femea
- 1x Cabo Macho-Macho
- 1x Cabo Macho-Macho

# Arduino IDE - SETUP

Siga as direções dadas por essa página: [Esp32 Instalando no arduino IDE](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)

- Para esse Esp32 o Modulo da Placa (Board) é o "Esp32 Dev Module", essa board
deve ser definida na sua IDE do arduino após seguir as recomendações do site
acima.
- Não esquecer de ao ligar o esp na sua porta usb também colocar no arduino IDE
a porta

# Arduino-CLI - SETUP

## Instalar o Arduino CLI:

Se você ainda não instalou o arduino-cli, pode baixá-lo do repositório oficial do GitHub do Arduino CLI ou usar um gerenciador de pacotes como o brew (no macOS/Linux):

```bash
brew install arduino-cli
```

## Configurar o Arduino CLI:
Após instalar o arduino-cli, você precisa configurá-lo:

```bash
arduino-cli config init
```

Isso criará um arquivo de configuração (arduino-cli.yaml) e configurará os diretórios padrão.

## Instalar o pacote da placa ESP32:
Para carregar código para o ESP32, você precisa do núcleo do ESP32. Instale-o com:

```bash
arduino-cli core update-index
arduino-cli core install esp32:esp32
```

## Verificar se o ESP32 é reconhecido:
Verifique se o ESP32 DevKit V1 está disponível, listando todas as placas conectadas:

```bash
arduino-cli board list
```

Isso exibirá as placas conectadas, e você deverá ver o seu ESP32 na lista.

Compilar seu arquivo .ino:
Agora, você pode compilar o seu arquivo .ino (vamos assumir que ele se chama drops.ino):

bash
```bash
arduino-cli compile --fqbn esp32:esp32:esp32 drops.ino
```

Substitua drops.ino pelo nome real do seu arquivo.

Carregar o arquivo .ino:
Após compilar, carregue-o no seu ESP32 usando:

```bash
arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:esp32 your_file.ino
```
Substitua /dev/ttyUSB0 pela porta correta do seu ESP32 (verifique a lista de portas com arduino-cli board list).

# Arduino-cli com arduino.json

Se você tem arduino-cli ja configurado e as dependências:

- jq
- make
- arduino.json

Basta executar:

```bash
    make compile # Para compilar seu código
    make upload # Para fazer o upload pro seu esp32
```

**OBS: Verifique o arquivo arduino.json para ver se estão corretas as
informaçeõs de porta que seu arduino está utilizando e o modulo da placa**







