#include <Ticker.h>
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif 
static int led_delay = 50; 
const int ledPin = 22;                    // I have a LED on pin 22
const int buttonpin1 = 21;               // I have a push button on pin 21
const int PulseIN = 2;                  //pulse counter pin   
const int potPin = 34;                 //potentiometer pin
const int analog_pin = 33;   
int buttonstate1 = 0;
int potValue = 0;
int counter=0;
int average_analog_in = 0;             //averaging an analog value
int average;
int error_code=0;
float T;                              // offcycle+oncycle
int F;                               //frequency =1/T
float OnCycle;                      //on cycle variable
float OffCycle;                    //off cycle variable
float frequency;
float analog_in_array[]={0,0,0,0};

void CycleF()
{
  counter++;
  if( counter % 18  )loop;              //from assignment 1 
  if( counter % 200 )task2;            //converted to Milliseconds
  if( counter % 1000)task3;
  if( counter % 42)task4;
  if( counter % 42)task5;
  if( counter % 100)task6;
  if( counter % 333)task7;            // task7 has both task7 & task8 
  if( counter % 5000)task9;
}
void setup()
{
  pinMode(ledPin, OUTPUT);       
  pinMode (buttonpin1, INPUT);
  pinMode(PulseIN, INPUT);
  pinMode(analog_pin, INPUT);
  vTaskDelay(1000 / portTICK_PERIOD_MS); //in ms 
  Serial.begin(9600);                  //baud rate value
  task2();
  task3();
  task4();
  task5();
  task6();
  task7();
  task9();
  
 xTaskCreatePinnedToCore(  
             task2,
            "TASK 2",   
            2048,           
            NULL,           
            8,              
            NULL,           
            app_cpu);       
 
 xTaskCreatePinnedToCore(  
            task3,      
            "TASK 3",   
            1024,           
            NULL,           
            1,              
            NULL,           
            app_cpu);       

 xTaskCreatePinnedToCore(  
            task4,          
            "TASK 4",       
            4095,           
            NULL,           
            4,              
            NULL,           
            app_cpu);       
 
 xTaskCreatePinnedToCore(  
            task5,      
            "TASK 5",   
            1024,           
            NULL,           
            5,              
            NULL,           
            app_cpu);       
 
 xTaskCreatePinnedToCore(  
            task6,      
            "TASK 6",   
            2048,          
            NULL,           
            9,              
            NULL,           
            app_cpu);       
 xTaskCreatePinnedToCore(  
            task7,      
            "TASK 7",   
            4095,           
            NULL,           
            3,             
            NULL,           
            app_cpu);       
 xTaskCreatePinnedToCore(  
            task9,      
            "TASK 9",   
            2048,           
            NULL,           
            1,              
            NULL,           
            app_cpu);       
}
void loop() 
{ digitalWrite(ledPin, HIGH);                    //task1
  delayMicroseconds(50);
  digitalWrite(ledPin, LOW);
  delay(500);
  vTaskDelay(50/portTICK_PERIOD_MS);
}
void task2() (void *parameter)                                   //task2
{buttonstate1 = digitalRead(buttonpin1);
  if(buttonstate1 ==1)
  {digitalWrite(ledPin, HIGH);}
  else
  {digitalWrite(ledPin, LOW);}
  vTaskDelay(200/portTICK_PERIOD_MS);
}
void task3() (void *parameter)                                  //task3
{OnCycle = pulseIn(PulseIN, HIGH, 10000);
  OffCycle = pulseIn(PulseIN, LOW, 10000);
  T = OnCycle + OffCycle;
  if(T==0)
  {frequency=0;}
  else
  {F = 1000000 / T;}   
  Serial.print("Frequency = ");
  Serial.print(F);
  vTaskDelay(1/portTICK_PERIOD_MS);  
}
void task4() (void *parameter)                                  //task4
{potValue = analogRead(potPin);
  analog_in_array[4]=analog_pin;
  for(int i=0; i<4;i++)
  {analog_in_array[i]=analog_in_array[i+1];}
  Serial.println(potValue);
  vTaskDelay(41/portTICK_PERIOD_MS);
}
void task5() (void *parameter)                                //task5
{average=0;
  for(int i=0;i<4;i++)
  {average=average+analog_in_array[i];}
  average_analog_in=average/4;
  vTaskDelay(41/portTICK_PERIOD_MS);
}
void task6() (void *parameter)                               //task6
{for(int i=0;i<1000;i++)
{asm volatile("nop\n\t"::);}
vTaskDelay(100/portTICK_PERIOD_MS);
}
void task7() (void *parameter)                              //task7 & task8
{int n=0;
  int error_code= 0;
  for (int i =0;i<n; i++)
  {average_analog_in += analogRead(analog_pin); }
   average_analog_in =average_analog_in/n;
   if(average_analog_in> 4095/2)
   {error_code =1;
     digitalWrite(ledPin, HIGH);}
     else
     {error_code =0;
     digitalWrite(ledPin, LOW);}
    vTaskDelay(333/portTICK_PERIOD_MS);
} 
void task9() (void *parameter)                               //task9
{Serial.print("error_code");
   Serial.print(error_code);
   Serial.print(",");
   Serial.print("frequency");
   Serial.print(frequency);
   Serial.print(",");
   Serial.print("average_analog_in");
   Serial.print(average_analog_in);
   Serial.print(",");
   vTaskDelay(5000/portTICK_PERIOD_MS);
}
  
