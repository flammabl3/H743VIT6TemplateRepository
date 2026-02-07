/**
 ******************************************************************************
 * File Name          : AltitudeTask.cpp
 * Description        : Altitude Prediction Filter
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "AltitudeTask.hpp"
#include "stm32h7xx_hal.h"
#include "SensorDataTypes.hpp"
#include "DataBroker.hpp"
#include "DataBrokerMessageTypes.hpp"

// External Tasks (to send debug commands to)

/* Macros --------------------------------------------------------------------*/

/* Structs -------------------------------------------------------------------*/

/* Constants -----------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/

/* Prototypes ----------------------------------------------------------------*/

/**
 * @brief Init task for RTOS
 */
void AltitudeTask::InitTask() {
	// Make sure the task is not already initialized
	SOAR_ASSERT(rtTaskHandle == nullptr,
			"Cannot initialize Altitude task twice");

	// Start the task
	BaseType_t rtValue = xTaskCreate((TaskFunction_t) AltitudeTask::RunTask,
			(const char*) "AltitudeTask",
			(uint16_t) TASK_ALTITUDE_STACK_DEPTH_WORDS, (void*) this,
			(UBaseType_t) TASK_ALTITUDE_PRIORITY,
			(TaskHandle_t*) &rtTaskHandle);

	// Ensure creation succeeded
	SOAR_ASSERT(rtValue == pdPASS,
			"AltitudeTask::InitTask - xTaskCreate() failed");
}

// TODO: Only run thread when appropriate GPIO pin pulled HIGH (or by define)
/**
 *    @brief Runcode for the AltitudeTask
 */
void AltitudeTask::Run(void *pvParams) {
	// Create an everest object
	everest = EverestTask::getEverest();

	// Task subscribes to Data using DataBroker.
	// Should we subscribe to each sensor individually?
	DataBroker::Subscribe<IMUData>(this);
	DataBroker::Subscribe<GPSData>(this);
	DataBroker::Subscribe<MagData>(this);
	DataBroker::Subscribe<BaroData>(this);

	while (1) {
		// Time in seconds given by ticks since program execution, divided by 1000.0f for seconds.
		currentTime = TICKS_TO_MS(xTaskGetTickCount()) / 1000.0f;

		/* Process commands in blocking mode
		 * HandleCommand should place the appropriate sensor data into their respective structs.
		 * */
		Command cm;
		bool res = qEvtQueue->ReceiveWait(cm);
		if (res) {
			HandleCommand(cm);
		}

		// main wrapper for all the Prediction filter tasks. We might want to ensure data is within the same time window.
		std::vector<float> haloData = everest.QueueEverest(&everest);

		// should this be blocking?
		FilterData haloOutput =
				{ haloData.at(0), haloData.at(1), haloData.at(2) };

		DataBroker::Publish<FilterData>(&haloOutput);
	}
}

/**
 * @brief Handles a command
 * @param cm Command reference to handle
 */
void AltitudeTask::HandleCommand(Command &cm) {
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
 * @brief Handle all data broker commands
 * @param cm The command object with the data
 *            Use cm.GetTaskCommand() to get the message type
 *              Message types must be cast back into DataBrokerMessageTypes enum
 *            Use cm.GetDataPointer() to get the pointer to the data
 */
void AltitudeTask::HandleDataBrokerCommand(const Command &cm) {
	DataBrokerMessageTypes messageType = DataBroker::getMessageType(cm);
	switch (messageType) {
	case DataBrokerMessageTypes::IMU_DATA: {
		IMUData imu_data = DataBroker::ExtractData<IMUData>(cm);

		// How will we identify each IMU?
		SOAR_PRINT("\n IMU DATA : \n");
		SOAR_PRINT("  X -> %d \n", imu_data.accelX);
		SOAR_PRINT("  Y -> %d \n", imu_data.accelY);
		SOAR_PRINT("  Z -> %d \n", imu_data.accelZ);
		SOAR_PRINT("--DATA_END--\n\n");

		// note that imu_data will not contain magnetometer data. Everest still takes mag as part of IMUData_Everest, so we will add it when MAG_DATA is received.
		// will currentTime be subject to async problems? currentTime might not be updated by the time this is called.
		IMUData1 = IMUData_Everest(currentTime, imu_data.gyroX, imu_data.gyroY,
				imu_data.gyroZ, imu_data.accelX, imu_data.accelY,
				imu_data.accelZ, IMUData1.magX, IMUData1.magY, IMUData1.magZ);
		everest.IMU1_Measurements(IMUData1, &everest);

		// imudata2 is reduplicated for now...
		IMUData2 = IMUData_Everest(currentTime, imu_data.gyroX, imu_data.gyroY,
				imu_data.gyroZ, imu_data.accelX, imu_data.accelY,
				imu_data.accelZ, IMUData1.magX, IMUData1.magY, IMUData1.magZ);
		everest.IMU2_Measurements(IMUData2, &everest);

		break;
	}

	case DataBrokerMessageTypes::GPS_DATA: {
		GPSData gps_data = DataBroker::ExtractData<GPSData>(cm);

		gps = gps_data.gps;
		everest.GPS_Measurements(gps, &everest);

		break;
	}

	case DataBrokerMessageTypes::MAG_DATA:{
		MagData mag_data = DataBroker::ExtractData<MagData>(cm);

		//update IMU data with new mag measurements
		IMUData1 = IMUData_Everest(currentTime, IMUData1.gyroX, IMUData1.gyroY,
				IMUData1.gyroZ, IMUData1.accelX, IMUData1.accelY,
				IMUData1.accelZ, mag_data.magX, mag_data.magY, mag_data.magZ);
		everest.IMU1_Measurements(IMUData1, &everest);

		// imudata2 is reduplicated for now...
		IMUData2 = IMUData_Everest(currentTime, IMUData2.gyroX, IMUData2.gyroY,
				IMUData2.gyroZ, IMUData2.accelX, IMUData2.accelY,
				IMUData2.accelZ, mag_data.magX, mag_data.magY, mag_data.magZ);
		everest.IMU2_Measurements(IMUData2, &everest);


		break;
	}

	case DataBrokerMessageTypes::BARO_DATA: {
		BaroData baro_data = DataBroker::ExtractData<BaroData>(cm);

	    baro1 = {currentTime, baro_data.baro, 0, 0};
	    everest.Baro1_Measurements(baro1, &everest);

	    baro2 = {currentTime, baro_data.baro, 0, 0};
	    everest.Baro2_Measurements(baro2, &everest);

		break;
	}

	case DataBrokerMessageTypes::INVALID:
		[[fallthrough]];
	default:
		break;
	}
}

