#pragma once
#include <windows.h>
#include <iostream>
#include <exception>
#include <SDL.h>
#include <GL/glew.h>
#include<math.h>
#include <vector>
#ifndef CDESSINE_H
#define CDESSINE_H
#include <vector>
#include "NIDAQmx.h"
using namespace std;

class CDessine
{

public:
	CDessine();
	~CDessine();
	void dessineUnObjet3D(int pAngleX, int pAngleY, int pAngleZ);
	void point2D(int x, int y);
	void rotationPoint3D(double& x, double& y, double& z, double alpha, double beta, double gamma);
	void Forme3D();
	void db_point();
	void db_ligne(int x1, int y1, int x3, int y3);
	void db_dessine2D();
	void placerPoint(double x, double y);
	void config(void);

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

#endif // CDESSINE_H

