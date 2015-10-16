//--------------------------------------------
// Macro to parse results from hydrodynamic
// calculation into ROOT objects
//--------------------------------------------

#include <iostream>
#include <string>

#include "TGraphErrors.h"
#include "TFile.h"

using namespace std;

//-------------------------------
// Variables
//-------------------------------

//Number of pT points on the graph
const int NPOINT = 25;

//TGraphs for v2 at different energies
TGraphErrors *g_v2_7GeV;
TGraphErrors *g_v2_7GeV_pf;

TGraphErrors *g_v2_20GeV;
TGraphErrors *g_v2_20GeV_pf;

TGraphErrors *g_v2_39GeV;
TGraphErrors *g_v2_39GeV_pf;

TGraphErrors *g_v2_64GeV;
TGraphErrors *g_v2_GeV_pf;

TGraphErrors *g_v2_200GeV;
TGraphErrors *g_v2_200GeV_pf;

//TGraphs for v3 at different energies
TGraphErrors *g_v3_7GeV;
TGraphErrors *g_v3_7GeV_pf;

TGraphErrors *g_v3_20GeV;
TGraphErrors *g_v3_20GeV_pf;

TGraphErrors *g_v3_39GeV;
TGraphErrors *g_v3_39GeV_pf;

TGraphErrors *g_v3_64GeV;
TGraphErrors *g_v3_GeV_pf;

TGraphErrors *g_v3_200GeV;
TGraphErrors *g_v3_200GeV_pf;

//-------------------------------
// Functions
//-------------------------------

void processFile(string filename, TGraphErrors *& graph_v2, TGraphErrors *& graph_v3)
{
	//Arrays to store v_n values and their uncertainties
	float pT_vals[NPOINT];
	float x_err[NPOINT];

	float v0[NPOINT];
	float v0_err[NPOINT];

	float v1[NPOINT];
	float v1_err[NPOINT];

	float v2[NPOINT];
	float v2_err[NPOINT];

	float v3[NPOINT];
	float v3_err[NPOINT];

	float v4[NPOINT];
	float v4_err[NPOINT];

	float v5[NPOINT];
	float v5_err[NPOINT];

	//Open file with v_n info
	ifstream myFile;
	myFile.open(filename.c_str());

	//Check that file exists
	if (!myFile) 
	{
		printf("Input file does not exist!\n");
		return;
	}
	else
	{
		cout << "--> Successfully opened file " << filename << endl << endl;
	}

	//Loop over file, line by line
	while(myFile)
	{
		//Read first header line
		string head[13];

		myFile >> head[0] >> head[1] >> head[2] >> head[3] >> head[4] >> head[5] >> head[6] >> head[7] >> head[8] >> head[9] >> head[10] >> head[11] >> head[12];

		//Read v_n values as a function of pT
		for(int line = 0; line<NPOINT; line++)
		{
			myFile >> pT_vals[line] >> v0[line] >> v0_err[line] >> v1[line] >> v1_err[line] >> v2[line] >> v2_err[line] >> v3[line] >> v3_err[line] >> v4[line] >> v4_err[line] >> v5[line] >> v5_err[line];
			cout << pT_vals[line] << " " << v2[line] << " " << v2_err[line] << endl;
			x_err[line] = 0;
		}	
		break;
	}

	graph_v2 = new TGraphErrors(NPOINT,pT_vals,v2,x_err,v2_err);
	graph_v3 = new TGraphErrors(NPOINT,pT_vals,v3,x_err,v3_err);
}

void parseSONIC()
{
	//File with points from SONIC
	processFile("all-dAu/7.7/av_unid_vn.dat",g_v2_7GeV,g_v3_7GeV);
}