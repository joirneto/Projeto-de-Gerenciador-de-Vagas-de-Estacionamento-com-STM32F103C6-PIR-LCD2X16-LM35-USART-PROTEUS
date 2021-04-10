# Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-SENSOR-PIR-PROTEUS
Projeto da disciplina de Sistemas Microprocessados - Engenharia de Computação UFC

Projeto consiste em simular um estacionamento de veículos. Controlando a entrada e saída de veículos.
Utilizamos para este projeto:
* o simulador Proteus:
* <a href="https://www.st.com/en/microcontrollers-microprocessors/stm32f103c6.html">microcontrolador stm32f103c6</a>
<img src="https://github.com/joirneto/Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-SENSOR-PIR-PROTEUS/blob/main/images/smt32f103c6.jpg" width="200" height="200"/>
* <a href="https://www.theengineeringprojects.com/2016/01/pir-sensor-library-proteus.html">PIR Sensor Library for Proteus</a>
<img src="https://github.com/joirneto/Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-SENSOR-PIR-PROTEUS/blob/main/images/PIR-Sensor-Library-for-Proteus-214x300.jpg">
* LCD 16×2 (LM016L) - FONTE: <a href="https://controllerstech.com/">Library LCD 2x16</a> - FONTE: <a href="https://embeddedcenter.wordpress.com/ece-study-centre/display-module/lcd-16x2-lm016l/">Sobre: LCD 2x16</a>
<img src="https://github.com/joirneto/Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-SENSOR-PIR-PROTEUS/blob/main/images/LCD%202x16.jpg">

Realizamos a inclusão ao projeto um sensor de temperatura, simulando um sinistro de incêndio quando a temperatura passar a um valor pré-definido. O sensor utiliza a entrada ACD do smt32. Também utilizamos comunicação via USART.
* LM35
<img src="https://github.com/joirneto/Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-SENSOR-PIR-PROTEUS/blob/main/images/LM35.png">

**DIAGRAMA DE BLOCOS**
<img src="https://github.com/joirneto/Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-PIR-LCD2X16-LM35-USART-PROTEUS/blob/main/images/BPMN%202.0.jpeg">


**PROJETO PROTEUS**
<img src="https://github.com/joirneto/Projeto-de-Gerenciador-de-Vagas-de-Estacionamento-com-STM32F103C6-SENSOR-PIR-PROTEUS/blob/main/images/Projeto%20Proteus.jpg" width="600" height="600">







