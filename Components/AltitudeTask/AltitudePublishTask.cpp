/**
 ******************************************************************************
 * File Name          : AltitudePublishTask.cpp
 * Description        : Altitude Prediction Filter
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "AltitudePublishTask.hpp"
#include "stm32h7xx_hal.h"
#include "SensorDataTypes.hpp"
#include "DataBroker.hpp"
#include "DataBrokerMessageTypes.hpp"
#include "Publisher.hpp"

// External Tasks (to send debug commands to)

/* Macros --------------------------------------------------------------------*/

/* Structs -------------------------------------------------------------------*/

/* Constants -----------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/

/* Prototypes ----------------------------------------------------------------*/

AltitudePublishTask::AltitudePublishTask() {
	// don't know what to write for a Task constructor.
}

/**
 * @brief Init task for RTOS
 */
void AltitudePublishTask::InitTask() {
	// Make sure the task is not already initialized
	SOAR_ASSERT(rtTaskHandle == nullptr,
			"Cannot initialize Altitude task twice");

	// Start the task
	BaseType_t rtValue = xTaskCreate((TaskFunction_t) AltitudePublishTask::RunTask,
			(const char*) "AltitudePublishTask",
			(uint16_t) TASK_ALTITUDE_STACK_DEPTH_WORDS, (void*) this,
			(UBaseType_t) TASK_ALTITUDE_PRIORITY,
			(TaskHandle_t*) &rtTaskHandle);

	// Ensure creation succeeded
	SOAR_ASSERT(rtValue == pdPASS,
			"AltitudePublishTask::InitTask - xTaskCreate() failed");

}

// TODO: Only run thread when appropriate GPIO pin pulled HIGH (or by define)
/**
 *    @brief Publishes dummy data of the types for the Altitude Filter.
 */
void AltitudePublishTask::Run(void *pvParams) {


	// dummy publishers to avoid SOAR_ASSERT
	IMUData imu{};
	GPSData gps{};
	MagData mag{};
	BaroData baro{};

	DataBroker::Publish(&imu);
	DataBroker::Publish(&gps);
	DataBroker::Publish(&mag);
	DataBroker::Publish(&baro);


	while (1) {
		imu.accelX = 0;
		imu.accelY = 0;
		imu.accelZ = 0;
		imu.gyroX = 0;
		imu.gyroY = 0;
		imu.gyroZ = 0;

		gps.gps = 0;

		mag.magX = 0;
		mag.magY = 0;
		mag.magZ = 0;

		baro.baro = 0;


		DataBroker::Publish<IMUData>(&imu);
		DataBroker::Publish<GPSData>(&gps);
		DataBroker::Publish<MagData>(&mag);
		DataBroker::Publish<BaroData>(&baro);
	}
}

/**
 * @brief Handles a command
 * @param cm Command reference to handle
 */
void AltitudePublishTask::HandleCommand(Command &cm) {
	switch (cm.GetCommand()) {
	case DATA_BROKER_COMMAND:
		HandleDataBrokerCommand(cm);
		break;

	default:
		SOAR_PRINT("PubSubReceive - Received Unsupported Command {%d}\n",
				cm.GetCommand());
		break;
	}

	// No matter what we happens, we must reset allocated data
	cm.Reset();
}

/**
 @ does nothing for now.
 */
void AltitudePublishTask::HandleDataBrokerCommand(const Command &cm) {

}

