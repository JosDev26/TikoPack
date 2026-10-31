#pragma once
#include <iostream>
#include <string>
using namespace std;

string decimal(double valor);

string pad(string valor, int longi);

string padr(string valor, int longi);

string inString(string mensaje, int longi);

double inDouble(string mensaje, int longi);

int inInt(string mensaje, int min, int max);