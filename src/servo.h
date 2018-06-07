/**
* @file C:\Users\Angelo Manganiello\Documents\PlatformIO\Projects\FindBall\src\servo.h
* @author Angelo Manganiello
* @date 4 Jun 2018
* @copyright 2018 Angelo Manganiello
* @brief Questo file contiene le funzioni per la gestione dei servo motori di
* Johnny 5
*/


#ifndef SERVO_H
#define SERVO_H

#include <SPI.h>

#define Bot                 Serial1
#define BASE_ROTATE         0   /*!< canale del motore della base */
#define LOWER_BACK          1   /*!< canale del motore del torso inferiore */
#define UPPER_BACK          2   /*!< canale del motore del torso superiore */
#define L_SHOULDER          3   /*!< canale del motore della spalla sinistra */
#define L_UPPER_ELBOW       4   /*!< canale del motore del gomito superiore sinistro */
#define L_LOWER_ELBOW       5   /*!< canale del motore del gomito inferiore sinistro */
#define L_FINGERS           6   /*!< canale del motore delle dita della mano sinistra */
#define L_THUMB             7   /*!< canale del motore del polso della mano sinistra */
#define R_SHOULDER          8   /*!< canale del motore della spalla destra */
#define R_UPPER_ELBOW       9   /*!< canale del motore del gomito superiore destro */
#define R_LOWER_ELBOW       10  /*!< canale del motore del gomito inferiore destro */
#define R_FINGERS           11  /*!< canale del motore delle dita della mano destra */
#define R_THUMB             12  /*!< canale del motore dek polso della mano destra */
#define NECK                13  /*!< canale del motore del collo */
#define R_TRACK             14  /*!< canale del motore del cingolo destro */
#define L_TRACK             15  /*!< canale del motore del cingolo sinistro */

#define SERVO_MIN_POS       500L   /*!< valore minimo di posizione del servo motore */
#define SERVO_MAX_POS       2500L  /*!< valore massimo di posizione del servo motore */
#define SERVO_CENTER_POS    1500L /*!< valore centrale di posizione del srvo motore */

/**
 * Modella un generico servo motore
 * @method ServoLoop
 * @param  pgain     valore del guadagno proporzionale sull'errore di posizione
 * @param  dgain     valore del guadagno differenziale sull'errore di posizione
 */
class ServoLoop
{
public:
  ServoLoop(int pgain,int dgain);

  /**
   * Calcola la nuova posizione del motore in funzione dell'errore di posizione.
   * @method update
   * @param  error  differenza tra il valore della posizione di riferimento
   * ed il valore misurato
   */
  void update(int error);
  /**
   * Muove il servo motore nella posizione specificata
   * @method moveServo
   * @param  channel   numero del canale a cui è collegato il motore
   * @param  position  la posizione in cui si vuole portare il motore
   * @param  speed     velocità con cui muovere il motore
   * @param  time      tempo che il motore impiegherà a portarsi in quella posizione
   */
  static void moveServo(int channel, int position, int time=0, int speed=0);

  int m_pos;              /*!< posizione in cui si trova il motore */
  int m_prevError;        /*!< valore dell'errore nell'istante precedente */
  int m_pgain;            /*!< guadagno proporzionale */
  int m_dgain;            /*!< gudagno derivativo */
};

#endif
