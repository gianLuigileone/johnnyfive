#include <Pixy.h>
#ifndef SERVO_H
#include <servo.h>
#endif

#define X_CENTER        ((PIXY_MAX_X-PIXY_MIN_X)/2)
#define Y_CENTER        ((PIXY_MAX_Y-PIXY_MIN_Y)/2)

Pixy camera;
bool trovato;
uint16_t blocks;
int pos = 1500;
int ypos = 1500;
bool centrato = false;

void initialPosition(int time=0)
{
  ServoLoop::moveServo(BASE_ROTATE, SERVO_CENTER_POS,time);
  ServoLoop::moveServo(LOWER_BACK, SERVO_CENTER_POS,time);
  ServoLoop::moveServo(UPPER_BACK, SERVO_CENTER_POS,time);
  ServoLoop::moveServo(L_SHOULDER, SERVO_CENTER_POS,time);
  ServoLoop::moveServo(L_UPPER_ELBOW, SERVO_CENTER_POS,time);
  ServoLoop::moveServo(L_LOWER_ELBOW, SERVO_CENTER_POS,time);
  ServoLoop::moveServo(L_FINGERS, SERVO_CENTER_POS,time);
  ServoLoop::moveServo(L_THUMB, SERVO_CENTER_POS,time);
  ServoLoop::moveServo(R_SHOULDER, SERVO_CENTER_POS,time);
  ServoLoop::moveServo(R_UPPER_ELBOW, SERVO_CENTER_POS,time);
  ServoLoop::moveServo(R_LOWER_ELBOW, SERVO_CENTER_POS,time);
  ServoLoop::moveServo(R_FINGERS, SERVO_CENTER_POS,time);
  ServoLoop::moveServo(R_THUMB, SERVO_CENTER_POS,time);
  ServoLoop::moveServo(NECK, SERVO_CENTER_POS,time);
}

void afferraOggetto()
{
  ServoLoop::moveServo(L_SHOULDER, SERVO_CENTER_POS,1000);
  ServoLoop::moveServo(L_UPPER_ELBOW, 600,1000);
  ServoLoop::moveServo(L_LOWER_ELBOW, 1500,1000);
  ServoLoop::moveServo(L_FINGERS, 900,1000);
  ServoLoop::moveServo(L_THUMB, 800,1000);
  ServoLoop::moveServo(BASE_ROTATE, 1925,1000);
  ServoLoop::moveServo(L_THUMB, 2000,1000);
}

void osserva()
{
  int t;
  for(int tilt=1500;tilt>1000;tilt-=500)
  {
    t=4000;
    for(int pan=700;pan<2300;pan+=400)
    {
      ServoLoop::moveServo(BASE_ROTATE,pan,t);
      ServoLoop::moveServo(LOWER_BACK,tilt,500);
      t=500;
      blocks = camera.getBlocks(1);
      if (blocks && !trovato)
      {
        afferraOggetto();
        trovato=true;
        return;
      }
    }
  }
}


void setup() {
    Serial.begin(9600);
    Bot.begin(9600);
    camera.init();
    delay(100);
    // Initial position
    initialPosition(1000);
  }

void loop() {

    blocks = camera.getBlocks(1);

    if (blocks) {
      int pan = camera.blocks[0].x;
      int tilt = camera.blocks[0].y;
      if (!centrato)
      {
      if (pan>160)
      {
        do
        {
          pos++;
          if (pos>=SERVO_MAX_POS)
          {
            pos = SERVO_MAX_POS;
            break;
          }
          ServoLoop::moveServo(BASE_ROTATE, pos);
          blocks = camera.getBlocks(1);
          Serial.println(pos);
        } while(camera.blocks[0].x > 160);
      }
      else if (pan<160)
       {
        do {
            pos--;
            if (pos==SERVO_MIN_POS){
              pos = SERVO_MIN_POS;
              break;
            }
            ServoLoop::moveServo(BASE_ROTATE, pos);
            blocks = camera.getBlocks(1);
            Serial.println(pos);
        } while(camera.blocks[0].x < 160);
      }
      if (tilt>100)
      {
        do
        {
          ypos--;
          if (ypos==SERVO_MIN_POS)
          {
            ypos = SERVO_MIN_POS;
            break;
          }
          ServoLoop::moveServo(LOWER_BACK, ypos);
          blocks = camera.getBlocks(1);
          Serial.println(ypos);
        } while(camera.blocks[0].y >= 100);
      } else if (pan<100) {
        do {
            ypos++;
            if (ypos==SERVO_MAX_POS){
              ypos = SERVO_MAX_POS;
              break;
            }
            ServoLoop::moveServo(LOWER_BACK, ypos);
            blocks = camera.getBlocks(1);
            Serial.println(ypos);
        } while(camera.blocks[0].y <= 100);
      }
        if ((camera.blocks[0].x>150) && (camera.blocks[0].x<170))
          if ((camera.blocks[0].y>95) && (camera.blocks[0].y<105)){
            centrato=true;
            Serial.println("Centrato");
        }
      }

      Serial.println("height:");
      Serial.println(camera.blocks[0].height);
      Serial.println("width:");
      Serial.println(camera.blocks[0].width);
    }
      if (centrato){
      delay(2000);
      afferraOggetto();
      delay(5000);
      centrato=false;
      initialPosition(500);
      }

}
