int IN_PIN = 2;
int k=0,btn,t=0,a=0;
void setup() 
{
  pinMode(IN_PIN,INPUT_PULLUP);
  attachInterrupt(0,pause,FALLING);
  DDRB = B00111111;
  PORTB = B00000000;
}

void loop() 
{
  delay(50);
  for(a=0;a<=6;a++)
  {
    if(a==1)
    { PORTB = B00000011;
      delay(50);
      if(btn == LOW)
      {
      delay(10);
      PORTB = B00000011;
      while(btn == HIGH);
      }
    }

    if(a==2)
    {
      PORTB = B00000110;
      delay(50);

      if(btn == LOW)
      {
      delay(10);
      PORTB = B00000110;
      while(btn == HIGH);
      }
    }

    if(a==3)
    {
      PORTB = B00001100;
      delay(50);
      if(btn == LOW)
      {
      delay(10);
      PORTB = B00001100;
      while(btn == HIGH);
      }
    }

    if(a==4)
    {
      PORTB = B00011000;
      delay(50);

      if(btn == LOW)
      {
      delay(10);
      PORTB = B00011000;
      while(btn == HIGH);
      }
    }

    if(a==5)
    {
      PORTB = B00110000;
      delay(50);

      if(btn == LOW)
      {
      delay(10);
      PORTB = B00110000;
      while(btn == HIGH);
      }
    }

    if(a==6)
    {
      PORTB = B00100000;
      delay(50);

      if(btn == LOW)
      {
      delay(10);
      PORTB = B00100000;
      while(btn == HIGH);
      }
    }
  } 
} 
 

void pause()
{
  while(digitalRead(2) == 0);
  while(true)
  {
    if(digitalRead(2) == 0)
    {
    break;
    }
  }
}
