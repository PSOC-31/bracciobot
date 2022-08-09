/*
  BraccioBot.h - board library Version 2.0
  Written by Andrea Martino and Angelo Ferrante

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef BRACCIOBOT_H_
#define BRACCIOBOT_H_

#include <Arduino.h>
#include <Servo.h>

// You should set begin(SOFT_START_DISABLED) if you are using the Arm Robot shield V1.6
#define SOFT_START_DISABLED		-999


//The default value for the soft start
#define SOFT_START_DEFAULT		0

//The software PWM is connected to PIN 12. You cannot use the pin 12 if you are using
//a BraccioBot shield V4 or newer
#define SOFT_START_CONTROL_PIN	12

//Low and High Limit Timeout for the Software PWM
#define LOW_LIMIT_TIMEOUT 2000
#define HIGH_LIMIT_TIMEOUT 6000

class BraccioBot {

public:

//@braccioBot - initialisation
//@bloc texte=nouveau bras png=init.png
  BraccioBot();
  
  //@bloc texte=activer les moteurs png=on.png
  unsigned int initialisation(); 
  
  //@bloc texte=entre 10 et 50
  
int delayStep = 20;
  
  //@mouvements basiques
//@bloc texte=lever le bras png=lever.png
void lever();
//@bloc texte=baisser le bras png=baisser.png
void baisser();
//@bloc texte=tourner à gauche png=tournegauche.png
void rotationGauche();
//@bloc texte=tourner à droite png=tournedroite.png
void rotationDroite();
//@bloc texte=tourner à droite png=tournecentre.png
void rotationCentre();

//@pince

//@bloc texte=ouvrir la pince png=pinceouverte.png
void ouvrirPince();
//@bloc texte=fermer la pince png=pincefermee.png
void fermerPince();
//@bloc texte=lever la pince png=pincehaut.png
void inclinerHaut();
//@bloc texte=baisser l apince png=pincebas.png
void inclinerBas();
//@bloc texte=pince à l'horizontal png=pinceplat.png
void horizontal();


  
//@bras - Articulations  
  //@bloc texte=tous les angles png=tous.png
  void deplacer(int delay, int base,int epaule, int coude, int poignetV, int poignetR, int pince); 
//@bloc texte=angle de la base png=anglebase.png
  void rotationBase(int delay, int base); 
  //@bloc texte=angle des épaules png=angleepaule.png
  void rotationEpaule(int delay, int epaule); 
//@bloc texte=angle du coude png=anglecoude.png
  void rotationcoude(int delay,  int coude); 
  //@bloc texte=angle du poignet png=anglepoignet.png
  void rotationpoignet(int delay, int poignetV); 
  //@bloc texte=angle de la pince png=rotationpince.png
  void rotationPince(int delay, int poignetR); 




private:
 Servo base;
 Servo shoulder;
 Servo elbow;
 Servo wrist_rot;
 Servo wrist_ver;
 Servo gripper;
  void _softStart(int soft_start_level);
	
  void _softwarePWM(int high_time, int low_time);


};


#endif // BraccioBot_H_
