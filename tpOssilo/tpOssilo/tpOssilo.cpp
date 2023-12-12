#include <iostream>
#include "NIDAQmx.h"
#include "CDessine.h"
int main(void)
{
	CDessine dessine;
	dessine.config();
	int i = 0;
	
		dessine.db_ligne(-128, -128, 128, -128);
		dessine.db_ligne(128, -128, 128, 128);
		dessine.db_ligne(128, 128, -128, 128);
		dessine.db_ligne(-128, 128, -128, -128);
	



	/*Dessine.placerPoint(-128, -128);
	Dessine.placerPoint(-128, 128);
	Dessine.placerPoint(128, -128);
	Dessine.placerPoint(128, 128);*/

	return 0;
}



	//try {
	//	/*********************************************/
	//	// DAQmx Configure Code
	//	/*********************************************/
	//	error = DAQmxCreateTask("", &taskHandleX);
	//	if (DAQmxFailed(error)) {
	//		throw "Erreur CreateTask X";
	//	}
	//	error = DAQmxCreateTask("", &taskHandleY);
	//	if (DAQmxFailed(error)) {
	//		throw "Erreur CreateTask Y";
	//	}
	//	error = DAQmxCreateAOVoltageChan(taskHandleX, "Dev1/ao0", "", -10.0, 10.0, DAQmx_Val_Volts, "");
	//	if (DAQmxFailed(error)) {
	//		throw "Erreur CreateAOVoltageChan X";
	//	}
	//	error = DAQmxCreateAOVoltageChan(taskHandleY, "Dev1/ao1", "", -10.0, 10.0, DAQmx_Val_Volts, "");
	//	if (DAQmxFailed(error)) {
	//		throw "Erreur CreateAOVoltageChan Y";
	//	}
	//	/*********************************************/
	//	// DAQmx Start Code
	//	/*********************************************/
	//	error = DAQmxStartTask(taskHandleX);
	//	if (DAQmxFailed(error)) {
	//		throw "Erreur StartTask X";
	//	}
	//	error = DAQmxStartTask(taskHandleY);
	//	if (DAQmxFailed(error)) {
	//		throw "Erreur StartTask Y";
	//	}

	//	for (int i = 0; i < 1000; ++i) {
	//		if ((i % 500) < 250) {
	//			dataX[i] = amplitude;
	//			dataY[i] = amplitude;
	//		}
	//		else {
	//			dataX[i] = -amplitude;
	//			dataY[i] = -amplitude;
	//		}
	//	}
	//	/*********************************************/
	//	// DAQmx Write Code
	//	/*********************************************/
	//	error = DAQmxWriteAnalogF64(taskHandleX, 1000, 1, 10.0, DAQmx_Val_GroupByChannel, dataX, NULL, NULL);
	//	if (DAQmxFailed(error)) {
	//		throw "Erreur writeAnalogF64 X";
	//	}
	//	error = DAQmxWriteAnalogF64(taskHandleY, 1000, 1, 10.0, DAQmx_Val_GroupByChannel, dataY, NULL, NULL);
	//	if (DAQmxFailed(error)) {
	//		throw "Erreur writeAnalogF64 Y";
	//	}
	//}
	//catch (const char* msg)
	//{
	//	std::string sError;
	//	std::cerr << "Fatal error PCI6024" << std::endl;
	//	std::cerr << msg << "\t" << error << std::endl;
	//	sError.resize(2048);
	//	DAQmxGetExtendedErrorInfo((char*)sError.c_str(), 2048);
	//	if (taskHandleX != 0) {
	//		/*********************************************/
	//		// DAQmx Stop Code
	//		/*********************************************/
	//		DAQmxStopTask(taskHandleX);
	//		DAQmxClearTask(taskHandleX);
	//	}
	//	if (taskHandleY != 0) {
	//		/*********************************************/
	//		// DAQmx Stop Code
	//		/*********************************************/
	//		DAQmxStopTask(taskHandleY);
	//		DAQmxClearTask(taskHandleY);
	//	}
	//	return -1;
	//}
	//catch (...)
	//{
	//	std::cerr << "Erreur DLL" << std::endl;
	//	if (taskHandleX != 0) {
	//		/*********************************************/
	//		// DAQmx Stop Code
	//		/*********************************************/
	//		DAQmxStopTask(taskHandleX);
	//		DAQmxClearTask(taskHandleX);
	//	}
	//	if (taskHandleY != 0) {
	//		/*********************************************/
	//		// DAQmx Stop Code
	//		/*********************************************/
	//		DAQmxStopTask(taskHandleY);
	//		DAQmxClearTask(taskHandleY);
	//	}
	//	return -1;
	//}
	//return 0;