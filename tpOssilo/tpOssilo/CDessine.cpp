#include "CDessine.h"
#include <iostream>

int error = 0;
float64 dataX[1]; // Data contains a single voltage channel x
float64 dataY[1]; // Data contains a single voltage channel y
TaskHandle taskHandleX;
TaskHandle taskHandleY;


CDessine::CDessine()
{
   
}

void CDessine::config()
{

	try {
		/*********************************************/
		// DAQmx Configure Code
		/*********************************************/
		error = DAQmxCreateTask("", &taskHandleX);
		if (DAQmxFailed(error)) {
			throw "Erreur CreateTask X";
		}
		error = DAQmxCreateTask("", &taskHandleY);
		if (DAQmxFailed(error)) {
			throw "Erreur CreateTask Y";
		}
		error = DAQmxCreateAOVoltageChan(taskHandleX, "Dev1/ao0", "", -10.0, 10.0, DAQmx_Val_Volts, "");
		if (DAQmxFailed(error)) {
			throw "Erreur CreateAOVoltageChan X";
		}
		error = DAQmxCreateAOVoltageChan(taskHandleY, "Dev1/ao1", "", -10.0, 10.0, DAQmx_Val_Volts, "");
		if (DAQmxFailed(error)) {
			throw "Erreur CreateAOVoltageChan Y";
		}
		/*********************************************/
		// DAQmx Start Code
		/*********************************************/
		error = DAQmxStartTask(taskHandleX);
		if (DAQmxFailed(error)) {
			throw "Erreur StartTask X";
		}
		error = DAQmxStartTask(taskHandleY);
		if (DAQmxFailed(error)) {
			throw "Erreur StartTask Y";
		}
		/*********************************************/
		// DAQmx Write Code
		/*********************************************/


	}
	catch (const char* msg)
	{
		std::string sError;
		std::cerr << "Fatal error PCI6024" << std::endl;
		std::cerr << msg << "\t" << error << std::endl;
		sError.resize(2048);
		DAQmxGetExtendedErrorInfo((char*)sError.c_str(), 2048);
		if (taskHandleX != 0) {
			/*********************************************/
			// DAQmx Stop Code
			/*********************************************/
			DAQmxStopTask(taskHandleX);
		}
		if (taskHandleY != 0) {
			/*********************************************/
			// DAQmx Stop Code
			/*********************************************/
			DAQmxStopTask(taskHandleY);
		}

	}
	catch (...)
	{
		std::cerr << "Erreur DLL" << std::endl;
		if (taskHandleX != 0) {
			/*********************************************/
			// DAQmx Stop Code
			/*********************************************/
			DAQmxStopTask(taskHandleX);
		}
		if (taskHandleY != 0) {
			/*********************************************/
			// DAQmx Stop Code
			/*********************************************/
			DAQmxStopTask(taskHandleY);
		}

	}

}

void CDessine::point2D(int x, int y)
{
	// Dessiner le point
	glBegin(GL_POINTS);
	glVertex2f(x / 256.0, y / 256.0);
	glEnd();
	glFlush();

}

CDessine::~CDessine()
{
    // Arrêt et nettoyage de vos tâches et autres ressources
    DAQmxStopTask(taskHandleX);
    DAQmxStopTask(taskHandleY);
    DAQmxClearTask(taskHandleX);
    DAQmxClearTask(taskHandleY);
}

void CDessine::placerPoint(double x, double y)
{
    // Générer un signal carré pour placer le point

	dataX[0] = x * 0.019; // 2 volts
	error = DAQmxWriteAnalogF64(taskHandleX, 1, 1, 10.0, DAQmx_Val_GroupByChannel, dataX, NULL, NULL);
	if (DAQmxFailed(error)) {
		throw "Erreur writeAnalogF64 X";
	}
	dataY[0] = y * 0.019; // 2 volts
	error = DAQmxWriteAnalogF64(taskHandleY, 1, 1, 10.0, DAQmx_Val_GroupByChannel, dataY, NULL, NULL);
	if (DAQmxFailed(error)) {
		throw "Erreur writeAnalogF64 Y";
	}
}

void CDessine::db_ligne(int x1, int y1, int x3, int y3)
{
    int x2, y2;
    int dx, dy;
    int pasx, pasy;
    int e;

    dx = x3 - x1;
    dy = y3 - y1;
    x2 = x1;
    y2 = y1;

    if (dx < 0) {
        dx = -dx;
        pasx = -1;
    }
    else {
        pasx = 1;
    }

    if (dy < 0) {
        dy = -dy;
        pasy = -1;
    }
    else {
        pasy = 1;
    }

    if (dy == 0) {
        e = -1;
    }
    else {
        e = 0;
    }

    while ((x2 != x3) || (y2 != y3)) {
        placerPoint(x2, y2);
		placerPoint(x2, y2);
        if (e >= 0) {
            y2 = y2 + pasy;
            e = e - dx;
        }
        else {
            x2 = x2 + pasx;
            e = e + dy;
        }
    }
}
