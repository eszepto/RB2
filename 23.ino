int doubledotpause()   //11 as SW to pause
{
    for(i=3;i<=8;i++)// pin3-8 as LED
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
     while(true)
     {
       if(digitalRead(11) == LOW && digitalRead(12) == LOW)  //
        {
            while(digitalRead(11) == LOW || digitalRead(12) == LOW){} //
            break;
        }
                
     }
    }
    delay(300);
    
    }
}
