#include <Arduino.h>
int period = 35;    //30ml=1050 1ml=35  //35*40=37 1:1 37.8
int pcounter=10;     //protective counter
int settime=40;
const int stationno=5;
//const int relayperstation=6;
const int relayperstation=2;
int bottle=50;
//source  pinNumber do not use pin0 start from pin2
int Vodka = 2;
int Cointreau = 3;
int CranberryJuice = 4;
int Sprite = 5;
int LemonJuice = 6;
int SugarWater = 7;
int BlueCur = 8;
int Gin = 9;

//manuM
String manu[]={"0","VodkaSprite","BlueLagoon","Cosmo","Lemondrop","Bluemoon","BlueGinMoon"}; //last 2 need to test on mega
int manurecipe[][20]={    //recipe {name,volume,name,volume}
  
  {0},
  //{Vodka,15,Cointreau,30},   //"VodkaSprite" //2+3 sta 0+0
  {Vodka,20,Cointreau,35,5,35},   //"BlueLagoon"  //2+8 sta 0+1
  {Vodka,15,Cointreau,30},   //"Cosmo"
  {Vodka,15,Cointreau,30},   //"Lemondrop"
  {Vodka,15,Cointreau,30},   //"BlueMoon"
  {Vodka,15,Cointreau,30}    //"BlueGinMoon"
  };


//station 
int station[stationno][relayperstation]={
/**
  {Vodka, Cointreau,4,5,6,7},//2,3 //drink at station 0
  {8,9,10,11,12,13},                    //drink at station 1 //13should deplug before upload
  {14,15,16,17,18,19},                   //drink at station 2
  {20,21,22,23,24,25},                 //drink at station 3
  {26,27,28,29,30,31}                     //drink at station 4
**/
  {Vodka, Cointreau},//2,3 //drink at station 0
  {4,5},                    //drink at station 1 //13should deplug before upload
  {6,7},                   //drink at station 2
  {8,9},                 //drink at station 3
  {10,11}                     //drink at station 4

  };
  
