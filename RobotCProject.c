#pragma config(Sensor, S2,     gyroSensor,     sensorEV3_Gyro)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

float absVal(float n)
{
	if(n < 0)
	{
		return n * -1;
	}
	return n;
}

void turnLeft()
{
	resetGyro(gyroSensor);
	float kF = 10;
	float kP = 1;
	float threshold = 1;
	float error = 0;
	float powers = 0; //Max can be 100
	float endAngle = -90; //90 degrees to the left
	while(absVal(getGyroHeading(gyroSensor)-(endAngle))>threshold)
	{
		error = getGyroHeading(gyroSensor)-(endAngle);
		powers = error * kP + kF * error/absVal(error); //kF is applied in the unit vector direction of the error
		if(absVal(powers) > 100) // scale the power to be in the range of a 100 to -100
		{
			powers = 100*powers/abs(powers);
		}
		setMotorSpeed(leftMotor, -powers);
		setMotorSpeed(rightMotor, powers);
	}
}

void forwardMove()
{
	moveMotorTarget(leftMotor, 500,100);
	moveMotorTarget(rightMotor, 500,100);
	waitUntilMotorStop(leftMotor);
	waitUntilMotorStop(rightMotor);
}

task main()
{ //Move in a box
	/*
	forward
	left turn
	forward
	left turn
	forward
	left turn
	forward
	*/
	resetGyro(gyroSensor);

	forwardMove();
	turnLeft();
	forwardMove();
	turnLeft();
	forwardMove();
	turnLeft();
	forwardMove();
}