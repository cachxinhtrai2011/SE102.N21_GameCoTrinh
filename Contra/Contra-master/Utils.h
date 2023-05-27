#pragma once

#include <Windows.h>

#include <signal.h>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include "QuadTree.h"

using namespace std;

vector<string> split(string line, string delimeter = "\t");
wstring ToWSTR(string st);
float Radius(float ax, float ay, float bx, float by);
LPCWSTR ToLPCWSTR(string st);

BOOL IsIntersac(LPGAMEOBJECT object, LPTREENODE node);
BOOL IsIntersac(float left, float top, float right, float bottom, LPTREENODE node);