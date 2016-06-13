
#include "Arduino.h"
#include "CNCStepper.h"
void Motor::setSpeed(int _speed) 
{ 
  speed=_speed;
}
void Motor::sequence(int n) // Modo Passo ~n sei~
{
  switch (n) 
  {
    case 3:  
    digitalWrite(pin1, 1);
    digitalWrite(pin2, 0);
    digitalWrite(pin3, 0);
    digitalWrite(pin4, 1);
    break;
    case 2:  
    digitalWrite(pin1, 1);
    digitalWrite(pin2, 1);
    digitalWrite(pin3, 0);
    digitalWrite(pin4, 0);
    break;
    case 1: 
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 1);
    digitalWrite(pin3, 1);
    digitalWrite(pin4, 0);
    break;
    case 0: 
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    digitalWrite(pin3, 1);
    digitalWrite(pin4, 1);
    break;
  }
}  
void Motor::move(int steps)
{
    if(repetition==0) /* se repeticoes dos passos foram igual a 0 então acabou um ciclo de passos*/
    {
       finished=0;
    }
    if(finished==0) /* se tiver no inicio para o primeiro ciclo ou acabou um ciclo entao */
    {
        steps_cycle=steps; /* salva o numero de passos para o ciclo */
        repetition=abs(steps_cycle); /* o numero de repeticoes necessarias para cada ciclo de passos */
        if(count_cycle>0 && cycle==count_cycle && motor_off==0) /* numero de ciclos total acabou */
        {
            motor_off=1; /* ir para a funcao off() */
            finished=2; /* não executar mais a funcao de passos*/
        }
        else /* está em um ciclo atual */
        {
            count_cycle++;
            finished=1;
        }
    }
    if(delimiter==0)
    {
        cycle++;
    }
    if(finished==1 && steps_cycle==steps && motor_off==0) 
    {
        /* verifica se está em um ciclo, se está ligado
         o motor e se o numero de passos da funcao lida é 
        igual a numero de passos do ciclo atual */
        if(repetition>=0) /* enquanto numero de passo total for maior 0 */
        {
            current_time = millis();
            if(current_time - previous_time >=speed) /* tempo de execução maior/igual a velocidade que você quer? */
            {
                previous_time = current_time;  
                if(steps < 0) /* sentido de passo anti-horário */
                { 
                    if(rest==0) sequencer=4;
                    if((rest-1)==0)
                    {
                        repetition--;
                    }
                    sequencer--;
                } 
                else /* sentido do passo horário */
                { 
                    if((rest+1)==3) 
                    { 
                        repetition--;
                    }
                    sequencer++;
                }
                rest=sequencer%4;
                sequence(rest); 
            }
        }
    }
}
int Motor::off()
{   
    if(delimiter==0) delimiter=1;
    if(motor_off==1)
    {
        digitalWrite(pin1,0);
        digitalWrite(pin2,0);
        digitalWrite(pin3,0);
        digitalWrite(pin4,0); 
        digitalWrite(13,1);
        repetition=0;
        steps_cycle=0;
        finished=0;
        count_cycle=0;
        motor_off=0;
        cycle=0;
        sequencer=0;
        rest=0;
        delimiter=0;
        motor_off=0;
        return 1;
    }
    return 0;
}