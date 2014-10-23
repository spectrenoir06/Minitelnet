#include <SPI.h>
#include <Ethernet.h>
#include <SoftwareSerial.h>
#include <Minitel.h>

Minitel m(6,7,4800);

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xCF
};
IPAddress ip(192, 168, 0, 177);

byte server[] = {192, 168, 1, 2};
int port = 23;

byte datado[] = {0xFF, 0xFA, 0x1F, 0x00, 0x50, 0x00, 0x18, 0xFF, 0xF0}; // IAC, SB, windows size, 00, 80, 00, 24, IAC, END
byte datawill[] = {0xFF, 0xFB, 0x18, 0xFF, 0xFB, 0x20, 0xFF, 0xFC, 0x23, 0xFF, 0xFC, 0x27, 0xFF, 0xFD, 0x03, 0xFF, 0xFD, 0x05};
byte datasb[] = {0xFF, 0xFA, 0x20, 0x00, 0x33, 0x38, 0x34, 0x30, 0x30, 0x2C, 0x33, 0x38, 0x34, 0x30, 0x30, 0xFF, 0xF0,
                 0xFF, 0xFA, 0x18, 0x00, 0X56, 0X54, 0X31, 0X30, 0x30, 0XFF, 0XF0};
byte data3[] = {0xFF, 0xFB, 0x1F,
                //0xFF, 0xFB, 0x03,
                0xFF, 0xFC, 0x01,
                0xFF, 0xFB, 0x21
                };
byte  data4[] = {0xFF, 0xFD, 0x01};

byte  clearcmd[] = {0x1B, 0x5B, 0x48, 0x1B, 0x5B, 0x4A};
byte  goUp[] = {0x1B,  0x5B, 0x41};

char tablekey[256];

int stage = 0;

//bool majkey = false;

char telnet[][6] = {
  "SE", // 240
  "NOP",
  "data",
  "Break",
  "",
  "",
  "",
  "",
  "",
  "GA", // 249
  "SB",
  "WILL",
  "WONT",
  "DO",
  "DONT",
  "IAC"
 };
 
 char  str[4];

EthernetClient client;


void inittelnet(){
  int etape=0;
  while (1){
   if (stage == 0){
     delay(50);
     client.write(datawill,18);
     stage++;
   }
   else if (stage == 1){
     delay(50);
     client.write(datasb,28);
     stage++;
   }
   else if (stage == 2){
     delay(50);
     client.write(data3,15);
     stage++;
   }
   else if (stage == 3){
     delay(50);
     client.flush();
     while (client.available()){
       client.read();
     }
     client.write(data4,3);
     return;
   }
 }
}

void setup() {
  
  tablekey[65]    = 'A';
  tablekey[66]    = 'B';
  tablekey[195]   = 'C';
  tablekey[68]    = 'D';
  tablekey[197]   = 'E';
  tablekey[198]   = 'F';
  tablekey[71]    = 'G';
  tablekey[72]    = 'H';
  tablekey[201]   = 'I';
  tablekey[202]   = 'J';
  tablekey[75]    = 'K';
  tablekey[204]   = 'L';
  tablekey[77]    = 'M';
  tablekey[78]    = 'N';
  tablekey[207]   = 'O';
  tablekey[80]    = 'P';
  tablekey[209]   = 'Q';
  tablekey[210]   = 'R';
  tablekey[83]    = 'S';
  tablekey[212]   = 'T';
  tablekey[85]    = 'U';
  tablekey[86]    = 'V';
  tablekey[215]   = 'W';
  tablekey[216]   = 'X';
  tablekey[89]    = 'Y';
  tablekey[90]    = 'Z';
  
  tablekey[225]    = 'a';
  tablekey[226]    = 'b';
  tablekey[99]    = 'c';
  tablekey[228]    = 'd';
  tablekey[101]   = 'e';
  tablekey[102]   = 'f';
  tablekey[231]    = 'g';
  tablekey[232]    = 'h';
  tablekey[105]   = 'i';
  tablekey[106]   = 'j';
  tablekey[235]    = 'k';
  tablekey[108]   = 'l';
  tablekey[237]    = 'm';
  tablekey[238]    = 'n';
  tablekey[111]   = 'o';
  tablekey[240]    = 'p';
  tablekey[113]   = 'q';
  tablekey[114]   = 'r';
  tablekey[243]    = 's';
  tablekey[116]   = 't';
  tablekey[245]    = 'u';
  tablekey[246]    = 'v';
  tablekey[119]   = 'w';
  tablekey[120]   = 'x';
  tablekey[249]    = 'y';
  tablekey[250]    = 'z';
  
  tablekey[177]   = '1';
  tablekey[178]   = '2';
  tablekey[51]    = '3';
  tablekey[180]   = '4';
  tablekey[53]    = '5';
  tablekey[54]    = '6';
  tablekey[183]   = '7';
  tablekey[184]   = '8';
  tablekey[57]    = '9';
  tablekey[170]   = '*';
  tablekey[48]    = '0';
  tablekey[163]   = '#';
  
  tablekey[160]   = ' ';
  tablekey[172]   = ',';
  tablekey[46]    = '.';
  tablekey[39]   = '\'';
  tablekey[187]   = ';';
  tablekey[45]   = '-';
  tablekey[58]   = ':';
  tablekey[63]   = '?';
  
  tablekey[141]   = '\n';
  
  
  // start the Ethernet connection:
   if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to configure Ethernet using DHCP");
      // no point in carrying on, so do nothing forevermore:
      // try to congifure using IP address instead of DHCP:
      Ethernet.begin(mac, ip);
  }
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.flush();
  //m.clearScreen();
  for (byte i=0; i<6; i++)
     m.serialprint7(clearcmd[i]);
  delay(200);
  m.serialprint7(0x1F);
  m.serialprint7(0x40);
  m.serialprint7(0x41);
  m.text("My ip = ");
  Serial.print("My IP address: ");
  for (byte i=0; i<3; i++)
     m.serialprint7(goUp[i]);
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
    itoa(Ethernet.localIP()[thisByte], str, 10);
    m.text(str);
    m.serialprint7('.');
    //m.text(String s, int x, int y) {
  }
  m.text("  , Server ip =");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    itoa(server[thisByte], str, 10);
    m.text(str);
    m.serialprint7('.');
    //m.text(String s, int x, int y) {
  }
  m.serialprint7('\n');
  m.serialprint7('\r');
  Serial.println();
  
  Serial.println("connecting...");

  int statut;
  statut = client.connect(server, port);
  if (statut == 1) {
    Serial.println("connected");
    //m.serialprint7("connected");
}
  else {
    // if you didn't get a connection to the server:
    Serial.print("connection failed statut = ");
    Serial.println(statut);
  }
  inittelnet();
}

void loop()
{
  if (client.available()) {
     byte c = client.read();
     //Serial.print((char)c);
     m.serialprint7(c);
  }
  
  byte keynb = m.getKeyCode();
  
  if (keynb != 255){
    if (keynb == 207)
    {
      delay(50);
    }
    else
      client.print(tablekey[keynb]);
   }
   
    //Serial.println((byte)key);  
  
  //Serial.println((byte) m.getKey());
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    // do nothing:
    while (true){
       byte keynb = m.getKeyCode();
       byte key = m.getKey();
  
      if (keynb != 255){
         client.print(key);
         Serial.print("nb=");
         Serial.print(keynb);
         Serial.print(" , char=");
         Serial.print((char) keynb);
         Serial.print(", key =");
         Serial.print(key);
         Serial.print(" , char=");
         Serial.println((char)key);
        // Serial.println("helllo");
         //delay(500);
     }
   };
  }
}




