#include "mbed.h"
#include "Motor.h"

void encoderread(){
    //direction to PA_9 -- step to PA_8
    TIM_HandleTypeDef timer;
    TIM_Encoder_InitTypeDef encoder;
     GPIO_InitTypeDef GPIO_InitStruct;
        __TIM1_CLK_ENABLE();
        __GPIOA_CLK_ENABLE();
        GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9; // set pin = A | B
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
        GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
    timer.Instance = TIM1;
    timer.Init.Period = 0xffff;
    timer.Init.Prescaler = 1;
    timer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    timer.Init.CounterMode = TIM_COUNTERMODE_UP;
     
    encoder.EncoderMode = TIM_ENCODERMODE_TI1; 
    encoder.IC1Filter = 0x0f;
    encoder.IC1Polarity = TIM_INPUTCHANNELPOLARITY_RISING; //step signal
    encoder.IC1Prescaler = TIM_ICPSC_DIV1;
    encoder.IC1Selection = TIM_ICSELECTION_DIRECTTI;
 
    encoder.IC2Filter = 0x0f;
    encoder.IC2Polarity = TIM_INPUTCHANNELPOLARITY_BOTHEDGE;  //check direction  
    encoder.IC2Prescaler = TIM_ICPSC_DIV1;
    encoder.IC2Selection = TIM_ICSELECTION_INDIRECTTI;
 
    HAL_TIM_Encoder_Init(&timer, &encoder);
    HAL_TIM_Encoder_Start(&timer,TIM_CHANNEL_1);   
   
    TIM1->EGR = 1;           // Generate an update event
    TIM1->CR1 = 1;           // Enable the counter
}

void encoderprint() {
        int16_t count1;
        count1=TIM1->CNT; 
        printf("%d\r\n", count1);
        wait(0.1);
 }
 

int main(){
     
     /*
     * @param pwm A PwmOut pin, driving the H-bridge enable line to control the speed
     * @param fwd A DigitalOut, set high when the motor should go forward
     * @param rev A DigitalOut, set high when the motor should go backwards 
     */
 Motor A(D10, D4, D3);  //(PinName pwm, PinName fwd, PinName rev)
 encoderread();
 DigitalIn button(USER_BUTTON, PullUp); // Create the button object and setup internall pull-up resistor
 
 while (1) { 
    int flag;
    float userInput;
    float x;   
    do{ 
        printf("Enter Speed of motor (-255 to 255)\r\n");
        flag = scanf("%f", &userInput);
    }while(flag == EOF);
    x = userInput/255 ;
    
    do{
        encoderprint(); 
        A.speed(x);
    }while(button == 1);
    A.speed(0);
                           
 }
} 

