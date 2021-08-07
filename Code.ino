//Robotarm styrd med joysticks via arduino.
//All kod skriven av Benjamin Dervisevic, elev, Sollefteå Gymnasium

#include <Servo.h>

Servo bas;
Servo axel;
Servo armbage;
Servo klo;

const int knapp = 2;  //Blåa reset knappen
const int vSwitch = 7;  //Vänstra joystick knappen
const int hSwitch = 8;  // Högra joystick knappen

int vansterX, vansterY, hogerX, hogerY; //Joystick-axlar

//Startvärde på vinklar
int vinkel1 = 90;
int vinkel2 = 90;
int vinkel3 = 90;
int vinkel4 = 90;

const int mitten = 511; // mitten värdet på spakarna, d.v.s värdet när dem inte används
const int offset = 50; // De första 50 värdena i mitten av spakarna kommer inte påverka motorerna

void setup() {
  //Serial.begin(115200); används för debug som förekommer nedan
  pinMode(knapp, INPUT);
  pinMode(vSwitch, INPUT_PULLUP);
  pinMode(hSwitch, INPUT_PULLUP);
  bas.attach(3);
  axel.attach(5);
  armbage.attach(6);
  klo.attach(9);
}

void loop() {
  // Läs av joystick värden och tilldela till rätt axel för varsin joystick
  vansterX = analogRead(A1);
  vansterY = analogRead(A0);
  hogerX = analogRead(A3);
  hogerY = analogRead(A2);

  //Styr rotationen av basen
  if (vansterX > mitten + offset) {
    vinkel1++;
    bas.write(vinkel1);
    delay(10);
  }
  else if (vansterX < mitten - offset) {
    vinkel1--;
    bas.write(vinkel1);
    delay(10);
  }

  //Styr rotationen av axeln
  if (hogerY > mitten + offset) {
    vinkel2--;
    if (vinkel2 < 15) vinkel2 = 15; //Motorn får gå som lägst till 15 graders rotation
    axel.write(vinkel2);
    delay(10);
  }
  else if (hogerY < mitten - offset) {
    vinkel2++;
    if (vinkel2 > 160) vinkel2 = 160; //Motorn får röra sig högst fram till 160 grader
    axel.write(vinkel2);
    delay(10);
  }

  //Styr rotationen av armbågen
  if (vansterY > mitten + offset) {
    vinkel3--;
    if (vinkel3 < 10) vinkel3 = 10;
    armbage.write(vinkel3);
    delay(10);
  }
  else if (vansterY < mitten - offset) {
    vinkel3++;
    if (vinkel3 > 135) vinkel3 = 135;
    armbage.write(vinkel3);
    delay(10);
  }

  //Styr greppet
  if (hogerX > mitten + offset) {
    vinkel4++;
    if (vinkel4 > 170) vinkel4 = 170;
    klo.write(vinkel4);
    delay(10);
  }
  else if (hogerX < mitten - offset) {
    vinkel4--;
    if (vinkel4 < 115) vinkel4 = 115;
    klo.write(vinkel4);
    delay(10);
  }

  //Kollar ifall man trycker på knappen, och sätter olika värden på motorerna som ska motsvara en utgångspunkt
  // "Reset knapp"
  if (digitalRead(knapp) == HIGH) {
    if (vinkel1 > 90) {
      for (int n = vinkel1; n > 90; n--) {
        vinkel1 = n;
        bas.write(vinkel1);
        delay(10);
      }
      delay(100);
    }
    else if (vinkel1 < 90) {
      for (int n = vinkel1; n < 90; n++) {
        vinkel1 = n;
        bas.write(vinkel1);
        delay(10);
      }
      delay(100);
    }

    if (vinkel2 > 90) {
      for (int n = vinkel2; n > 90; n--) {
        vinkel2 = n;
        axel.write(vinkel2);
        delay(10);
      }
      delay(100);
    }
    else if (vinkel2 < 90) {
      for (int n = vinkel2; n < 90; n++) {
        vinkel2 = n;
        axel.write(vinkel2);
        delay(10);
      }
      delay(100);
    }

    if (vinkel3 > 90) {
      for (int n = vinkel3; n > 90; n--) {
        vinkel3 = n;
        armbage.write(vinkel3);
        delay(10);
      }
      delay(100);
    }
    else if (vinkel3 < 90) {
      for (int n = vinkel3; n < 90; n++) {
        vinkel3 = n;
        armbage.write(vinkel3);
        delay(10);
      }
      delay(100);
    }

    if (vinkel4 > 170) {
      for (int n = vinkel4; n > 170; n--) {
        vinkel4 = n;
        klo.write(vinkel4);
        delay(10);
      }
      delay(100);
    }
    else if (vinkel4 < 170) {
      for (int n = vinkel4; n < 170; n++) {
        vinkel4 = n;
        klo.write(vinkel4);
        delay(10);
      }
      delay(100);
    }
  }
  
  //Joystick knapparna används även för att styra klon
  if (digitalRead(vSwitch) == LOW) {
    vinkel4 = 170;
    klo.write(vinkel4);
  }
  if (digitalRead(hSwitch) == LOW) {
    vinkel4 = 115;
    klo.write(vinkel4);
  }


// DEBUG som användes för att hitta gränsvärden, kan orsaka märkvärdig störning
/*
  Serial.println("----------------------");
  Serial.println(vinkel1);
  Serial.println(vinkel2);
  Serial.println(vinkel3);
  Serial.println(vinkel4);
  Serial.println("----------------------");
*/
}
