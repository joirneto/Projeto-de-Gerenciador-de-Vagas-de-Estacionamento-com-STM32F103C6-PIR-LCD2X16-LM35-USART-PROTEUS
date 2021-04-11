# Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-PIR-LCD2X16-LM35-USART-PROTEUS
Projeto da disciplina de Sistemas Microprocessados - Engenharia de Computação UFC

Projeto consiste em simular um estacionamento de veículos. Controlando a entrada e saída de veículos.
Utilizamos para este projeto:
* <a href="https://www.st.com/en/ecosystems/stm32cube.html">STM32Cube</a>
* <a href="https://www.labcenter.com/">Proteus</a>
* <a href="https://www.st.com/en/microcontrollers-microprocessors/stm32f103c6.html">microcontrolador stm32f103c6</a>
<img src="https://github.com/joirneto/Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-SENSOR-PIR-PROTEUS/blob/main/images/smt32f103c6.jpg" width="200" height="200"/>
* <a href="https://www.theengineeringprojects.com/2016/01/pir-sensor-library-proteus.html">PIR Sensor Library for Proteus</a>
<img src="https://github.com/joirneto/Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-SENSOR-PIR-PROTEUS/blob/main/images/PIR-Sensor-Library-for-Proteus-214x300.jpg">
* LCD 16×2 (LM016L) - FONTE: <a href="https://controllerstech.com/">Library LCD 2x16</a> - FONTE: <a href="https://embeddedcenter.wordpress.com/ece-study-centre/display-module/lcd-16x2-lm016l/">Sobre: LCD 2x16</a>
<img src="https://github.com/joirneto/Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-SENSOR-PIR-PROTEUS/blob/main/images/LCD%202x16.jpg">

Realizamos a inclusão ao projeto um sensor de temperatura, simulando um sinistro de incêndio quando a temperatura passar a um valor pré-definido. O sensor utiliza a entrada ACD do smt32. Também utilizamos comunicação via USART.
* LM35
<img src="https://github.com/joirneto/Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-SENSOR-PIR-PROTEUS/blob/main/images/LM35.png">

Por fim, realizamos a representação da conexão entre os sensores e o microcontrador em grandes distâncias, implementando o <a href="https://www.ti.com/lit/ds/symlink/max232.pdf?ts=1618077179451&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FMAX232%253Futm_source%253Dsupplyframe%2526utm_medium%253DSEP%2526utm_campaign%253Dnot_alldatasheet%2526DCM%253Dyes%2526dclid%253DCOr3nMv08-8CFUswuQYd2tIO5g">MAX232</a>, <img src="https://github.com/joirneto/Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-PIR-LCD2X16-LM35-USART-PROTEUS/blob/main/images/MAX232.jpg">.

**DIAGRAMA DE BLOCOS**
<img src="https://github.com/joirneto/Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-PIR-LCD2X16-LM35-USART-PROTEUS/blob/main/images/BPMN%202.0.jpeg">


**PROJETO PROTEUS**

<img src="https://github.com/joirneto/Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-SENSOR-PIR-PROTEUS/blob/main/images/Projeto%20Proteus.jpg">
<img src="https://github.com/joirneto/Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-PIR-LCD2X16-LM35-USART-PROTEUS/blob/main/images/Projeto%20Proteus%201.jpg">
<img src="https://github.com/joirneto/Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-PIR-LCD2X16-LM35-USART-PROTEUS/blob/main/images/Projeto%20Proteus%202.jpg">

**CONFIGURAÇÃO STM32CUBE-IDE**

<img src="https://github.com/joirneto/Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-PIR-LCD2X16-LM35-USART-PROTEUS/blob/main/images/Configura%C3%A7%C3%A3o%20stm32.png/">

- PA3 a PA7 configuradas GPIO_Output e renomeadas com a identificação das entradas das 4 entradas do LM016 (LCD2x16);

- PA8 e PA9 configuradas GPIO_Output e renomeadas com a identificação de RS (Register Set) e EN (Enable) do LM016 (LCD2x16);

- PB0 e PB1 configuradas GPIO_input(sem configuração de pull-down-up), utilizadas para receber as informações do Sensor PIR;

- PA1 configurada para ACD. Alterado para Enabled a configuração Continous Conversion Mode;

- PB6 e PB7 Configuradas para USART, mode Asynchronous.



**Video com a execução do Projeto e resultados obtidos.**

[![Watch the video](https://img.youtube.com/vi/T-D1KVIuvjA/maxresdefault.jpg)](https://youtu.be/T-D1KVIuvjA)



