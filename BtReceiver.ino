

int pin_btvcc=11;
int pin_uppin=10;
int pin_stoppin=9;
int pin_downpin=8;

int test_mode=0; //test mode disable
//int test_mode=1; //test mode enable

#define BAUDRATE 9600

int delaytime=400;
int delaytime_verifyled=1000;

const char UpCmd[] = "IamUpButton\n";
const char StopCmd[] = "IamStopButton\n";
const char DownCmd[] = "IamDownButton\n";

void setup()
{
  pinMode(pin_btvcc, OUTPUT); 
  pinMode(pin_uppin, OUTPUT); 
  pinMode(pin_stoppin, OUTPUT); 
  pinMode(pin_downpin, OUTPUT); 
  VerifyLed();
  Serial.begin(BAUDRATE);  
}

void loop()
{
  ReadCommand();  
  delay(1000);
}

void WriteCommand(const char *str)
{
  Serial.println(str);
}

void ReadCommand(void)
{
  //Serial.print("ReadCommand\n");
  int readsize=0;
  
  if(test_mode>0)
      readsize=10;
      
  if ( ((readsize=Serial.available()) > 0) || test_mode>0) {
    //Serial.print("read data from serial");
    char buf[readsize];
    if(0!=Serial.readBytes(buf, readsize) || test_mode>0)
    {
      //Serial.print("readsize is %3d\n",readsize);
      //It means vliad data was found
      if(memcmp(buf,UpCmd,readsize)==0 /*&& test_mode==1*/)
      {
        //match UpCmd
        //Serial.print("match IamUpButton command\n");
        DoUp();
      }
      else if(memcmp(buf,StopCmd,readsize)==0 /*&& test_mode==2*/)
      {
        //match StopCmd
        //Serial.print("match IamStopButton command\n");
        DoStop();
      }
      else if(memcmp(buf,DownCmd,readsize)==0 /*&& test_mode==3*/)
      {
        //match DownCmd
        //Serial.print("match IamDownButton command\n");
        DoDown();
      }
      else
      {
        Serial.print("Not expect value\n");
      }
      
      //test_mode = test_mode%3+1;
    }
  }
}

void VerifyLed(void)
{
  digitalWrite(pin_uppin, HIGH);
  digitalWrite(pin_stoppin, HIGH);
  digitalWrite(pin_downpin, HIGH);
  delay(delaytime_verifyled);
  digitalWrite(pin_uppin, LOW);
  digitalWrite(pin_stoppin, LOW);
  digitalWrite(pin_downpin, LOW);
}

void ResetStatus(void)
{
  digitalWrite(pin_uppin, LOW);
  digitalWrite(pin_stoppin, LOW);
  digitalWrite(pin_downpin, LOW);
  delay(delaytime);
}

void DoUp(void)
{
  digitalWrite(pin_uppin, HIGH);
  digitalWrite(pin_stoppin, LOW);
  digitalWrite(pin_downpin, LOW);
  delay(delaytime);
  ResetStatus();
}

void DoStop(void)
{
  digitalWrite(pin_uppin, LOW);
  digitalWrite(pin_stoppin, HIGH);
  digitalWrite(pin_downpin, LOW);
  delay(delaytime);  
  ResetStatus();
}

void DoDown(void)
{
  digitalWrite(pin_uppin, LOW);
  digitalWrite(pin_stoppin, LOW);
  digitalWrite(pin_downpin, HIGH);
  delay(delaytime);
  ResetStatus();
}
