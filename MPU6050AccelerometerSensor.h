// MPU6050AccelerometerSensor.h

#ifndef _MPU6050ACCELEROMETERSENSOR_h
#define _MPU6050ACCELEROMETERSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SenseNode.h"
#include "SenseI2CBusSensor.h"
#include "ISenseYawPitchRollValued.h"
#include "MPU6050.h" 


class MPU6050AccelerometerSensor : public SenseI2CBusSensor
{
public:
  MPU6050AccelerometerSensor(uint8_t sensorId, uint8_t address);
  virtual ~MPU6050AccelerometerSensor() {};

  YawPitchRollValue getlastValues();
  byte* getValueInBuffer(byte* buffer) override;
  byte getMinBufferSize() override;
  char* getValueAsChars(char* value) override;
protected:
  virtual void initialize();

  virtual void readRawValue();
  virtual void calcSensorValue();

  virtual bool observersMustBeNotified();
  virtual void saveReportedState();

private:
  MPU6050 mpu;
  uint8_t mpu_address;

  YawPitchRollValue prevValues;
  YawPitchRollValue lastValues;

};

#endif

