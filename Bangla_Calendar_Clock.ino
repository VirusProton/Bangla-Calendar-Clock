#include "time.h"
#include <WiFi.h>
#include <WiFiUdp.h>
#include "RTClib.h"

#include <LedControl.h> // For Bangla Print in LED MAtrix


#define NBR_MTX 24 //number of matrices attached is 8

#define CLK_PIN   18 // or SCK
#define DATA_PIN  19 // or MOSI
#define CS_PIN    5 // or SS


LedControl lc=LedControl(DATA_PIN,CLK_PIN,CS_PIN,NBR_MTX);



// SSID and password of Wifi connection:
//char* ssid = "silicon valley";
//char* password = "silicon14";


//char* ssid = "Taufiqur";
//char* password = "12345678";

char* ssid = "Virus_Proton";
char* password = "123456789O";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 21600;
const int   daylightOffset_sec = 0;





RTC_DS3231 rtc;


int count = 0;


byte shunno_small_1[8] = {0x18, 0x24, 0x42, 0x42, 0x42, 0x42, 0x24, 0x18};
byte ek_small_1[8] = {0x60, 0x70, 0x1c, 0x06, 0x02, 0x62, 0x76, 0x3c};
byte dui_small_1[8] = {0x60, 0x7c, 0x06, 0x06, 0x7c, 0x60, 0x30, 0x1e};
byte tin_small_1[8] = {0x0c, 0x5a, 0x5a, 0x42, 0x42, 0x42, 0x42, 0x3c};
byte char_small_1[8] = {0x3c, 0x66, 0x66, 0x3c, 0x3c, 0x66, 0x66, 0x3c};
byte pach_small_1[8] = {0x30, 0x38, 0x46, 0x48, 0x4a, 0x46, 0x62, 0x3c};
byte chhoy_small_1[8] = {0x18, 0x58, 0x48, 0x4a, 0x4e, 0x42, 0x62, 0x3e};
byte shaat_small_1[8] = {0x38, 0x44, 0x44, 0x3c, 0x04, 0x04, 0x06, 0x06};
byte aat_small_1[8] = {0x60, 0x60, 0x26, 0x22, 0x3e, 0x24, 0x24, 0x38};
byte noy_small_1[8] = {0x60, 0x78, 0x0c, 0x06, 0x72, 0x4a, 0x6a, 0x0e};



byte Zero_1[8] = {0x00,0x00,0x3C,0x66,0x42,0x42,0x42,0x42};
byte Zero_2[8] = {0x42,0x42,0x42,0x42,0x66,0x3C,0x00,0x00};

byte One_1[8] = {0x00,0x00,0x60,0x60,0x30,0x18,0x0C,0x06};
byte One_2[8] = {0x02,0x02,0x02,0x62,0x76,0x3C,0x00,0x00};

byte Two_1[8] = {0x00,0x00,0x60,0x60,0x38,0x0C,0x06,0x02};
byte Two_2[8] = {0x66,0x7C,0x30,0x18,0x0C,0x06,0x00,0x00};

//byte Three_1[8] = {0x00,0x00,0x0C,0x1E,0x5E,0x5E,0x4E,0x42};
//byte Three_2[8] = {0x42,0x42,0x42,0x42,0x66,0x3C,0x00,0x00};

byte Three_1[8] = {0x00,0x00,0x00,0x1C,0x5A,0x5A,0x42,0x42};
byte Three_2[8] = {0x42,0x42,0x42,0x42,0x66,0x3C,0x00,0x00};

byte Four_1[8] = {0x00,0x00,0x3C,0x66,0x42,0x42,0x66,0x3C};
byte Four_2[8] = {0x3C,0x66,0x42,0x42,0x66,0x3C,0x00,0x00};

byte Five_1[8] = {0x00,0x00,0x22,0x26,0x5C,0x44,0x48,0x48};
byte Five_2[8] = {0x4A,0x46,0x62,0x32,0x1C,0x00,0x00,0x00};

byte Six_1[8] = {0x00,0x00,0x0C,0x4C,0x48,0x48,0x48,0x48};
byte Six_2[8] = {0x4A,0x4E,0x42,0x62,0x36,0x1C,0x00,0x00};

byte Seven_1[8] = {0x00,0x00,0x3C,0x66,0x42,0x42,0x62,0x3E};
byte Seven_2[8] = {0x02,0x02,0x02,0x02,0x03,0x03,0x00,0x00};

byte Eight_1[8] = {0x00,0xC0,0xC0,0x40,0x43,0x43,0x46,0x4C};
byte Eight_2[8] = {0x7C,0x66,0x42,0x42,0x66,0x3C,0x00,0x00};

byte Nine_1[8] = {0x00,0x00,0x60,0x60,0x30,0x18,0x0C,0x06};
byte Nine_2[8] = {0x02,0x02,0x3A,0x66,0x76,0x34,0x00,0x00};




byte r_Zero_1[8] = {0x00,0x00,0x78,0xCD,0x85,0x84,0x84,0x84};
byte r_Zero_2[8] = {0x84,0x84,0x84,0x85,0xCD,0x78,0x00,0x00};

byte r_One_1[8] = {0x00,0x00,0xC0,0xC1,0x61,0x30,0x18,0x0C};
byte r_One_2[8] = {0x04,0x04,0x04,0xC5,0xED,0x78,0x00,0x00};

byte r_Two_1[8] = {0x00,0x00,0xC0,0xC1,0x71,0x18,0x0C,0x04};
byte r_Two_2[8] = {0xCC,0xF8,0x60,0x31,0x19,0x0C,0x00,0x00};


byte r_Three_1[8] = {0x00,0x00,0x38,0xB5,0xB5,0x84,0x84,0x84};
byte r_Three_2[8] = {0x84,0x84,0x84,0x85,0xCD,0x78,0x00,0x00};

byte r_Four_1[8] = {0x00,0x00,0x78,0xCD,0x85,0x84,0xCC,0x78};
byte r_Four_2[8] = {0x78,0xCC,0x84,0x85,0xCD,0x78,0x00,0x00};

byte r_Five_1[8] = {0x00,0x00,0x44,0x4D,0xB9,0x88,0x90,0x90};
byte r_Five_2[8] = {0x90,0x94,0x8C,0xC5,0x65,0x38,0x00,0x00};


byte r_Six_1[8] = {0x00,0x00,0x18,0x99,0x91,0x90,0x90,0x90};
byte r_Six_2[8] = {0x94,0x9C,0x84,0xC5,0x6D,0x38,0x00,0x00};

byte r_Seven_1[8] = {0x00,0x00,0x78,0xCD,0x85,0x84,0xC4,0x7C};
byte r_Seven_2[8] = {0x04,0x04,0x05,0x07,0x06,0x00,0x00,0x00};

byte r_Eight_1[8] = {0x00,0x00,0x80,0x81,0x87,0x86,0x8C,0x98};
byte r_Eight_2[8] = {0xF8,0xCC,0x84,0x85,0xCD,0x78,0x00,0x00};

byte r_Nine_1[8] = {0x00,0x00,0xC0,0xC1,0x61,0x30,0x18,0x0C};
byte r_Nine_2[8] = {0x04,0x04,0x74,0xCD,0xED,0x68,0x00,0x00};



byte l_Zero_1[8] = {0x00,0x00,0x1E,0xB3,0xA1,0x21,0x21,0x21};
byte l_Zero_2[8] = {0x21,0x21,0x21,0xA1,0xB3,0x1E,0x00,0x00};

byte l_One_1[8] = {0x00,0x00,0x30,0xB0,0x98,0x0C,0x06,0x03};
byte l_One_2[8] = {0x01,0x01,0x01,0xB1,0xBB,0x1E,0x00,0x00};

byte l_Two_1[8] = {0x00,0x00,0x30,0xB0,0x9C,0x06,0x03,0x01};
byte l_Two_2[8] = {0x33,0x3E,0x18,0x8C,0x86,0x03,0x00,0x00};

byte l_Three_1[8] = {0x00,0x00,0x0E,0xAD,0xAD,0x21,0x21,0x21};
byte l_Three_2[8] = {0x21,0x21,0x21,0xA1,0xB3,0x1E,0x00,0x00};

byte l_Four_1[8] = {0x00,0x00,0x1E,0xB3,0xA1,0x21,0x33,0x1E};
byte l_Four_2[8] = {0x1E,0x33,0x21,0xA1,0xB3,0x1E,0x00,0x00};

byte l_Five_1[8] = {0x00,0x00,0x11,0x93,0xAE,0x22,0x24,0x24};
byte l_Five_2[8] = {0x24,0x25,0x23,0xB1,0x99,0x0E,0x00,0x00};


byte l_Six_1[8] = {0x00,0x00,0x06,0x86,0xA4,0x24,0x24,0x24};
byte l_Six_2[8] = {0x25,0x27,0x21,0xB1,0x9B,0x0E,0x00,0x00};

byte l_Seven_1[8] = {0x00,0x00,0x1E,0xB3,0xA1,0x21,0x31,0x1F};
byte l_Seven_2[8] = {0x01,0x01,0x01,0x81,0x81,0x01,0x00,0x00};

byte l_Eight_1[8] = {0x00,0x00,0x60,0xE0,0xA1,0x21,0x23,0x26};
byte l_Eight_2[8] = {0x3E,0x33,0x21,0xA1,0xB3,0x1E,0x00,0x00};

byte l_Nine_1[8] = {0x00,0x00,0x30,0xB0,0x98,0x0C,0x06,0x03};
byte l_Nine_2[8] = {0x01,0x01,0x1D,0xB3,0xBB,0x1A,0x00,0x00};


byte shonibar[2][8] = {{0x00,0x05,0xDF,0x25,0x55,0x05,0x05,0x00},
                      {0xF0,0x08,0xFE,0x08,0x68,0x58,0x08,0x00}};


byte robibar[2][8] = {{0x01,0x02,0xFF,0x3A,0x4A,0x2A,0x5A,0x00},
                      {0xE0,0x10,0xFC,0x70,0x90,0x90,0x70,0x00}};


byte shombar[2][8] = {{0x00,0x00,0xFF,0x29,0x45,0x47,0x2D,0x00},
                  {0x00,0x40,0x7F,0xD2,0x4A,0x5E,0x5A,0x00}};


byte mongol[2][8] = {{0x04,0x03,0xFA,0x99,0x56,0xF1,0xD3,0x00},
                    {0x00,0x40,0x7F,0xC1,0x4B,0x55,0x51,0x00}};

byte budhbar[2][8] = {{0x01,0x02,0xFE,0x39,0x4A,0x39,0x14,0x0A},
                     {0x00,0x00,0xF0,0x40,0x40,0xC0,0x40,0x00}};

byte briho[2][8] = {{0x00,0x00,0xFF,0x3B,0x48,0x3B,0x11,0x1C},
                   {0x00,0x00,0xD8,0x18,0x80,0x18,0xD8,0x00}};

byte shukro[2][8] = {{0x00,0x02,0xDB,0x26,0x52,0x06,0x0A,0x05},
                    {0x00,0x00,0xFF,0x3C,0x4A,0x3A,0x98,0x68}};




byte january[3][8] = {{0x00,0x02,0xFB,0x36,0xAB,0x9B,0xF6,0x00},
                      {0x00,0x00,0xFF,0x29,0xA5,0x6F,0xA1,0xD4},
                      {0x0E,0x51,0x7F,0xD3,0x55,0x53,0x55,0x00}};


byte february[3][8] = {{0x00,0x00,0x1F,0x05,0x08,0x09,0x04,0x00},
            {0x00,0x00,0xFF,0x30,0xA8,0x2A,0xE1,0x00},
            {0x00,0x00,0xF8,0xE0,0xA0,0x60,0xD4,0x68}};



byte march[3][8] = {{0x00,0x00,0x07,0x02,0x01,0x03,0x03,0x00},
          {0x00,0x11,0xDF,0x74,0x57,0xD4,0x57,0x00},
          {0x80,0x00,0xC0,0x00,0x80,0x80,0x00,0x00}};



byte april[3][8] = {{0x00,0x00,0x0D,0x0A,0x02,0x26,0x1A,0x00},
          {0x78,0x86,0xDB,0xA6,0x9A,0x92,0xC6,0x3A},
          {0x00,0x00,0xFC,0x08,0x58,0xA8,0x88,0x00}};



byte may[3][8] = {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
          {0x00,0x00,0xFF,0x52,0x8A,0x9E,0x5A,0x00},
          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};



byte june[3][8] = {{0x00,0x00,0x0F,0x01,0x05,0x04,0x07,0x00},
           {0x00,0x00,0xFF,0xC0,0x27,0xA4,0xD6,0x68},
           {0x00,0x00,0xE0,0x40,0x40,0xC0,0x40,0x00}};



byte july[3][8] = {{0x00,0x00,0x3F,0x0E,0x29,0x25,0x3E,0x03},
           {0x00,0x01,0xFD,0x07,0x2D,0x55,0x85,0x40},
           {0xE0,0x10,0xFC,0x60,0x10,0x60,0x38,0x00}};



byte august[3][8] = {{0x00,0x00,0xFE,0x1B,0x56,0x46,0x3A,0x00},
                    {0x00,0x82,0xDB,0xA6,0x92,0xB2,0x82,0x00},
                    {0x98,0x64,0xFF,0x90,0x76,0x92,0x0C,0x00}};



byte september[3][8] = {{0x00,0x00,0xFF,0x52,0x8B,0x8F,0x5A,0x00},
            {0x98,0x64,0xEF,0xD8,0x68,0x0A,0x8E,0x00},
            {0x00,0x00,0xFF,0x53,0xF5,0x73,0x55,0x30}};



byte october[3][8] = {{0x00,0x00,0xFF,0x34,0xAD,0x8D,0x74,0x00},
            {0x90,0x69,0xFD,0xBF,0x55,0x33,0x9D,0x00},
            {0x00,0x00,0xFF,0x33,0x55,0x53,0x35,0x00}};



byte november[3][8] = {{0x00,0x00,0xFF,0x04,0x75,0x4D,0x64,0x00},
             {0x00,0x00,0xFF,0x98,0x51,0x4C,0xB8,0x00},
             {0x00,0x00,0xFF,0xA7,0xE9,0xE5,0xAB,0x60}};



byte december[3][8] = {{0x78,0x84,0xFF,0x88,0xAD,0xA5,0x9C,0x00},
             {0x00,0x00,0xFF,0xA4,0x15,0x1C,0xB4,0x00},
             {0x00,0x00,0xFF,0xA7,0xE9,0xE5,0xAB,0x60}};



byte boishakh[3][8] = {{0x60,0x10,0xFF,0x27,0x49,0x4D,0x23,0x00},
             {0x00,0x05,0xDD,0x27,0x55,0x05,0x05,0x00},
             {0x00,0x02,0xEB,0x7A,0x0A,0x32,0x0E,0x00}};



byte joishtho[3][8] = {{0x30,0x08,0x7F,0x11,0x25,0x24,0x13,0x00},
             {0x00,0x00,0xFF,0xC5,0x28,0xA4,0xA8,0x00},
             {0x1C,0x20,0xFE,0x38,0xE4,0xA4,0x78,0x00}};



byte ashar[3][8] = {{0x00,0x00,0xFE,0x1B,0x56,0x46,0x3A,0x00},
            {0x00,0x81,0xFD,0xA7,0x95,0xAD,0x9D,0x00},
            {0x00,0x00,0xFE,0x40,0x4C,0x44,0x38,0x10}};


byte srabon[3][8] = {{0x00,0x01,0x37,0x09,0x15,0x01,0x23,0x1D},
          {0x00,0x40,0x7F,0xCE,0x52,0x5A,0x46,0x00},
          {0x00,0x08,0x6C,0x98,0xC8,0x08,0x08,0x00}};


byte bhadro[3][8] = {{0x00,0x00,0x0F,0x00,0x04,0x02,0x01,0x00},
                    {0x00,0x08,0xEF,0x59,0x89,0x69,0xCA,0x01},
                    {0x00,0x00,0xF0,0x00,0x20,0xD0,0x90,0x60}};


byte ashin[3][8] = {{0x00,0x00,0xFE,0x1B,0x56,0x46,0x3A,0x00},
          {0x1E,0xA1,0xFB,0xA4,0xAA,0xA1,0xA2,0x01},
          {0x00,0x80,0xFF,0x82,0xBA,0xA6,0xB2,0x80}};
          
          

byte kartik[3][8] = {{0x00,0x00,0xFE,0x3D,0x4A,0x6A,0x18,0x00},
          {0x1C,0xA3,0xFF,0xA3,0xAA,0xA8,0xA7,0x00},
          {0x80,0x00,0xFF,0x1E,0xA5,0xB5,0x0C,0x00}};



byte ogrohayon[3][8] = {{0x00,0x00,0x1F,0x03,0x0A,0x08,0x07,0x00},
            {0x00,0x00,0xF6,0x49,0xC4,0xCC,0x51,0x0E},
            {0x00,0x80,0xD8,0x98,0x80,0x98,0x98,0x00}};



byte poush[3][8] = {{0x00,0x00,0x0E,0x05,0x08,0x08,0x04,0x00},
          {0xB8,0x54,0xDF,0x35,0xD4,0x95,0x14,0x00},
          {0x00,0x00,0xF0,0x20,0xA0,0x60,0xE0,0x00}};



byte magh[3][8] = {{0x00,0x00,0x07,0x02,0x01,0x03,0x03,0x00},
           {0x00,0x10,0xDF,0x74,0x55,0xD2,0x53,0x00},
           {0x00,0x00,0xE0,0x40,0x40,0x40,0xC0,0x00}};



byte falgun[3][8] = {{0x00,0x00,0xFE,0x4D,0x2A,0x4A,0x38,0x00},
          {0x00,0x80,0xF8,0x86,0xA9,0xD4,0x8D,0x01},
          {0x00,0x80,0xFF,0x81,0x9D,0x93,0x59,0xA0}};



byte choitro[3][8] = {{0x06,0x01,0x0F,0x02,0x04,0x04,0x02,0x00},
            {0x00,0x00,0xFF,0x81,0xF1,0x94,0xE3,0x00},
            {0x00,0x00,0xF0,0xC0,0x20,0x60,0xA0,0x00}};



byte muharram[3][8] = {{0x00,0x00,0xFF,0x44,0x24,0x7C,0x6A,0x0D},
                      {0x00,0x00,0xFF,0xC6,0x2A,0xC6,0x6A,0x00},
                      {0x00,0x00,0xFF,0x69,0xA5,0x6F,0xAD,0x00}};


byte sofor[3][8] = {{0x00,0x00,0x1F,0x09,0x05,0x07,0x0D,0x00},
          {0x00,0x00,0xFF,0x4C,0x2A,0x4A,0x38,0x00},
          {0x00,0x00,0xF8,0x70,0x90,0x50,0xB0,0x00}};


byte robiul_aual[3][8] = {{0x00,0x00,0xFC,0x38,0x48,0x28,0x5A,0x00},
              {0x00,0x00,0xFE,0x1B,0x56,0x46,0x3A,0x00},
              {0x38,0x84,0xFE,0x88,0xAC,0xA4,0x9D,0x00}};



byte robius_sani[3][8] = {{0x00,0x00,0xFD,0x38,0x48,0x28,0x5A,0x00},
              {0x00,0x05,0xF7,0x9D,0x55,0x75,0xD5,0x00},
              {0xF8,0x04,0xFE,0x04,0x74,0x4C,0x65,0x00}};



byte joma_aual[3][8] = {{0x00,0x00,0xFE,0x1C,0x52,0x4A,0x7A,0x00},
            {0x00,0x00,0x7F,0x0D,0x2B,0x23,0x9D,0x00},
            {0x1C,0x42,0x7F,0xC4,0x56,0x52,0x4E,0x00}};



byte joma_sani[3][8] = {{0x00,0x00,0xFD,0x38,0xA4,0x94,0xF6,0x00},
            {0x00,0x05,0xF7,0x9D,0x55,0x75,0xD5,0x00},
            {0xF8,0x04,0xFE,0x04,0x74,0x4C,0x65,0x00}};



byte rojob[3][8] = {{0x00,0x00,0x1F,0x07,0x09,0x05,0x0B,0x00},
          {0x00,0x00,0xFF,0x1C,0x52,0x4A,0x7A,0x00},
          {0x00,0x00,0xF8,0x70,0x90,0xD0,0x30,0x00}};



byte shaban[3][8] = {{0x00,0x02,0x6E,0x13,0x3A,0x2A,0x02,0x00},
          {0x00,0x81,0xFD,0x9F,0xA5,0xB5,0x8D,0x00},
          {0x00,0x00,0xFE,0x04,0x74,0x4C,0x64,0x00}};


byte romjan[3][8] = {{0x00,0x00,0xFF,0x74,0x92,0x57,0xB6,0x00},
          {0x00,0x00,0xFF,0x8E,0xA9,0xA5,0xBD,0x00},
          {0x00,0x40,0x7F,0xC1,0x5D,0x53,0x59,0x00}};



byte shaoal[3][8] = {{0x00,0x0A,0xBA,0x4F,0xEA,0xAB,0x0A,0x00},
          {0x00,0x00,0xDF,0x29,0x45,0x2F,0xE1,0x04},
          {0x00,0x40,0x7F,0xC1,0x4B,0x55,0x51,0x00}};



byte jilkad[3][8] = {{0x78,0x84,0xFF,0x9C,0xD2,0xCB,0xBD,0x03},
          {0x00,0x00,0xFF,0x09,0x5A,0xAA,0x09,0x00},
          {0x00,0x00,0xFF,0xC8,0xAB,0xAD,0x89,0x00}};


byte jilhajj[3][8] = {{0x78,0x84,0xFF,0x9C,0xD2,0xCB,0xBD,0x03},
           {0x00,0x00,0xFF,0x0B,0x58,0xAB,0x09,0x00},
           {0x00,0x00,0xFF,0x0C,0xAA,0x25,0x9B,0x0D}};
           

byte bangla_year[3][8] = {{0x60,0x71,0x09,0x04,0x05,0x65,0x65,0x38},
                         {0xE6,0x17,0x10,0xE0,0xF7,0x16,0x13,0xE0},
                         {0x18,0x9C,0x42,0x41,0x81,0x0D,0x1B,0xDA}};

byte hizri_year[3][8] = {{0x60,0x71,0x09,0x04,0x05,0x65,0x65,0x38},
                        {0xE3,0x14,0x14,0xE3,0xF7,0x14,0x14,0xE3},
                        {0x8E,0x51,0x51,0x8E,0xDF,0x51,0x51,0x8E}};

byte english_year[3][8] = {{0x60,0x79,0x05,0x05,0x79,0x61,0x31,0x0C},
                          {0xE6,0x17,0x10,0x10,0x17,0x16,0x13,0xE0},
                          {0x18,0x9E,0x41,0x41,0x9E,0x18,0x0C,0xC3}};


byte raat[3][8] = {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
                  {0x00,0x01,0xFD,0x3B,0x49,0x29,0x59,0x00},
                  {0x00,0x00,0xFE,0x18,0x54,0x44,0x38,0x00}};

byte purbanno[3][8] = {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
                      {0x00,0x11,0xDF,0xB3,0x54,0x36,0x21,0x18},
                      {0x80,0x20,0xBF,0xEC,0xA3,0xAD,0xA6,0x00}};


byte modhhanno[3][8] = {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
                        {0x04,0x08,0xFB,0x96,0x5B,0xF6,0xD3,0x00},
                        {0x00,0x20,0xBF,0xEC,0x23,0xAD,0x26,0x00}};


byte Oporanno[3][8] = {{0x00,0x00,0x0F,0x02,0x09,0x09,0x06,0x00},
                      {0x00,0x08,0xEF,0xD9,0xAA,0x89,0x8A,0x00},
                      {0x00,0x20,0xBF,0xEC,0xA3,0xAD,0xA6,0x00}};


byte sayanno[3][8] = {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
                      {0x00,0x08,0xEF,0xBA,0x69,0x6B,0xA8,0x01},
                      {0x00,0x10,0xDF,0x76,0x53,0x55,0xD6,0x00}};


byte usha[3][8] = {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
                  {0x44,0x3A,0xFF,0x08,0xAE,0x62,0x1C,0x00},
                  {0x00,0x04,0xF7,0x9C,0x74,0x94,0x74,0x00}};



byte month_name[3][8];
byte bar_name[2][8];
byte prohor_name[3][8];



void setup(){
  Serial.begin(19200);
  
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");

  if (! rtc.begin()) { 
  Serial.println("Couldn't find RTC"); 
  while (1);
  }

 

  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
  
  for (int i=0; i< NBR_MTX; i++)
  {
    lc.shutdown(i,false);
  /* Set the brightness to a medium values */
    lc.setIntensity(i,1);
  /* and clear the display */
    lc.clearDisplay(i);
    delay(10);
  }



  
  Serial.print("hello");
  adjust_Time();
}



void loop() {  
  // put your main code here, to run repeatedly:
  //DateTime now = rtc.now();
  uint8_t ss = rtc.now().second();
  uint8_t mm = rtc.now().minute();
  uint8_t hh = rtc.now().hour();
  uint8_t d = rtc.now().day();
  uint8_t m = rtc.now().month();
  uint8_t yoff = rtc.now().year();

  int day_of_week = dayofweek(d, m+1, 2022);

  String str = String(hh) + ":" + String(mm) + ":" + String(ss) + "- " + String(d)+ " -" + String(m) + " -" + String(day_of_week);
  Serial.println(str);



  /*if(mm==0 && ss==0){
    wifi_synchronize();
    Serial.println("Wifi Synchronized");
  }*/

  
  //print hour
  print_big_num(hh/10,7,15);
  //print_big_num(hh%10,6,14);
  print_right_colon_big_num(hh%10,6,14);


  //print min
  //print_big_num(mm/10,5,13);
  print_left_colon_big_num(mm/10,5,13);
  print_big_num(mm%10,4,12);

  //print seconds
  print_small_num(ss/10,11);
  print_small_num(ss%10,10);


  find_prohor_name(hh);
  printByte(2, prohor_name[0]);
  printByte(1, prohor_name[1]);
  printByte(0, prohor_name[2]);

  find_bar_name(day_of_week);
  printByte(9, bar_name[0]);
  printByte(8, bar_name[1]);


  if(ss >= 40){
    GregorianToHizriMonthConverter(d,m+1,2022);
  }

  else if(ss<40){
    if(ss<20){
      GregorianToBanglaMonthConverter(d,m+1,2022);
    }
    else{
      print_small_num(d/10,23);
      print_small_num(d%10,22);

      find_month_name(m,0);
      printByte(21, month_name[0]);
      printByte(20, month_name[1]);
      printByte(19, month_name[2]);

      
      printByte(18,english_year[0]);
      printByte(17,english_year[1]);
      printByte(16,english_year[2]);
     }
    }
}


void adjust_Time(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  uint16_t year = timeinfo.tm_year + 1900;
  uint8_t month = timeinfo.tm_mon;
  uint8_t day = timeinfo.tm_mday;
  uint8_t hours = timeinfo.tm_hour;
  uint8_t minutes = timeinfo.tm_min;
  uint8_t seconds = timeinfo.tm_sec;
  //String str = String(hours) + ":" + String(minutes) + ":" + String(seconds) + "-" + String(day) + "-" + String(month) + "-" + String(year) + "-" +String(day_of_week);
  //Serial.println(str);
  rtc.adjust(DateTime(year, month, day,  hours,  minutes, seconds));

}



int dayofweek(int d, int m, int y)
{
  static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
  y -= m < 3;
  return ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}



void find_month_name(int m, int month_mode){
  if(month_mode == 0){
    switch(m){
     case 0: 
      memcpy(month_name, january, sizeof(month_name));
      break;
     case 1: 
      memcpy(month_name, february, sizeof(month_name));
      break;
     case 2: 
      memcpy(month_name, march, sizeof(month_name));
      break;
     case 3: 
      memcpy(month_name, april, sizeof(month_name));
      break;  
     case 4: 
      memcpy(month_name, may, sizeof(month_name));
      break;
     case 5: 
      memcpy(month_name, june, sizeof(month_name));
      break;
     case 6: 
      memcpy(month_name, july, sizeof(month_name));
      break;
     case 7: 
      memcpy(month_name, august, sizeof(month_name));
      break; 
     case 8: 
      memcpy(month_name, september, sizeof(month_name));
      break;
     case 9: 
      memcpy(month_name, october, sizeof(month_name));
      break;
     case 10: 
      memcpy(month_name, november, sizeof(month_name));
      break;
     case 11: 
      memcpy(month_name, december, sizeof(month_name));
      break;   
    }   
  }

  else if(month_mode == 1){
    switch(m){
     case 0: 
      memcpy(month_name, boishakh, sizeof(month_name));
      break;
     case 1: 
      memcpy(month_name, joishtho, sizeof(month_name));
      break;
     case 2: 
      memcpy(month_name, ashar, sizeof(month_name));
      break;
     case 3: 
      memcpy(month_name, srabon, sizeof(month_name));
      break;  
     case 4: 
      memcpy(month_name, bhadro, sizeof(month_name));
      break;
     case 5: 
      memcpy(month_name, ashin, sizeof(month_name));
      break;
     case 6: 
      memcpy(month_name, kartik, sizeof(month_name));
      break;
     case 7: 
      memcpy(month_name, ogrohayon, sizeof(month_name));
      break; 
     case 8: 
      memcpy(month_name, poush, sizeof(month_name));
      break;
     case 9: 
      memcpy(month_name, magh, sizeof(month_name));
      break;
     case 10: 
      memcpy(month_name, falgun, sizeof(month_name));
      break;
     case 11: 
      memcpy(month_name, choitro, sizeof(month_name));
      break;   
    } 
  }

  else if(month_mode == 2){
    switch(m){
     case 0: 
      memcpy(month_name, muharram, sizeof(month_name));
      break;
     case 1: 
      memcpy(month_name, sofor, sizeof(month_name));
      break;
     case 2: 
      memcpy(month_name, robiul_aual, sizeof(month_name));
      break;
     case 3: 
      memcpy(month_name, robius_sani, sizeof(month_name));
      break;  
     case 4: 
      memcpy(month_name, joma_aual, sizeof(month_name));
      break;
     case 5: 
      memcpy(month_name, joma_sani, sizeof(month_name));
      break;
     case 6: 
      memcpy(month_name, rojob, sizeof(month_name));
      break;
     case 7: 
      memcpy(month_name, shaban, sizeof(month_name));
      break; 
     case 8: 
      memcpy(month_name, romjan, sizeof(month_name));
      break;
     case 9: 
      memcpy(month_name, shaoal, sizeof(month_name));
      break;
     case 10: 
      memcpy(month_name, jilkad, sizeof(month_name));
      break;
     case 11: 
      memcpy(month_name, jilhajj, sizeof(month_name));
      break;   
    } 
  }
}



void GregorianToBanglaMonthConverter(int date2, int month2, int year2){
  // date2 = d+1, month2 = m+1, year2 = yoff+1
  if(month2>=4 && month2<=12)
    {
      year2=year2-593;
    }
    else
    {
      year2=year2-1-593;
    }
  
    if(month2==4)
    {
  
      if(date2<14)
      {
        month2=12;
        date2=date2+14+3;
      }
      else if(date2>=14)
      {
        month2=1;
        date2=date2-14+1;
      }
  
    }
    else if(month2==5)
    {
  
      if(date2<15)
      {
        month2=1;
        date2=date2+15+2;
      }
      else if(date2>=15)
      {
        month2=2;
        date2=date2-15+1;
      }
  
    }
    else if(month2==6)
    {
  
      if(date2<15)
      {
        month2=2;
        date2=date2+15+2;
      }
      else if(date2>=15)
      {
        month2=3;
        date2=date2-15+1;
      }
    }
    else if(month2==7)
    {
  
      if(date2<16)
      {
        month2=3;
        date2=date2+16;
      }
      else if(date2>=16)
      {
        month2=4;
        date2=date2-16+1;
      }
    }
    else if(month2==8)
    {
  
      if(date2<16)
      {
        month2=4;
        date2=date2+16;
      }
      else if(date2>=16)
      {
        month2=5;
        date2=date2-16+1;
      }
    }
    else if(month2==9)
    {
  
      if(date2<16)
      {
        month2=5;
        date2=date2+16;
      }
      else if(date2>=16)
      {
        month2=6;
        date2=date2-16+1;
      }
    }
    else if(month2==10)
    {
  
      if(date2<16)
      {
        month2=6;
        date2=date2+15;
      }
      else if(date2>=16)
      {
        month2=7;
        date2=date2-16+1;
      }
    }
    else if(month2==11)
    {
  
      if(date2<15)
      {
        month2=7;
        date2=date2+15+1;
      }
      else if(date2>=15)
      {
        month2=8;
        date2=date2-15+1;
      }
  
    }
    else if(month2==12)
    {
  
      if(date2<15)
      {
        month2=8;
        date2=date2+15+1;
      }
      else if(date2>=15)
      {
        month2=9;
        date2=date2-15+1;
      }
    }
    else if(month2==1)
    {
  
      if(date2<14)
      {
        month2=9;
        date2=date2+14+3;
      }
      else if(date2>=14)
      {
        month2=10;
        date2=date2-14+1;
      }
  
    }
    else if(month2==2)
    {
  
      if(date2<13)
      {
        month2=10;
             
        date2=date2+13+5;
      }
      else if(date2>=13)
      {
        month2=11;
             
        date2=date2-13+1;
      }
    }
    else if(month2==3)
    {
  
      if(date2<15)
      {
        month2=11;
             
        date2=date2+15+2;
      }
      else if(date2>=15)
      {
        month2=12;
             
        date2=date2-15+1;
      }
    }
    printf("%d-%d-%d",date2,month2,year2);

    print_small_num(date2/10,23);
    print_small_num(date2%10,22);

    find_month_name(month2-1,1);
    printByte(21, month_name[0]);
    printByte(20, month_name[1]);
    printByte(19, month_name[2]);

    //year2 = year2%100;
    //print_small_num(year2/10,17);
    //print_small_num(year2%10,16);
    printByte(18,bangla_year[0]);
    printByte(17,bangla_year[1]);
    printByte(16,bangla_year[2]);
}




int LastDayOfGregorianMonth(int month2, int year2) {
// Compute the last date of the month for the Gregorian calendar.

  switch (month2) {
  case 2:
    if ((((year2 % 4) == 0) && ((year2 % 100) != 0))
        || ((year2 % 400) == 0))
      return 29;
    else
      return 28;
  case 4:
  case 6:
  case 9:
  case 11: return 30;
  default: return 31;
  }
}



int calcAbsGregorianDays(int d, int m, int y) {
 int N = d;
 for (int i = m - 1; i > 0; i--)
  N += LastDayOfGregorianMonth(i, y);

 return N + (y - 1) * 365
    + (y - 1) / 4
    - (y - 1) / 100
    + (y - 1) / 400;
}

bool IsIslamicLeapYear(int year2) {
// True if year is an Islamic leap year

  if ((((11 * year2) + 14) % 30) < 11)
    return true;
  else
    return false;
}



int LastDayOfIslamicMonth(int month2, int year2) {
// Last day in month during year on the Islamic calendar.

  if (((month2 % 2) == 1) || ((month2 == 12) && IsIslamicLeapYear(year2)))
    return 30;
  else
    return 29;
}

const int IslamicEpoch = 227014; // Absolute date of start of Islamic calendar

int IslamicDate(int month2, int day2, int year2) {
 return (day2                      // days so far this month
            + 29 * (month2 - 1)       // days so far...
            + month2/2                //            ...this year
            + 354 * (year2 - 1)       // non-leap days in prior years
            + (3 + (11 * year2)) / 30 // leap days in prior years
            + IslamicEpoch);                // days before start of calendar
}



void GregorianToHizriMonthConverter(int d, int m, int y){
    d = calcAbsGregorianDays(d, m, y);
    int month2, day2, year2;

    // Search forward year by year from approximate year
    year2 = (d - IslamicEpoch) / 355;

    while (d >= IslamicDate(1, 1, year2))
    year2++;

    year2--;
    // Search forward month by month from Muharram
    month2 = 1;
    while (d > IslamicDate(month2, LastDayOfIslamicMonth(month2, year2), year2))
    month2++;

    day2 = d - IslamicDate(month2, 1, year2) + 1;

    printf("%d-%d-%d",day2,month2,year2);

    print_small_num(day2/10,23);
    print_small_num(day2%10,22);

    find_month_name(month2-1,2);
    printByte(21, month_name[0]);
    printByte(20, month_name[1]);
    printByte(19, month_name[2]);

    //year2 = year2%100;
    //print_small_num(year2/10,17);
    //print_small_num(year2%10,16);
    
    printByte(18,hizri_year[0]);
    printByte(17,hizri_year[1]);
    printByte(16,hizri_year[2]);
  
}



void print_small_num(uint8_t num, int a){

  switch(num){
   case 0: 
    printByte(a,shunno_small_1);
    break; 
   case 1: 
    printByte(a,ek_small_1);
    break; 
   case 2: 
    printByte(a,dui_small_1);
    break;  
   case 3: 
    printByte(a,tin_small_1);
    break; 
   case 4: 
    printByte(a,char_small_1);
    break; 
   case 5: 
    printByte(a,pach_small_1);
    break; 
   case 6: 
    printByte(a,chhoy_small_1);
    break; 
   case 7: 
    printByte(a,shaat_small_1);
    break; 
   case 8: 
    printByte(a,aat_small_1);
    break;  
   case 9: 
    printByte(a,noy_small_1);
    break;  
  }

}

void print_big_num(uint8_t num, int a, int b){

  switch(num){
   case 0: 
    print_zero(a,b);
    break; 
   case 1: 
    print_one(a,b);
    break; 
   case 2: 
    print_two(a,b);
    break;  
   case 3: 
    print_three(a,b);
    break; 
   case 4: 
    print_four(a,b);
    break; 
   case 5: 
    print_five(a,b);
    break; 
   case 6: 
    print_six(a,b);
    break; 
   case 7: 
    print_seven(a,b);
    break; 
   case 8: 
    print_eight(a,b);
    break;  
   case 9: 
    print_nine(a,b);
    break;  
  }
}


void print_right_colon_big_num(uint8_t num, int a, int b){
  switch(num){
   case 0: 
    print_right_colon_zero(a,b);
    break; 
   case 1: 
    print_right_colon_one(a,b);
    break; 
   case 2: 
    print_right_colon_two(a,b);
    break;  
   case 3: 
    print_right_colon_three(a,b);
    break; 
   case 4: 
    print_right_colon_four(a,b);
    break; 
   case 5: 
    print_right_colon_five(a,b);
    break; 
   case 6: 
    print_right_colon_six(a,b);
    break; 
   case 7: 
    print_right_colon_seven(a,b);
    break; 
   case 8: 
    print_right_colon_eight(a,b);
    break;  
   case 9: 
    print_right_colon_nine(a,b);
    break;  
  }
}




void print_left_colon_big_num(uint8_t num, int a, int b){
  switch(num){
   case 0: 
    print_left_colon_zero(a,b);
    break; 
   case 1: 
    print_left_colon_one(a,b);
    break; 
   case 2: 
    print_left_colon_two(a,b);
    break;  
   case 3: 
    print_left_colon_three(a,b);
    break; 
   case 4: 
    print_left_colon_four(a,b);
    break; 
   case 5: 
    print_left_colon_five(a,b);
    break; 
   case 6: 
    print_left_colon_six(a,b);
    break; 
   case 7: 
    print_left_colon_seven(a,b);
    break; 
   case 8: 
    print_left_colon_eight(a,b);
    break;  
   case 9: 
    print_left_colon_nine(a,b);
    break;  
  }
}




void print_zero(int a, int b){
  printByte(a,Zero_1);
  printByte(b,Zero_2);
}


void print_one(int a, int b){
  printByte(a,One_1);
  printByte(b,One_2);
}


void print_two(int a, int b){
  printByte(a,Two_1);
  printByte(b,Two_2);
}


void print_three(int a, int b){
  printByte(a,Three_1);
  printByte(b,Three_2);
}



void print_four(int a, int b){
  printByte(a,Four_1);
  printByte(b,Four_2);
}


void print_five(int a, int b){
  printByte(a,Five_1);
  printByte(b,Five_2);
}


void print_six(int a, int b){
  printByte(a,Six_1);
  printByte(b,Six_2);
}

void print_seven(int a, int b){
  printByte(a,Seven_1);
  printByte(b,Seven_2);  
}


void print_eight(int a, int b){
  printByte(a,Eight_1);
  printByte(b,Eight_2); 
}

void print_nine(int a, int b){
  printByte(a,Nine_1);
  printByte(b,Nine_2);
}



void print_right_colon_zero(int a, int b){
  printByte(a,r_Zero_1);
  printByte(b,r_Zero_2);
}


void print_right_colon_one(int a, int b){
  printByte(a,r_One_1);
  printByte(b,r_One_2);
}


void print_right_colon_two(int a, int b){
  printByte(a,r_Two_1);
  printByte(b,r_Two_2);
}


void print_right_colon_three(int a, int b){
  printByte(a,r_Three_1);
  printByte(b,r_Three_2);
}



void print_right_colon_four(int a, int b){
  printByte(a,r_Four_1);
  printByte(b,r_Four_2);
}


void print_right_colon_five(int a, int b){
  printByte(a,r_Five_1);
  printByte(b,r_Five_2);
}


void print_right_colon_six(int a, int b){
  printByte(a,r_Six_1);
  printByte(b,r_Six_2);
}

void print_right_colon_seven(int a, int b){
  printByte(a,r_Seven_1);
  printByte(b,r_Seven_2);  
}


void print_right_colon_eight(int a, int b){
  printByte(a,r_Eight_1);
  printByte(b,r_Eight_2); 
}

void print_right_colon_nine(int a, int b){
  printByte(a,r_Nine_1);
  printByte(b,r_Nine_2);
}


void print_left_colon_zero(int a, int b){
  printByte(a,l_Zero_1);
  printByte(b,l_Zero_2);
}


void print_left_colon_one(int a, int b){
  printByte(a,l_One_1);
  printByte(b,l_One_2);
}


void print_left_colon_two(int a, int b){
  printByte(a,l_Two_1);
  printByte(b,l_Two_2);
}


void print_left_colon_three(int a, int b){
  printByte(a,l_Three_1);
  printByte(b,l_Three_2);
}



void print_left_colon_four(int a, int b){
  printByte(a,l_Four_1);
  printByte(b,l_Four_2);
}


void print_left_colon_five(int a, int b){
  printByte(a,l_Five_1);
  printByte(b,l_Five_2);
}


void print_left_colon_six(int a, int b){
  printByte(a,l_Six_1);
  printByte(b,l_Six_2);
}

void print_left_colon_seven(int a, int b){
  printByte(a,l_Seven_1);
  printByte(b,l_Seven_2);  
}


void print_left_colon_eight(int a, int b){
  printByte(a,l_Eight_1);
  printByte(b,l_Eight_2); 
}

void print_left_colon_nine(int a, int b){
  printByte(a,l_Nine_1);
  printByte(b,l_Nine_2);
}



void find_prohor_name(int h){
  switch(h){
    case 20:
    case 21:
    case 22:
    case 23:
    case 0:
    case 1:
    case 2:
    case 3:
      memcpy(prohor_name, raat, sizeof(prohor_name));
      break;
    case 4:
    case 5:
      memcpy(prohor_name, usha, sizeof(prohor_name));
      break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
      memcpy(prohor_name, purbanno, sizeof(prohor_name));
      break;
    case 11:
    case 12:
    case 13:
    case 14:
      memcpy(prohor_name, modhhanno, sizeof(prohor_name));
      break;
    case 15:
    case 16:
    case 17:
      memcpy(prohor_name, Oporanno, sizeof(prohor_name));
      break;
    case 18:
    case 19:
      memcpy(prohor_name, sayanno, sizeof(prohor_name));
      break;
  }
}



void find_bar_name(int d){
  switch(d){
    case 0:
      memcpy(bar_name, robibar, sizeof(bar_name));
      break;  
    case 1:
      memcpy(bar_name, shombar, sizeof(bar_name));
      break;   
    case 2:
      memcpy(bar_name, mongol, sizeof(bar_name));
      break;  
    case 3:
      memcpy(bar_name, budhbar, sizeof(bar_name));
      break; 
    case 4:
      memcpy(bar_name, briho, sizeof(bar_name));
      break;  
    case 5:
      memcpy(bar_name, shukro, sizeof(bar_name));
      break;  
    case 6:
      memcpy(bar_name, shonibar, sizeof(bar_name));
      break;    
  }
}

void printByte(int n, byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(n,i,character[i]);
  }
}
