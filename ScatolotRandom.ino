/*
		 */
		/*
		pin layout
		0 tx
		1 rx
		2
		3
		4
		5
		6
		7 left motor direction pin
		8 right motor direction pin
		9 left motor pwm pin
		10 right motor pwm pin
		11
		12
		13
		A0
		A1
		A2
		A3
		A4
		A5
		The program requires that the RN42 bluetooth chip has the Tx pin linked to the 2 pin and the Rx pin linked to the 4 pin
		 */
		const int LEFT_MOTOR_DIR_PIN = 7;
		const int LEFT_MOTOR_PWM_PIN = 9;
		const int RIGHT_MOTOR_DIR_PIN = 8;
		const int RIGHT_MOTOR_PWM_PIN = 10;
		int reflex=210;
		boolean ledOn = false; //debug boolean
		boolean executing = false; //stops reading if the robot is moving to prevent long queues
		void setup()
		{
			delay(2000);

			digitalWrite(13,HIGH);
			delay(400); // Short delay, wait for the Mate to send back CMD
			digitalWrite(13,LOW);
			pinMode(7, OUTPUT); //Initiates left Motor dir pin
			pinMode(9, OUTPUT); //Initiates left Motor pwm pin
			pinMode(8, OUTPUT); //Initiates right Motor dir pin
			pinMode(10, OUTPUT); //Initiates right Motor pwm pin
			randomSeed(analogRead(0));
		}
		void loop()
		{
			int randDir = random(5);
			int randTime = random(100,500);
			if(randDir == 0){
				steersx(randTime);
			}
			else if(randDir == 1){
				forward(randTime);
			}
			else if(randDir == 2){
				backward(randTime); 
			}
			else if(randDir == 3){
				steerdx(randTime);
			}  
			else if(randDir == 4){
				delay(randTime);
			}  
		}
		void forward(int time){
			executing = true;
			digitalWrite(LEFT_MOTOR_DIR_PIN, HIGH); //Establishes forward direction of Channel A
			digitalWrite(RIGHT_MOTOR_DIR_PIN, HIGH); //Establishes forward direction of Channel B
			analogWrite(LEFT_MOTOR_PWM_PIN,255);//pwmA
			analogWrite(RIGHT_MOTOR_PWM_PIN,255);//pwmB
			delay(time);
			executing=false;
			analogWrite(LEFT_MOTOR_PWM_PIN, 0); // Brake for Channel A
			analogWrite(RIGHT_MOTOR_PWM_PIN, 0); // Brake for Channel B
		}
		void forward(int time, int intensity){
			executing = true;
			digitalWrite(LEFT_MOTOR_DIR_PIN, HIGH); //Establishes forward direction of Channel A
			digitalWrite(RIGHT_MOTOR_DIR_PIN, HIGH); //Establishes forward direction of Channel B
			analogWrite(LEFT_MOTOR_PWM_PIN, intensity);//pwmA
			analogWrite(RIGHT_MOTOR_PWM_PIN,intensity);//pwmB
			delay(time);
			executing=false;
			digitalWrite(LEFT_MOTOR_PWM_PIN, 0);
			digitalWrite(RIGHT_MOTOR_PWM_PIN, 0);
		}
		void backward(int time){
			executing = true;
			digitalWrite(LEFT_MOTOR_DIR_PIN, LOW); //Establishes forward direction of Channel A
			digitalWrite(RIGHT_MOTOR_DIR_PIN, LOW); //Establishes forward direction of Channel B
			analogWrite(LEFT_MOTOR_PWM_PIN,255);//pwmA
			analogWrite(RIGHT_MOTOR_PWM_PIN,255);//pwmB
			delay(time);
			executing=false;
			analogWrite(LEFT_MOTOR_PWM_PIN, 0); // Brake for Channel A
			analogWrite(RIGHT_MOTOR_PWM_PIN, 0); // Brake for Channel B
		}
		void backward(int time, int intensity){
			executing = true;
			digitalWrite(LEFT_MOTOR_DIR_PIN, LOW); //Establishes forward direction of Channel A
			digitalWrite(RIGHT_MOTOR_DIR_PIN, LOW); //Establishes forward direction of Channel B
			analogWrite(LEFT_MOTOR_PWM_PIN, intensity);//pwmA
			analogWrite(RIGHT_MOTOR_PWM_PIN,intensity);//pwmB
			delay(time);
			executing=false;
			digitalWrite(LEFT_MOTOR_PWM_PIN, 0);
			digitalWrite(RIGHT_MOTOR_PWM_PIN, 0);
		}
		void steersx(int time){
			executing = true;
			digitalWrite(LEFT_MOTOR_DIR_PIN, LOW); //Establishes forward direction of Channel A
			digitalWrite(RIGHT_MOTOR_DIR_PIN, HIGH); //Establishes forward direction of Channel B
			analogWrite(LEFT_MOTOR_PWM_PIN, 128);//pwmA
			analogWrite(RIGHT_MOTOR_PWM_PIN,128);//pwmB
			delay(time);
			executing=false;
			digitalWrite(LEFT_MOTOR_PWM_PIN, 0);
			digitalWrite(RIGHT_MOTOR_PWM_PIN, 0);
		}
		void steerdx(int time){
			executing = true;
			digitalWrite(LEFT_MOTOR_DIR_PIN, HIGH); //Establishes forward direction of Channel A
			digitalWrite(RIGHT_MOTOR_DIR_PIN, LOW); //Establishes forward direction of Channel B
			analogWrite(LEFT_MOTOR_PWM_PIN, 128);//pwmA
			analogWrite(RIGHT_MOTOR_PWM_PIN,128);//pwmB
			delay(time);
			executing=false;
			digitalWrite(LEFT_MOTOR_PWM_PIN, 0);
			digitalWrite(RIGHT_MOTOR_PWM_PIN, 0);
		} 
