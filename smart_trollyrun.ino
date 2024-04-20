#include <SoftwareSerial.h>
#include <string.h>
#include <LiquidCrystal.h> 

//GSM
#define RX_PIN 9
#define TX_PIN 10

//Switches
#define Up   A0
#define Down A1
#define Ok   A2
#define Done A3

SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX, TX
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 


char SMSRead[100];
char RFIDData[15];

/* Store RFID card details */
const char RFID_1[15] = "3C00AE61887B";   //Milk
const char RFID_2[15] = "3C00AE7B739A";   //Egg
const char RFID_3[15] = "3C00AF71799B";   //Oil
const char RFID_4[15] = "3C00AF352284";   //Soap

unsigned int CartDB[4] = {0, 0, 0, 0};

/* Price deatils */
unsigned int Price[4] = {50, 10, 200, 30};

char Buffer_data = "";
unsigned int  Count = 0;
unsigned long Total = 0;

  
void setup() {

  mySerial.begin(19200); // SIM900 module
  Serial.begin(9600);    //For RFID Reader

  lcd.begin(16, 2);//lcd init with 16*2

/* Pin mode for Switches */
  pinMode(Up,   INPUT_PULLUP);
  pinMode(Down, INPUT_PULLUP);
  pinMode(Ok,   INPUT_PULLUP); 
  pinMode(Done, INPUT_PULLUP);    

/* welcome note */
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME TO SMART");   //1st line
  lcd.setCursor(0, 1);
  lcd.print("BILLING SYSTEM");     //2nd line
   delay(3000);
}

void loop() 
{
  /*if(RegDone == 0)
  {
    WaitForRegistration();
    FindRegistedNumber();
  }
  else*/
 
  WaitForRfidSwipe();
  IdentifyScannedItem();
 // DisplyAndCount();
}

void IdentifyScannedItem(void)
{
    lcd.clear();

    if (strcmp(RFIDData, RFID_1) == 0)
    {
      lcd.setCursor(0, 0);
      lcd.print("Item:Milk Rs-");
      lcd.print(Price[0]);

      lcd.setCursor(0, 1);
      lcd.print("C=");
      lcd.print(CartDB[0]);
      lcd.print(" T=");
      Total = ((CartDB[0]) * (Price[0])) + ((CartDB[1]) * (Price[1])) + ((CartDB[2]) * (Price[2])) + ((CartDB[3]) * (Price[3]));
      lcd.print(Total);
      ItemIndex = 0;
    }
    else if (strcmp(RFIDData, RFID_2) == 0)
    {
      lcd.setCursor(0, 0);
      lcd.print("Item:Egg Rs-");
      lcd.print(Price[1]);

      lcd.setCursor(0, 1);
      lcd.print("C=");
      lcd.print(CartDB[1]);
      lcd.print(" T=");
      Total =((CartDB[0]) * (Price[0])) + ((CartDB[1]) * (Price[1])) + ((CartDB[2]) * (Price[2])) + ((CartDB[3]) * (Price[3]));
      lcd.print(Total);
      ItemIndex = 1;
    }
    else if (strcmp(RFIDData, RFID_3) == 0)
    {
      lcd.setCursor(0, 0);
      lcd.print("Item:Oil Rs-");
      lcd.print(Price[2]);

      lcd.setCursor(0, 1);
      lcd.print("C=");
      lcd.print(CartDB[2]);
      lcd.print(" T=");
      Total = ((CartDB[0]) * (Price[0])) + ((CartDB[1]) * (Price[1])) + ((CartDB[2]) * (Price[2])) + ((CartDB[3]) * (Price[3]));
      lcd.print(Total);
      ItemIndex = 2;
    }
    else if (strcmp(RFIDData, RFID_4) == 0)
    {
      lcd.setCursor(0, 0);
      lcd.print("Item:Soap Rs-");
      lcd.print(Price[3]);

      lcd.setCursor(0, 1);
      lcd.print("C=");
      lcd.print(CartDB[3]);
      lcd.print(" T=");
      Total = ((CartDB[0]) * (Price[0])) + ((CartDB[1]) * (Price[1])) + ((CartDB[2]) * (Price[2])) + ((CartDB[3]) * (Price[3]));
      lcd.print(Total);
      ItemIndex = 3;
    }   
    delay(9000);   
}

void clearSerialBuffer() 
{
  while (Serial.available() > 0) 
  {
    char c = Serial.read(); 
  }
}

void WaitForRfidSwipe(void)
{
  unsigned int index = 0;
  
  /* Write data to LCD display */
  lcd.clear();
  clearSerialBuffer();
  lcd.setCursor(0, 0);
  lcd.print("Please Scan Item");


  for(index= 0; index < 12 ; index++)
  {
    while(!Serial.available())
    {

    }
    while(Serial.available()>0) 
    {
      RFIDData[index] = Serial.read();
    }
  }
  RFIDData[index] = '\0';
}
