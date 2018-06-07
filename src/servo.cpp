#ifndef SERVO_H
#include <servo.h>
#endif

ServoLoop::ServoLoop(int pgain, int dgain)
{
  m_pos = SERVO_CENTER_POS;
  m_pgain = pgain;
  m_dgain = dgain;
  m_prevError = 0x80000000L;
}

void ServoLoop::update(int error)
{
  long int vel;
  if (m_prevError!=0x80000000)
  {
    vel = (error*m_pgain + (error-m_prevError)*m_dgain)>>10;
    m_pos+=vel;
    if (m_pos>SERVO_MAX_POS)
      m_pos = SERVO_MAX_POS;
    else if (m_pos<SERVO_MIN_POS)
      m_pos = SERVO_MIN_POS;
  }
  m_prevError = error;
}

void ServoLoop::moveServo(int channel, int position, int time=0, int speed=0 )
{
  char buf[64];
  if (speed && position)
    sprintf(buf,"#%dP%dS%dT%d",channel,position,speed,time);
  else if (speed)
    sprintf(buf,"#%dP%dS%d",channel,position,speed);
  else if (time)
  {
    sprintf(buf,"#%dP%dT%d",channel,position,time);
    delay(time);
  }
  else
    sprintf(buf,"#%dP%d",channel,position);
  Bot.println(buf);
  Serial.println(buf);
}
