/**
 ******************************************************************************
 * File Name          : AltitudePublishTask.hpp
 * Description        :
 ******************************************************************************
 */
#ifndef CUBE_SYSTEM_ALTITUDE_PUBLISH_TASK_HPP_
#define CUBE_SYSTEM_ALTITUDE_PUBLISH_TASK_HPP_
/* Includes ------------------------------------------------------------------*/
#include "Task.hpp"
#include "SystemDefines.hpp"

class AltitudePublishTask: public Task {
public:
	static AltitudePublishTask& Inst() {
		static AltitudePublishTask inst;
		return inst;
	}

	void InitTask();

protected:
	static void RunTask(void *pvParams) {
		AltitudePublishTask::Inst().Run(pvParams);
	}  // Static Task Interface, passes control to the instance Run();

	void Run(void *pvParams);  // Main run code

	void ConfigureUART();


	// Implementation of DataBroker API.
	void HandleCommand(Command& cm);
	void HandleDataBrokerCommand(const Command& cm);

private:
	AltitudePublishTask();                             // Private constructor
	AltitudePublishTask(const AltitudePublishTask&);              // Prevent copy-construction
	AltitudePublishTask& operator=(const AltitudePublishTask&);  // Prevent assignment
};

#endif  // CUBE_SYSTEM_ALTITUDE_TASK_HPP_
