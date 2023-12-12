#pragma once
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
	void placerPoint(double x, double y);
	void db_ligne(int x1, int y1, int x3, int y3);
	void config(void);

private:
	TaskHandle taskHandleX;
	TaskHandle taskHandleY;
	int error;
	const double amplitude = 1.0;


};
#endif // CDESSINE_H

