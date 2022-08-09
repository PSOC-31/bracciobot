/*
 BraccioBot.cpp - board library Version 2.0
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

#include "BraccioBot.h"



extern int step_base = 0;
extern int step_shoulder = 45;
extern int step_elbow = 180;
extern int step_wrist_rot = 180;
extern int step_wrist_ver = 90;
extern int step_gripper = 10;
 

//BraccioBot BraccioBot;

//Initialize BraccioBot object
BraccioBot::BraccioBot() {
}

/**
 * BraccioBot initialization and set intial position
 * Modifing this function you can set up the initial position of all the
 * servo motors of BraccioBot
 * @param soft_start_level: default value is 0 (SOFT_START_DEFAULT)
 * You should set begin(SOFT_START_DISABLED) if you are using the Arm Robot shield V1.6
 * SOFT_START_DISABLED disable the BraccioBot movements
 */
unsigned int BraccioBot::initialisation() {
	int soft_start_level=0;
	//Calling BraccioBot.begin(SOFT_START_DISABLED) the Softstart is disabled and you can use the pin 12
	if(soft_start_level!=SOFT_START_DISABLED){
		pinMode(SOFT_START_CONTROL_PIN,OUTPUT);
		digitalWrite(SOFT_START_CONTROL_PIN,LOW);
	}

	// initialization pin Servo motors
	base.attach(11);
	shoulder.attach(10);
	elbow.attach(9);
	wrist_rot.attach(5);
	wrist_ver.attach(6);
	gripper.attach(3);
        
	//For each step motor this set up the initial degree
	base.write(0);
	shoulder.write(40);
	elbow.write(180);
	wrist_ver.write(170);
	wrist_rot.write(0);
	gripper.write(73);
	//Previous step motor position
	step_base = 0;
	step_shoulder = 40;
	step_elbow = 180;
	step_wrist_ver = 170;
	step_wrist_rot = 0;
	step_gripper = 73;
Serial.begin(250000);
	if(soft_start_level!=SOFT_START_DISABLED)
    		_softStart(soft_start_level);
	return 1;
}

/*
Software implementation of the PWM for the SOFT_START_CONTROL_PIN,HIGH
@param high_time: the time in the logic level high
@param low_time: the time in the logic level low
*/
void BraccioBot::_softwarePWM(int high_time, int low_time){
	digitalWrite(SOFT_START_CONTROL_PIN,HIGH);
	delayMicroseconds(high_time);
	digitalWrite(SOFT_START_CONTROL_PIN,LOW);
	delayMicroseconds(low_time); 
}

/*
* This function, used only with the BraccioBot Shield V4 and greater,
* turn ON the BraccioBot softly and save it from brokes.
* The SOFT_START_CONTROL_PIN is used as a software PWM
* @param soft_start_level: the minimum value is -70, default value is 0 (SOFT_START_DEFAULT)
*/
void BraccioBot::_softStart(int soft_start_level){      
	long int tmp=millis();
	while(millis()-tmp < LOW_LIMIT_TIMEOUT)
		_softwarePWM(80+soft_start_level, 450 - soft_start_level);   //the sum should be 530usec	

	while(millis()-tmp < HIGH_LIMIT_TIMEOUT)
		_softwarePWM(75 + soft_start_level, 430 - soft_start_level); //the sum should be 505usec

	digitalWrite(SOFT_START_CONTROL_PIN,HIGH);
}

/**
 * This functions allow you to control all the servo motors
 * 
 * @param stepDelay The delay between each servo movement
 * @param vBase next base servo motor degree
 * @param vShoulder next shoulder servo motor degree
 * @param vElbow next elbow servo motor degree
 * @param vWrist_ver next wrist rotation servo motor degree
 * @param vWrist_rot next wrist vertical servo motor degree
 * @param vgripper next gripper servo motor degree
 */
void BraccioBot::deplacer(int stepDelay, int vBase, int vShoulder, int vElbow,int vWrist_ver, int vWrist_rot, int vgripper) {

	// Check values, to avoid dangerous positions for the BraccioBot
    	if (stepDelay > 30) stepDelay = 30;
	if (stepDelay < 10) stepDelay = 10;
	if (vBase < 0) vBase=0;
	if (vBase > 180) vBase=180;
	if (vShoulder < 15) vShoulder=15;
	if (vShoulder > 165) vShoulder=165;
	if (vElbow < 0) vElbow=0;
	if (vElbow > 180) vElbow=180;
	if (vWrist_ver < 0) vWrist_ver=0;
	if (vWrist_ver > 180) vWrist_ver=180;
	if (vWrist_rot > 180) vWrist_rot=180;
	if (vWrist_rot < 0) vWrist_rot=0;
    	if (vgripper < 10) vgripper = 10;
	if (vgripper > 73) vgripper = 73;

	int exit = 1;
Serial.println("********");
Serial.print(vBase);
Serial.print("/");	
Serial.print(step_base);
Serial.print("\t\t");	
	
Serial.print(vShoulder);
Serial.print("/");	
Serial.print(step_shoulder);
Serial.print("\t\t");	
	
Serial.print(vElbow);
Serial.print("/");	
Serial.print(step_elbow);
Serial.print("\t\t");	

Serial.print(vWrist_rot);
Serial.print("/");	
Serial.print(step_wrist_rot);
Serial.print("\t\t");	

Serial.print(vWrist_ver);
Serial.print("/");	
Serial.print(step_wrist_ver);
Serial.print("\t\t");	

Serial.print(vgripper);
Serial.print("/");	
Serial.print(step_gripper);
Serial.print("\n");	
	//Until the all motors are in the desired position
	while (exit) 
	{



		//For each servo motor if next degree is not the same of the previuos than do the movement		
		if (vBase != step_base) 
		{			
			base.write(step_base);
			//One step ahead
			if (vBase > step_base) {
				step_base++;
			}
			//One step beyond
			if (vBase < step_base) {
				step_base--;
			}
		}

		if (vShoulder != step_shoulder)  
		{
			shoulder.write(step_shoulder);
			//One step ahead
			if (vShoulder > step_shoulder) {
				step_shoulder++;
			}
			//One step beyond
			if (vShoulder < step_shoulder) {
				step_shoulder--;
			}

		}

		if (vElbow != step_elbow)  
		{
			elbow.write(step_elbow);
			//One step ahead
			if (vElbow > step_elbow) {
				step_elbow++;
			}
			//One step beyond
			if (vElbow < step_elbow) {
				step_elbow--;
			}

		}

		if (vWrist_rot != step_wrist_rot) 
		{
			wrist_rot.write(step_wrist_rot);
			//One step ahead
			if (vWrist_rot > step_wrist_rot) {
				step_wrist_rot++;				
			}
			//One step beyond
			if (vWrist_rot < step_wrist_rot) {
				step_wrist_rot--;
			}

		}

		if (vWrist_ver != step_wrist_ver)
		{
			wrist_ver.write(step_wrist_ver);
			//One step ahead
			if (vWrist_ver > step_wrist_ver) {
				step_wrist_ver++;
			}
			//One step beyond
			if (vWrist_ver < step_wrist_ver) {
				step_wrist_ver--;
			}
		}

		if (vgripper != step_gripper)
		{
			gripper.write(step_gripper);
			if (vgripper > step_gripper) {
				step_gripper++;
			}
			//One step beyond
			if (vgripper < step_gripper) {
				step_gripper--;
			}
		}
		
		//delay between each movement
		delay(stepDelay);
	
		//It checks if all the servo motors are in the desired position 
		if ((vBase == step_base) && (vShoulder == step_shoulder)
				&& (vElbow == step_elbow) && (vWrist_ver == step_wrist_ver)
				&& (vWrist_rot == step_wrist_rot) && (vgripper == step_gripper)) {
			step_base = vBase;
			step_shoulder = vShoulder;
			step_elbow = vElbow;
			step_wrist_rot = vWrist_rot;
				step_wrist_ver = vWrist_ver;
			step_gripper = vgripper;
			exit = 0;
		} else {
			exit = 1;
		}
	}
}


  void BraccioBot::rotationBase(int delay, int Vbase)
  {
deplacer(delay,  Vbase,  step_shoulder,  step_elbow, step_wrist_ver,  step_wrist_rot,  step_gripper);
  }	  
  void BraccioBot::rotationEpaule(int delay, int Vshoulder)
  {
deplacer(delay,  step_base,  Vshoulder,  step_elbow, step_wrist_ver,  step_wrist_rot,  step_gripper);
  }	  
  
  void BraccioBot::rotationcoude(int delay,  int Velbow)
    {
deplacer(delay,  step_base,  step_shoulder,  Velbow, step_wrist_ver,  step_wrist_rot,  step_gripper);
  }	  

  void BraccioBot::rotationpoignet(int delay, int Vwrist_ver)
    {
deplacer(delay,  step_base,  step_shoulder,  step_elbow, Vwrist_ver,  step_wrist_rot,  step_gripper);
  }	  

  void BraccioBot::rotationPince(int delay, int Vwrist_rot)
    {
deplacer(delay,  step_base,  step_shoulder,  step_elbow, step_wrist_ver,  Vwrist_rot,  step_gripper);
  }	  

  void BraccioBot::ouvrirPince()
  {
deplacer(delayStep,  step_base,  step_shoulder,  step_elbow, step_wrist_ver,  step_wrist_rot,  10);
  }	  
  
  void BraccioBot::fermerPince()
   {
deplacer(delayStep,  step_base,  step_shoulder,  step_elbow, step_wrist_ver,  step_wrist_rot,  73);
  }	  

  //@mouvements basiques
void BraccioBot::lever()
{
		deplacer(delayStep,step_base, 45,180,135, 90, step_gripper);

}

void BraccioBot::baisser()
{
	deplacer(delayStep,step_base, 135,180,45, 90,  step_gripper);

}

void BraccioBot::rotationGauche()
{
deplacer(delayStep,  10,  step_shoulder,  step_elbow, step_wrist_ver,  90,  step_gripper);
}

void BraccioBot::rotationDroite()
{
deplacer(delayStep,  170,  step_shoulder,  step_elbow, step_wrist_ver,  90,  step_gripper);

}
void BraccioBot::rotationCentre()
{
deplacer(delayStep,  90,  step_shoulder,  step_elbow, step_wrist_ver,  step_wrist_rot,  step_gripper);

}
void BraccioBot::inclinerHaut()	{	
deplacer(delayStep,  step_base,  step_shoulder,  step_elbow, 0,  step_wrist_rot,  step_gripper);

}

void BraccioBot::inclinerBas()	{
	deplacer(delayStep,  step_base,  step_shoulder,  step_elbow, 180,  step_wrist_rot,  step_gripper);

}

void BraccioBot::horizontal()
{
	int vv=0;
	if (step_shoulder+step_elbow<179)
	vv=179-step_shoulder-step_elbow;
else
	vv=360-step_shoulder-step_elbow;
deplacer(delayStep,  step_base,  step_shoulder,  step_elbow, vv,  step_wrist_rot,  step_gripper);


}




