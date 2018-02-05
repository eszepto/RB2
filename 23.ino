int i=3;
int doubledotpause()   //11 as SW to pause
{
    
    digitalWrite(i,HIGH);
    digitalWrite(i+1,HIGH);
    Serial.println(i);
    for(int n=9;n>=3;n--) 
    {
        if(n != i && n != i+1)
        {
            digitalWrite(n,LOW);
        }
    }

    if(digitalRead(11) == LOW && digitalRead(12) == LOW)  //
      {   
       delay(10); 
       while(digitalRead(11) == LOW || digitalRead(12) == LOW){} //
       i++;
       if(i>8)i=3;
      }
    delay(300);
  
    }
}

void setup()
{
    PORTD = 0xFF;
    pinMode(11,INPUT_PULLUP);
    pinMode(12,INPUT_PULLUP);
}
void loop()
{
    doubledotpause();
}
