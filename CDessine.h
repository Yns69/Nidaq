#pragma once
#include <vector>
using namespace std;
#define NIDAQ
class CDessine
{
public:

    void point2D(int px, int py);
    void db_ligne(int x1, int y1, int x3, int y3);
    void Forme3D(void);
    void dessineUnObjet3D(int pAngleX, int pAngleY, int pAngleZ);
    void Rotationpoint3D(double& nx, double& ny, double& nz, double ax, double ay, double az, double alpha, double beta, double gamma);
    void config(void);
    void pointDaQ(int px, int py);


private:
    struct LigneEspace {
        double x;
        double y;
        double z;
        double x2;
        double y2;
        double z2;
    };
    vector<LigneEspace> Ligne3D;



};