#include "recipe.h"
int conveyer[stationno*2];//5max: staion(5)+conveyer(5) for now
void start();
void set();
void cmove();

void setup() {
  Serial.begin(115200); //115200 //9600
  Serial.println("Ready");
  for(int i=0;i<sizeof(conveyer)/sizeof(conveyer[0]);i++){conveyer[i]=0;}
  for (int i=1;i<40;i++){pinMode(i, OUTPUT);}
  pinMode(A0,OUTPUT);
}
int manuflag=1;
bool singleflag=0;

void loop() {

  if (manuflag){for(int i=1;i<sizeof(manu)/sizeof(manu[0]);i++){Serial.print(manu[i]);Serial.print(" ");}Serial.println('\n');manuflag=0;}
  if(Serial.available() > 0){ 
    
      String order = Serial.readStringUntil('\n');//' instead of "
      int findflag=0;
      for (int i=0; i<sizeof(manu)/sizeof(manu[0]);i++)
      {
        if (manu[i]==order){
          findflag=1;
          for(int i=stationno;i>1;i--){conveyer[i-1]=conveyer[i-2];}
          conveyer[0]=i;
         for(int i=0;i<sizeof(conveyer)/sizeof(conveyer[0]);i++){Serial.print(manu[conveyer[i]]);Serial.print(" ");}  Serial.println(); 
         if(singleflag==1){start();manuflag=1;}
  
        }
      }

      if (order=="start"){start();findflag=1;manuflag=1;}
      if (order=="single"){Serial.println("single mode");singleflag=1;manuflag=1;findflag=1;}
      if (order=="complex"){Serial.println("complex mode");singleflag=0;manuflag=1;findflag=1;}
      if (order=="set"){set();findflag=1;manuflag=1;findflag=1;}
      if (findflag==0){Serial.println("recipe not found");manuflag=1;}      
      } 
}
//need add protection prevent more than 10 relay open
void start(){
    int startpoint=0;
    cmove();
    
    Serial.println("conveyer move");  //delay(2000); //wait until finish movement  
    for (int i=0;i<stationno*2;i++){if(conveyer[i]==0){startpoint=i;break;}}
    
    //for(int repeat=0;repeat<(stationno+startpoint);repeat++){
    for(int repeat=0;repeat<(stationno);repeat++){
      for(int z=stationno*2;z>1;z--){conveyer[z-1]=conveyer[z-2];}
      conveyer[0]=0;      
        unsigned long volume[bottle];
        memset(volume,0,sizeof(volume));       
    for (int i=startpoint;i<(stationno+startpoint);i++){
      for (int l=0;l<stationno;l++){        //l search each staion
        for (int k=0;k<relayperstation;k++){  //k search pin in station
          for (int j=0;j<20;j+=2){     // order in converyer search pin number
            for (int m=0;m<relayperstation;m++){
     if (conveyer[i]!=0 and manurecipe[conveyer[i]][j]==station[l][k] and station[l][k]==station[i-startpoint][m]){
       volume[k+2]=manurecipe[conveyer[i]][j+1];
      }
    
    }}}}}

//protective counter:prevent total pump rating >converter rating    

    int counter=0;
    int split[bottle/pcounter+2];
    memset(split,0,sizeof(split));
    int j=1;
    for(int i=0;i<bottle;i++){if(volume[i]!=0){counter++;}
     if (counter==10){split[j]=i;counter=0;j++;}
     if (i==bottle-1){split[j]=i;}
    }

    
    for (int z=0;z<sizeof(split)/sizeof(split[0])-1;z++){
     
      
      if(split[z+1]!=0){
      //convert volume to time 
    for (int i=split[z];i<split[z+1];i++){if (volume[i]!=0){volume[i]=volume[i]*period+millis();digitalWrite(i,HIGH);}}
      //relay switch here

    
  for(int j=split[z];j<split[z+1];j++){
    bool flag=0;
    if(millis() > volume[j]){
      digitalWrite(j, LOW);
      volume[j]=0;  }
    for(int k=split[z];k<split[z+1];k++){if (volume[k] !=0){flag=1;}}
    if (flag==0){Serial.println("finished");break;}
    if (j==(split[z+1]-1)){j=0;}
  
  }
    }}
  delay(1000);     
    cmove();  

  

// for (int q=0; q<bottle;q++){Serial.print(volume[q]);Serial.print(" ");}Serial.println(" ");

  }memset(conveyer,0,sizeof(conveyer));

}

void set(){
  bool flag=1;

while(1){
  if (flag){Serial.println("Number for individual bottle.");Serial.println( "a for station 0, b for station 1,etc.");Serial.println("end to escape");Serial.println();
  flag=0;}
 if(Serial.available() > 0){ 
      String command=Serial.readStringUntil('\n');

      if(command=="end"){Serial.println("Returned to main manu");break;}
      else if(isDigit(command[0])){
        bool checkflag=0;
        for (int i=0;i<sizeof(command)/sizeof(command[0]);i++){
          if(!(isDigit(command[i])||command[i]=='\0')){checkflag=1;}}
        if(checkflag==0){
          for (int j=0;j<stationno;j++){
            for(int k=0;k<relayperstation;k++){
              if(command.toInt()==station[j][k]){
                digitalWrite(station[j][k],HIGH);
                unsigned long time_now=0;
                time_now = millis();
                while(1){
                if(millis() > time_now+period*settime){
                digitalWrite(station[j][k], LOW);break;}}
                Serial.println(station[j][k]);j=stationno;checkflag=0;break; //change serial to function                 
              }else{checkflag=1;}}}}
        if(checkflag==1){Serial.println("Invalid Input!");Serial.println();flag=1;}
        }
     else if(command=="a"||"b"||"c"||"d"||"e"){//relayperstaion should less than converter rating   //may add new command in the future for extra station
        int setstation=9999;
        if (command=="a"){setstation=0;
        }else if (command=="b"){setstation=1;
        }else if (command=="c"){setstation=2;
        }else if (command=="d"){setstation=3;
        }else if (command=="e"){setstation=4;
        }else{Serial.println("Invalid Input!");Serial.println();flag=1;}
          if(setstation!=9999){
          for (int z=0;z<relayperstation;z++){
            digitalWrite(station[setstation][z],HIGH);}
            unsigned long time_now=0;
            time_now=millis();
          while(1){
              if(millis() > time_now+period*settime){
                 for (int z=0;z<relayperstation;z++){
                  digitalWrite(station[setstation][z],LOW);} Serial.print("finished set up station ");Serial.println(setstation); break;    }        }
        
        }
        }
  

      else{Serial.println("Invalid Input!");Serial.println();flag=1;}
 } 
}
}

void cmove(){
    digitalWrite(A0,HIGH);
    delay(500);
    digitalWrite(A0,LOW);    
    Serial.println("conveyer move");  //delay(2000); //wait until finish movement  
    delay(2000);
}
