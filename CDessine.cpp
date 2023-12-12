#include "CDessine.h"
#include <vector>
using namespace std;

int error = 0;
float64 dataX[1]; // Data contains a single voltage channel x
float64 dataY[1]; // Data contains a single voltage channel y
TaskHandle taskHandleX;
TaskHandle taskHandleY;
CDessine::CDessine()
{
}

CDessine::~CDessine()
{
}

void CDessine::dessineUnObjet3D(int pAngleX, int pAngleY, int pAngleZ)
{
    double nx, ny, nz, nx2, ny2, nz2;
    for (int i = 0; i < Ligne3D.size(); i++)
    {
        rotationPoint3D(nx, ny, nz, Ligne3D.at(i).x, Ligne3D.at(i).y, Ligne3D.at(i).z, pAngleX, pAngleY, pAngleZ);
        rotationPoint3D(nx2, ny2, nz2, Ligne3D.at(i).x2, Ligne3D.at(i).y2, Ligne3D.at(i).z2, pAngleX, pAngleY, pAngleZ);
        db_ligne(nx, ny, nx2, ny2);
    }
}


void CDessine::point2D(int x, int y)
{
 
    // Dessiner le point
    glBegin(GL_POINTS);
    glVertex2f(x/256.0, y/256.0);
    glEnd();
    glFlush();
}

void CDessine::rotationPoint3D(double& x, double& y, double& z, double alpha, double beta, double gamma)
{

    // Conversion des angles en radians
    double alpha_rad = alpha * (M_PI / 180.0);
    double beta_rad = beta * (M_PI / 180.0);
    double gamma_rad = gamma * (M_PI / 180.0);

    // Calcul des nouvelles coordonnées
    double newX = x * (cos(beta_rad) * cos(gamma_rad)) + y * (-cos(beta_rad) * sin(gamma_rad)) + z * (sin(beta_rad));
    double newY = x * (sin(gamma_rad) * sin(beta_rad) * cos(alpha_rad) + cos(gamma_rad) * sin(alpha_rad)) +
        y * (-sin(alpha_rad) * sin(beta_rad) * sin(gamma_rad) + cos(alpha_rad) * cos(gamma_rad)) +
        z * (-cos(beta_rad) * sin(gamma_rad));
    double newZ = x * (-cos(gamma_rad) * sin(beta_rad) * cos(alpha_rad) + sin(gamma_rad) * sin(alpha_rad)) +
        y * (sin(alpha_rad) * cos(gamma_rad) * sin(beta_rad) + sin(gamma_rad) * cos(alpha_rad)) +
        z * (cos(gamma_rad) * cos(beta_rad));

    // Mettre à jour les coordonnées
    x = newX;
    y = newY;
    z = newZ;

}
struct LigneEspace {
    double x;
    double y;
    double z;
    double x2;
    double y2;
    double z2;
};

void CDessine::Forme3D()
{
    

    //face avant
    Ligne3D.push_back({ -50,50,0,  50,50,0 });
    Ligne3D.push_back({ 50,50,0,   50,-50,0 });
    Ligne3D.push_back({ 50,-50,0,  -50,-50,0 });
    Ligne3D.push_back({ -50,-50,0,  -50,50,0 });
    //face arriere
    Ligne3D.push_back({ 0,0,0,0,100,50 });
    Ligne3D.push_back({ 0,100,0,100,100,50 });
    Ligne3D.push_back({ 100,100,0,100,0,50 });
    Ligne3D.push_back({ 100,0,0,0,0,50 });

    //diagonales
    Ligne3D.push_back({ -50,50,0,0,100,50 });
    Ligne3D.push_back({ 50,50,0,100,100,50 });
    Ligne3D.push_back({ 50,-50,0,100,0,50 });
    Ligne3D.push_back({ -50,-50,0,0,0,50 });

}

void CDessine::db_point()
{
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

    if (dx < 0){
        dx = -dx; 
        pasx = -1;
    }
    else 
        pasx = 1;
   
    if (dy < 0) {
        dy = -dy; 
        pasy = -1;
    }
    else 
        pasy = 1;
    if (dy == 0) 
        e = -1; 
    else 
        e = 0;
    while ((x2 != x3) || (y2 != y3)) {
        point2D(x2, y2);
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

void CDessine::db_dessine2D()
{
}

void CDessine::placerPoint(double x, double y)
{
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

void CDessine::config(void)
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
