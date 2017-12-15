//---------------------------------Arduino UNO----&&&&---Serial baud 115200---------------------------

//----------------------------------Parameter------------------------------------------------------------------ 

  int blackline = 610; //  from IRsensor          *** not define yet
  int speedrun_l = 100; //100   100               *** not define yet
  int speedrun_r = 121; //141 121
  int speed_turnl = 0; //127  92 127  80 165sensor_linetracking      *** not define yet
  int speed_turnr = 127; //100 134 100  115  90sensor_linetracking   *** not define yet
  int turntime = 550; //                          *** not define yet
  int candle_brightness = 110;//                  *** not define yet
  int speedturn_l = 100; // motor r speed when turn right
  int speedturn_r = 0; // motor l speed when turn right
  
  int motor_l_pwm_pin = 3;
  int motor_r_pwm_pin = 6;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
  int a;
  int b = 0;
  int i;
  boolean fanloop;
  int left_tracking,mid_tracking,right_tracking = 0;
  int count;
  int terns;

  int amb_front;
  int amb_side;

 
  //--------------------------------------------------------------------------------------------------------------


/*---------------------------------AnalogPin Explanation-------------------------------------------------------
 A0,A1,A2  as  L,M,R IRsensor  
 A3        as  Side IRsensor
 A4        as  front Ambient Sensor
 A5        as  side  Ambient Sensor
----------------------------------DigitalPin Explanation-------------------------------------------------------
 3 as motor_l PWM ||  1+ , 2 gnd ---- as motor_l  direction  
 6 as motor_r PWM ||  4+ , 5 gnd ---- as motor_r  direction
 7 as fan_front  --- active low
 8 as fan_side   --- active low
 --------------------------------------------------------------------------------------------------------*/

//-------------------------------Function----------------------------------------------------------------------
  void motor_run()
  {
    analogWrite(6,speedrun_r); //right
    analogWrite(3,speedrun_l); //left
    
    digitalWrite(1,HIGH);
    digitalWrite(2,LOW); 
    
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);

  }

  void motor_stop()
  {
    analogWrite(6,255); //right
    analogWrite(3,255); //left
    
    digitalWrite(1,HIGH);
    digitalWrite(2,HIGH); 
    
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
  }

  void motor_end()
  {
    while(true)
    {
      motor_stop();
    }
  }

  void turn_right()
  {
    analogWrite(6,0);
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);

    //analogWrite(motor_r_pwm_pin,speedturn_r); // motor r speed when turn right
    analogWrite(motor_l_pwm_pin,speedturn_l); // motor l speed when turn right
    digitalWrite(1,HIGH);
    digitalWrite(2,LOW);
    delay(turntime);
    
  }

  void front_fan_On()
  {
    digitalWrite(7,LOW);
    digitalWrite(8,HIGH);
  }

  void side_fan_On()
  {
    digitalWrite(8,LOW);
    digitalWrite(7,HIGH);
  }

  void fan_Off()
  {
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
  }
  

//------------------------------Secondary Operation------------------------------------------------------------

  int light_out()
  {

      motor_stop();
      amb_front = analogRead(A4);
      amb_side = analogRead(A5);
       
      if(amb_front >= candle_brightness && amb_side < candle_brightness) 
      {
        front_fan_On();
        delay(3000);
        fan_Off();
        delay(100);
        return 1;
      }
      else if(amb_side >= candle_brightness && amb_front < candle_brightness)
      {
        side_fan_On();
        delay(900);
        fan_Off();
      }
      else
      {
        return 0;
      }
      
  }

  //------------------------------------------------------------------------------------------------




//-----------------------------Main Operation------------------------------------------------------------------

    void sensor_linetracking()
    {

      left_tracking = analogRead(A0);
      mid_tracking = analogRead(A1);
      right_tracking = analogRead(A2);
      
      if(left_tracking > blackline  && right_tracking < blackline ) 
        { 
         analogWrite(motor_l_pwm_pin,96);//96 turning_left 94
         analogWrite(motor_r_pwm_pin,134); //130 134
        }
      else if(left_tracking < blackline   && right_tracking > blackline ) 
        {
        
         analogWrite(motor_l_pwm_pin,140); //132
         analogWrite(motor_r_pwm_pin,105);//turning_right 114
        }
        
      else if(left_tracking >= 620 &&mid_tracking >= 620 && right_tracking >= 620) 
        { 
          motor_stop();
          count += 1;
          
          delay(160);//85
          
          if(quest() == 1)
          {
            motor_run();
            delay(60);
          }
          else
          {
            motor_run();
            delay(45);
          }
        }
        
      else
        {
         motor_run();
        }

    }


    int quest()  
    {
      if(count == 4 && terns == 0) 
      { 
        delay(100);
        terns += 1;
        turn_right();
        motor_stop();
        delay(50);
        count = 0;
        return 1;
      }
    
      if (count == 1 && terns == 1) //checkpoint
      {
          motor_run();
          delay(70);
          motor_stop();
          delay(150);
          
          terns +=1 ;
          
          if(light_out() == 1)
          {
          digitalWrite(4,HIGH);
          digitalWrite(5,HIGH);
          digitalWrite(1,HIGH);
          digitalWrite(2,LOW);
         
         analogWrite(6,255);
         //analogWrite(motor_r_pwm_pin,speedturn_r); // motor r speed when turn right
         analogWrite(motor_l_pwm_pin,speedturn_l); // motor l speed when turn right
        
         delay(525); //458
          }
          else 
          {
            digitalWrite(4,HIGH);
            digitalWrite(5,HIGH);
            digitalWrite(1,HIGH);
            digitalWrite(2,LOW);
           
           analogWrite(6,255);
           //analogWrite(motor_r_pwm_pin,speedturn_r); // motor r speed when turn right
           analogWrite(motor_l_pwm_pin,speedturn_l); // motor l speed when turn right
          
           delay(448  );
          }
         motor_stop();
         delay(100);
          count = 0;
          return 1;

      }
      if(count == 4 && terns == 2)
      {
        motor_stop();
        delay(500);
        motor_run();
        delay(60);
      }
      if(count == 8 && terns == 2)
      {
        delay(150);
        terns += 1;
        
       // light_out();

       
       digitalWrite(4,HIGH);
       digitalWrite(5,HIGH);
       digitalWrite(1,HIGH);
       digitalWrite(2,LOW);
       //analogWrite(motor_r_pwm_pin,speedturn_r); // motor r speed when turn right
       analogWrite(6,255);
       analogWrite(motor_l_pwm_pin,speedturn_l); // motor l speed when turn right
       
       delay(508);

        motor_stop();
        delay(100);
        
        count = 0;    
      }

      if(count == 2 && terns == 3)
      {
        delay(165);//150
        
        terns +=1 ;
        
        light_out();
       
        digitalWrite(4,HIGH);
        digitalWrite(5,HIGH);
       digitalWrite(1,HIGH);
       digitalWrite(2,LOW);
       
       analogWrite(6,255);
       //analogWrite(motor_r_pwm_pin,speedturn_r); // motor r speed when turn right
       analogWrite(motor_l_pwm_pin,speedturn_l); // motor l speed when turn right
      
       delay(580);//527
       
       motor_stop();
       delay(200);
        count = 0;
        return 1;
        
        
      }
      if(count == 4 && terns == 4)
      {
        motor_stop();
        delay(500);
        motor_run();
        delay(60);
      }
      if(count == 8 && terns == 4)
      {
        motor_stop();
        terns += 1;
        
       
        // light_out();
        motor_run();
        delay(10);
        motor_end();  
        return 1;
      }
      else
      { 
        return 2;
      }

    }

  //-----------------------------------------------------------------------------


//----------------------------Testing&Offset-------------------------------------------------------------------
    void fan_test()
    {
      while(true)
      {
      fan_Off();
      delay(2500);
      
      front_fan_On();
      delay(800);

      fan_Off();
      delay(200);
      
      side_fan_On();
      delay(800);

      }
    }

    void ambient_test()
    {
      while(true)
      {b += 1;
      Serial.print(b);
      Serial.print("\t");
      Serial.print("Side ");
      Serial.print(analogRead(A5));
      Serial.print("\t");
      Serial.print("Front ");   
      Serial.print(analogRead(A4));
      Serial.println("\t");
      delay(75);
      }
    }

    void blackline_test()
    {
      while(true)
      {
      Serial.print("\t");
      Serial.print(analogRead(A0));  //left_tracking  
      Serial.print("\t");
      Serial.print(analogRead(A1)); //mid_tracking
      Serial.print("\t");
      Serial.println(analogRead(A2)); //right_tracking
      delay(50);
      
      }
    }
  //-----------------------------------------------------------------------------


//---------------------------Arduino---------------------------------------------------------------------------


  void setup() 
  {
   Serial.begin(115200);

    pinMode(1,OUTPUT);//motor_r forward 0
    pinMode(2,OUTPUT);//motor_l forward plus//
    pinMode(3,OUTPUT);//motor_l rforward2 

    pinMode(4,OUTPUT);//
    pinMode(5,OUTPUT);//
    pinMode(6,OUTPUT);//
    
    pinMode(7,OUTPUT);
    pinMode(8,OUTPUT);

    pinMode(9,OUTPUT);
    digitalWrite(9,LOW);
    pinMode(10,OUTPUT);
    digitalWrite(10,HIGH);

    pinMode(11,OUTPUT);
    digitalWrite(11,LOW);
    pinMode(12,OUTPUT);
    digitalWrite(12,HIGH);


    pinMode(13,OUTPUT);
    digitalWrite(13,HIGH);
    

    fan_Off();
    
    //ambient_test();
   //blackline_test();
   
    /*
    analogWrite(6,70); //right
    analogWrite(3,55); //left
    
    digitalWrite(1,HIGH);
    digitalWrite(2,LOW); 
    
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    */
   // light_out();
   // turn_right();
   // motor_end();

    motor_run();
    delay(30);
    
    
  }

  void loop() 
  {  
   sensor_linetracking();
    
    //side_line_counting();
    //quest();
    //
    
  }


 //-------------------------------------------------------------------------------------------------------------