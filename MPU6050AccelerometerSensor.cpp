// 
// 
// 

#include "MPU6050AccelerometerSensor.h"
#include "SenseUtils.h"

YawPitchRollValue MPU6050AccelerometerSensor::getlastValues() {
  return lastValues;
}

byte * MPU6050AccelerometerSensor::getValueInBuffer(byte * buffer) {
  memcpy(buffer, &lastValues, sizeof(YawPitchRollValue));
  return buffer;
}

char* MPU6050AccelerometerSensor::getValueAsChars(char* value) {
  lastValues.getAsChars(value);
  return value;
}

byte MPU6050AccelerometerSensor::getMinBufferSize() {
  return sizeof(YawPitchRollValue);
}

MPU6050AccelerometerSensor::MPU6050AccelerometerSensor(uint8_t sensorId, uint8_t address) : SenseI2CBusSensor(sensorId), mpu_address(address) {
};

void MPU6050AccelerometerSensor::initialize() {
  sensorActive = mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G, mpu_address);
}


void MPU6050AccelerometerSensor::readRawValue() {

  Vector normAccel = mpu.readNormalizeAccel();

  // Calculate Pitch & Roll
  lastValues.setPitch(-(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0) / M_PI);
  lastValues.setRoll((atan2(normAccel.YAxis, normAccel.ZAxis)*180.0) / M_PI);
}

void MPU6050AccelerometerSensor::calcSensorValue() {
}

bool MPU6050AccelerometerSensor::observersMustBeNotified() {
  //TODO: add a threshold to MU6050AccelerometerSensor
  return (prevValues != lastValues);
}

void MPU6050AccelerometerSensor::saveReportedState() {
  prevValues = lastValues;
}
