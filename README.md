# CNCSTEPPER
Essa é uma biblioteca para Arduino para controlar vários motores de passo "ao mesmo tempo" e com velocidades diferentes em modo bipolar usando o CI de ponte H dupla L298. 
### Como usar
``` arduino
#include "CNCStepper.h"
Motor motor1(8,9,10,11); // mude os pinos
void setup()
{
    motor1.setSpeed(10); // 10 ms
}
void loop
{
    motor1.move(50); // 50 passos
    motor1.off(); // delimitador
}
```
### Funções
#### sequence()
Essa função precisa ser alterada a depender do modo de funcionamento, nela está a sequência de acionamentos das bobinas do motor.
Obs: para o modo meio-passo é preciso também alterar outras partes do código, já que seu acionamento exige uma sequência de 8 acionamentos.
#### move () 
Essa função gira o motor de acordo com a velocidade pré-determinada e o número que é passado para o função é a quantidade de passos que se quer chegar. 
Pode ser move(10) para sequência normal ou move(-10) para inverter a sequência.
#### setSpeed()
Essa função seta a velocidade de acordo com o tempo de acionamento das bobinas, assim o parâmentro dela é passo pela quantidade de milisegundos que se quer ter entre o acionamento de cada bobina.
#### off()
Essa função é para parar e resetar todas as configurações quando a sequência dos motores forem concluídas. Também serve de "delitador" para as funções de move() cada Classe de motores, sendo obrigátoria para o funcionamento do código.
