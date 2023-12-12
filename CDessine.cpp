#include <windows.h>
#include <vector>
#include <iostream>
#include <exception>
#include <SDL.h>
#include <GL/glew.h>
#include "CDessine.h"
#include "NIDAQmx.h"
using namespace std;

int error = 0;
float64 datax[1]; // Data contains a single voltage channel x
float64 datay[1]; // Data contains a single voltage channel y
TaskHandle taskHandleX;
TaskHandle taskHandleY;


void CDessine::point2D(int px, int py) //methode qui permet d'afficher un point
{
    glPointSize(1.5);
    glColor3f(0, 1, 0);
    glBegin(GL_POINTS);
    glVertex2f(px / 256.0, py / 256.0);
    glEnd();
}

void CDessine::db_ligne(int x1, int y1, int x3, int y3)
{
    int x2, y2;
    int dx, dy;
    int pasx, pasy;
    int e;
    // Initialisation
    dx = x3 - x1;
    dy = y3 - y1;
    x2 = x1;
    y2 = y1;
    // initialisation de dx et pasx
    if (dx < 0) { dx = -dx; pasx = -1; }
    else pasx = 1;
    // initialisation de dy et pasy
    if (dy < 0) { dy = -dy; pasy = -1; }
    else pasy = 1;
    if (dy == 0) e = -1; else e = 0;
    while ((x2 != x3) || (y2 != y3)) {
#ifdef NIDAQ
        pointDaQ(x2, y2);
#endif // NIDAQ


        point2D(x2, y2);
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

struct LigneEspace {
    double x;
    double y;
    double z;
    double x2;
    double y2;
    double z2;
};
void CDessine::Forme3D(void)
{
    //face avant
    Ligne3D.push_back({ -50,50,-50,  50,50,-50 });
    Ligne3D.push_back({ 50,50,-50,   50,-50,-50 });
    Ligne3D.push_back({ 50,-50,-50,  -50,-50,-50 });
    Ligne3D.push_back({ -50,-50,-50,  -50,50,-50 });
    //face arriere
    Ligne3D.push_back({ -50,50,50,  50,50,50 });
    Ligne3D.push_back({ 50,50,50,   50,-50,50 });
    Ligne3D.push_back({ 50,-50,50,  -50,-50,50 });
    Ligne3D.push_back({ -50,-50,50,  -50,50,50 });

    //diagonales
    Ligne3D.push_back({ -50,50,-50,    -50,50,50 });
    Ligne3D.push_back({ 50,50,-50,       50,50,50 });
    Ligne3D.push_back({ 50,-50,-50,      50,-50,50 });
    Ligne3D.push_back({ -50,-50,-50,   -50,-50,50 });


}

void CDessine::dessineUnObjet3D(int pAngleX, int pAngleY, int pAngleZ)
{
    double nx, ny, nz, nx2, ny2, nz2;
    for (int i = 0; i < Ligne3D.size(); i++)
    {
        Rotationpoint3D(nx, ny, nz, Ligne3D.at(i).x, Ligne3D.at(i).y, Ligne3D.at(i).z, pAngleX, pAngleY, pAngleZ);
        Rotationpoint3D(nx2, ny2, nz2, Ligne3D.at(i).x2, Ligne3D.at(i).y2, Ligne3D.at(i).z2, pAngleX, pAngleY, pAngleZ);
        db_ligne(nx, ny, nx2, ny2);
    }



}

void CDessine::Rotationpoint3D(double& nx, double& ny, double& nz, double ax, double ay, double az, double alpha, double beta, double gamma)
{
    alpha = alpha * 3.14 / 180;
    beta = beta * 3.14 / 180;
    gamma = gamma * 3.14 / 180;


    nx = ax * (cos(beta) * cos(alpha)) + ay * (-cos(beta) * sin(alpha)) + az * (sin(beta));
    ny = ax * (sin(gamma) * sin(beta) * cos(alpha) + cos(gamma) * sin(alpha)) + ay * (-sin(alpha) * sin(gamma) * sin(beta) + cos(alpha) * cos(gamma)) + az * (-cos(beta) * sin(gamma));
    nz = ax * (-cos(gamma) * sin(beta) * cos(alpha) + sin(gamma) * sin(alpha)) + ay * (sin(alpha) * cos(gamma) * sin(beta) + sin(gamma) * cos(alpha)) + az * (cos(gamma) * cos(beta));
}

void CDessine::config(void)
{
#ifdef NIDAQ

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
#endif // DEBUG
}

void CDessine::pointDaQ(int px, int py)
{
#ifdef NIDAQ

    datax[0] = px * 0.019; // 2 volts
    error = DAQmxWriteAnalogF64(taskHandleX, 1, 1, 10.0, DAQmx_Val_GroupByChannel, datax, NULL, NULL);
    if (DAQmxFailed(error)) {
        throw "Erreur writeAnalogF64 X";
    }
    datay[0] = py * 0.019; // 2 volts
    error = DAQmxWriteAnalogF64(taskHandleY, 1, 1, 10.0, DAQmx_Val_GroupByChannel, datay, NULL, NULL);
    if (DAQmxFailed(error)) {
        throw "Erreur writeAnalogF64 Y";
    }
#endif // 
}