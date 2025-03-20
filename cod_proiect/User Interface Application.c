//==============================================================================
//
// Title:		User Interface Application
// Purpose:		A short description of the application.
//
// Created on:	14.10.2024 at 12:19:44 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <stdlib.h>
#include <analysis.h>

#include <analysis.h>
#include <formatio.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "User Interface Application.h"
#include "toolbox.h"
#define SAMPLE_RATE		0
#define NPOINTS			1
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static int freqPanel = 0;
static int panelHandle = 0;

int waveInfo[2]; //waveInfo[0] = sampleRate
				 //waveInfo[1] = number of elements
double sampleRate = 0.0;
int npoints = 0;
double *waveData = 0;
//==============================================================================
// Static functions

//==============================================================================
// Global variables
int WindowSize = 0.0;
int start = 0,finish = 1;
short int XYset = 0;
double *output=0;
double* output1=0;
int nr=1000;//nr puncte de la start la finish ptr reprezentare semnal filtrat
double xmax=60000,xmin=0;
float alpha=0.0;
double* time_array=0;
double* envelopeData=0;
int filterType;//0=mediere;1=ordin 1
//double xfmax,xfmin,yfmax,yfmin;

//==============================================================================
// Global functions
void CustomMedianFilter(double* input, double* output, int n, int numElements,int panel);
void FirstOrderFilter(double* input, double* output, int n, double alpha,int panel);

double* Create_Time_Vector(){
	
	int i=0;
	while(i<npoints/4){
		time_array[i]=i;
		i++;
	}
		
	return time_array;
}

/// HIFN The main entry-point function.
int main (int argc, char *argv[])
{
	int error = 0;
	
	/* initialize and load resources */
	nullChk (InitCVIRTE (0, argv, 0));
	errChk (panelHandle = LoadPanel (0, "User Interface Application.uir", PANEL));
	errChk (freqPanel = LoadPanel (0, "User Interface Application.uir", FREQ_PANEL));
	/* display the panel and run the user interface */
	//errChk (DisplayPanel (panelHandle));
	errChk (DisplayPanel (freqPanel));
	errChk (RunUserInterface ());

	/*
	nullChk (InitCVIRTE (0, argv, 0));
	errChk (wavePanel = LoadPanel (0, "SwitchPanels.uir", WAVE_PANEL));
	errChk (freqPanel = LoadPanel (0, "SwitchPanels.uir", FREQ_PANEL));
	
	/* display the panel and run the user interface 
	errChk (DisplayPanel (wavePanel));
	errChk (RunUserInterface ());

	*/
Error:
	/* clean up */
	if (panelHandle > 0)
		DiscardPanel (panelHandle);
	return 0;
}

//==============================================================================
// UI callback function prototypes

/// HIFN Exit when the user dismisses the panel.

int CVICALLBACK panelCB (int panel, int event, void *callbackData,
						 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:
			
			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface(0);
			break;
	}
	return 0;
}



int CVICALLBACK LoadCB (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			//executa script python pentru conversia unui fisierului .wav in .txt
			//LaunchExecutable("python main.py");
			
			//astept sa fie generate cele doua fisiere (modificati timpul daca este necesar
			Delay(1);
			
			//incarc informatiile privind rata de esantionare si numarul de valori
			FileToArray("wafeInfo_6_seconds.txt", waveInfo, VAL_INTEGER, 2, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
			sampleRate = waveInfo[SAMPLE_RATE];
			npoints = waveInfo[NPOINTS];
			
			
			//sampleRate=44100;
			//npoints=685056;
			
			//alocare memorie pentru numarul de puncte
			waveData = (double *) calloc(npoints, sizeof(double));
			output = (double *) calloc(npoints, sizeof(double));
			output1 = (double *) calloc(npoints, sizeof(double));
			//incarcare din fisierul .txt in memorie (vector)
			FileToArray("waveData_6_seconds.txt", waveData, VAL_DOUBLE, npoints, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
			
			
			envelopeData = (double *) calloc(npoints, sizeof(double));
			FileToArray("envelopeData.txt", envelopeData, VAL_DOUBLE, npoints, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
			
			
			RawDataGraphCB(panel,control,event, callbackData, eventData1,eventData2);
			
			time_array=(double *) calloc(npoints, sizeof(double));
			AnvelopaCB(panel,control,event, callbackData, eventData1,eventData2);
			
			//WindowSizeCB(panel,control,event, callbackData, eventData1,eventData2);
			//CustomMedianFilter(&waveData[0], output, waveInfo[1], WindowSize,panel);
			
			
			//AlphaCB(panel,control,event, callbackData, eventData1,eventData2);
        	//FirstOrderFilter(&waveData[0], output1, waveInfo[1], alpha,panel);
			
			MeanCB(panel,control,event, callbackData, eventData1,eventData2);
			NrTreceriZeroCB(panel,control,event, callbackData, eventData1,eventData2);
			MinCB(panel,control,event, callbackData, eventData1,eventData2);
			MaxCB(panel,control,event, callbackData, eventData1,eventData2);
			MedianaCB(panel,control,event, callbackData, eventData1,eventData2);
			DispCB(panel,control,event, callbackData, eventData1,eventData2);
			KurtosisCB(panel,control,event, callbackData, eventData1,eventData2);
			SkewnessCB(panel,control,event, callbackData, eventData1,eventData2);
			break;
	}
	return 0;
}
void Salvare_grafic(){
	
}
//Filtru median
void CustomMedianFilter(double* input, double* output, int n, int numElements,int panel) {
    double sum = 0.0;
	
	for (int i = 0; i < n; i++) {
		if(i<numElements){
			sum+=input[i];
		}
		else if(i>=numElements){
			sum =sum + input[i] - input[i - numElements];
		}
		
		output[i] = sum/numElements;
    }
	
	//DeleteGraphPlot(panelHandle, PANEL_GRAPH_FILTERED_DATA, -1, VAL_IMMEDIATE_DRAW);
			PlotY(panel, PANEL_GRAPH_FILTERED_DATA, output, nr, VAL_DOUBLE, VAL_THIN_LINE, 
				  VAL_EMPTY_SQUARE, VAL_THIN_LINE, VAL_CONNECTED_POINTS, VAL_BLUE);
}

// Filtru de ordin I
void FirstOrderFilter(double* input, double* output, int n, double alpha,int panel) {
    output[0] = input[0];
    for (int i = 1; i < n; i++) {
        output[i] = (1 - alpha) * output[i - 1] + alpha * input[i];
    }
	
	//DeleteGraphPlot(panelHandle, PANEL_GRAPH_FILTERED_DATA, -1, VAL_IMMEDIATE_DRAW);
			PlotY(panel, PANEL_GRAPH_FILTERED_DATA, output, nr, VAL_DOUBLE, VAL_THIN_LINE, 
				  VAL_EMPTY_SQUARE, VAL_THIN_LINE, VAL_CONNECTED_POINTS, VAL_BLUE);
}

int CVICALLBACK RawDataGraphCB (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//afisare pe grapf
			PlotY(panel, PANEL_GRAPH_RAW_DATA, waveData, npoints, VAL_DOUBLE, VAL_THIN_LINE, 
				  VAL_EMPTY_SQUARE, VAL_THIN_LINE, VAL_CONNECTED_POINTS, VAL_MAGENTA);
			
			break;
	}
	return 0;
}

int CVICALLBACK FilteredDataGraphCB (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			/*	
			DeleteGraphPlot(panelHandle, PANEL_GRAPH_FILTERED_DATA, -1, VAL_IMMEDIATE_DRAW);
			PlotY(panel, PANEL_GRAPH_FILTERED_DATA, output, nr, VAL_DOUBLE, VAL_THIN_LINE, 
				  VAL_EMPTY_SQUARE, VAL_THIN_LINE, VAL_CONNECTED_POINTS, VAL_BLUE);
			*/
			break;
	}
	return 0;
}

int CVICALLBACK PrevCB (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			
			if(start-1<0){
				start=0;finish=1;
			}
			else{
				start--;finish--;
			}
	
			StartStopCB(panel,control,event, callbackData, eventData1,eventData2);

			ApplCB(panel,control,event, callbackData, eventData1,eventData2);
				break;
	}
	return 0;
}

int CVICALLBACK NextCB (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		
			if(finish+1>6){
				start=5;finish=6;
			}
			else{
				start++;finish++;
			}
			StartStopCB(panel,control,event, callbackData, eventData1,eventData2);

			ApplCB(panel,control,event, callbackData, eventData1,eventData2);

			
			break;
	}
	return 0;
}

int CVICALLBACK ApplCB (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DeleteGraphPlot(panelHandle, PANEL_GRAPH_FILTERED_DATA, -1, VAL_IMMEDIATE_DRAW);
			GetCtrlVal(panel, PANEL_FILTRU, &filterType);
			if(filterType==0){
				WindowSizeCB(panel,control,event, callbackData, eventData1,eventData2);
				CustomMedianFilter(&waveData[0], output, waveInfo[1], WindowSize,panel);
			}
			else if(filterType==1){
				AlphaCB(panel,control,event, callbackData, eventData1,eventData2);
        		FirstOrderFilter(&waveData[0], output1, waveInfo[1], alpha,panel);
    		}
						
			break;
	}
	return 0;
}


//===============MEDIA=============
int CVICALLBACK MeanCB (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	double mean = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			int err = Mean(waveData,npoints,&mean);
			if (err ==0){
				//double val;
				char mean_ch[10];
				sprintf(mean_ch, "%.2f", mean); 
				SetCtrlVal (panelHandle, PANEL_MEAN, mean_ch);
				
			}
			
			
			break;
	}
	return 0;
}

int CVICALLBACK WindowSizeCB (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:

			int wdS;
			
			GetCtrlVal(panelHandle, PANEL_WINDOW_SIZE, &wdS);
			
			/*if(wdS==0){
				WindowSize = 16;
			}else if(wdS==1){
				WindowSize=32;
			}*/
			if(wdS==0){
				WindowSize = 1;
			}else if(wdS==1){
				WindowSize=16;
			}else if(wdS==2){
				WindowSize=32;
			}else if(wdS==3){
				WindowSize=128;
			}
			
			//WindowSize =atof(wdS);
			
			
			break;
	}
	return 0;
}

int CVICALLBACK FilterCB (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
        	GetCtrlVal(panel, PANEL_FILTRU, &filterType);
    		/*int displayLength = sampleRate * 6; 
			int startIndex = start * displayLength;
		    int endIndex = startIndex + displayLength;

		    if (startIndex >= npoints) startIndex = npoints - displayLength;
		    if (startIndex < 0) startIndex = 0;
		    if (endIndex > npoints) endIndex = npoints;


    		int nToPlot = endIndex - startIndex;

			
			
			if(filterType==0){
				WindowSizeCB(panel,control,event, callbackData, eventData1,eventData2);
				CustomMedianFilter(&waveData[startIndex], output, nToPlot, WindowSize);
			}
			else {
				AlphaCB(panel,control,event, callbackData, eventData1,eventData2);
        		FirstOrderFilter(&waveData[startIndex], output, nToPlot, alpha);
    		}*/
			
			if(filterType==0){
				WindowSizeCB(panel,control,event, callbackData, eventData1,eventData2);
				CustomMedianFilter(&waveData[0], output, waveInfo[1], WindowSize,panel);
			}
			else {
				AlphaCB(panel,control,event, callbackData, eventData1,eventData2);
        		FirstOrderFilter(&waveData[0], output, waveInfo[1], alpha,panel);
    		}
			
			
			break;
	}
	return 0;
}

int CVICALLBACK StartStopCB (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			char str[100];
			sprintf(str, "%d", start); 
			SetCtrlVal(panelHandle, PANEL_START, str);
			
			char str1[100];
			sprintf(str1, "%d", finish); 
			SetCtrlVal(panelHandle, PANEL_STOP, str1);
			break;
	}
	return 0;
}


//free(waveData);

//=================DISPERSIE===============

int CVICALLBACK DispCB (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			double disp;
			double mean;
			Mean(waveData,npoints,&mean);
			Variance(waveData,npoints,&mean,&disp);
			
			char str[100];
			sprintf(str, "%.2f", disp); 
			SetCtrlVal (panelHandle, PANEL_DISPERSIE, str);
			break;
	}
	return 0;
}

//=============MINIM==============

int CVICALLBACK MinCB (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			double min = 99999;
			for(int i=0;i<npoints;i++){
				if(waveData[i] < min){
					min = waveData[i];
				}
			}
			char str[10];
			sprintf(str, "%.2f", min); 
			SetCtrlVal (panelHandle, PANEL_MINIM, str);
			break;
	}
	return 0;
}


//==========MAXIM=========

int CVICALLBACK MaxCB (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			double max = -99999;
			for(int i=0;i<npoints;i++){
				if(waveData[i] > max){
					max = waveData[i];
				}
			}
			//double max;
			
			char str[10];
			sprintf(str, "%.2f", max); 
			SetCtrlVal (panelHandle, PANEL_MAXIM, str);
			break;
	}
	return 0;
}

int CVICALLBACK MedianaCB (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			/*
			double mediana = calcMedian(waveData,npoints);
			
			char str[10];
			sprintf(str, "%.2f", mediana); 
			SetCtrlVal (panelHandle, PANEL_MEDIANA, str);\
			*/
			double mediana;
			Median(waveData,npoints,&mediana);
			char str[100];
			sprintf(str, "%.2f", mediana); 
			SetCtrlVal (panelHandle, PANEL_MEDIANA, str);
			
			break;
	}
	return 0;
}

//============NR=TRECERI=ZERO============
int CVICALLBACK NrTreceriZeroCB (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			int nr=0;
			for(int i=1;i<npoints;i++){
				if((waveData[i-1] >= 0 && waveData[i] < 0) || (waveData[i-1] <= 0 && waveData[i] > 0)){
					nr++;
				}
			}
			char str[10];
			sprintf(str, "%d", nr); 
			SetCtrlVal (panelHandle, PANEL_NR_ZERO, str);
			break;
	}
	return 0;
}

int CVICALLBACK AlphaCB (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			char str[10];
			GetCtrlVal(panelHandle, PANEL_ALPHA, str);
			sprintf(str, "%f", alpha); 
			//alpha=atof(str);
			
			break;
	}
	return 0;
}

int CVICALLBACK SkewnessCB (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			double skew;
			Moment (waveData, 256, 3, &skew);
			char str[100000];
			sprintf(str, "%lf", skew); 
			SetCtrlVal(panelHandle, PANEL_SKEWNESS, str);
			break;
	}
	return 0;
}

int CVICALLBACK KurtosisCB (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			double kurt;
			Moment (waveData, 256, 4, &kurt);
			char str[100000];
			sprintf(str, "%lf.2", kurt); 
			SetCtrlVal(panelHandle, PANEL_KURTOSIS, str);
			break;
	}
	return 0;
}



int CVICALLBACK SaveCB (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//Salvare_grafic();
			//int val = 0;
			int year = 0;
			int month = 0;
			int day = 0;
			int hour = 0;
			int minute = 0;
			int second = 0;
			char path[MAX_PATHNAME_LEN] = { 0 };
					
			int bitmapID;
			

			
			GetSystemDate (&month, &day, &year);
			GetSystemTime (&hour, &minute, &second);
			sprintf(path, "DataRaw_%d.%d.%d_%d-%d-%d.jpeg", year, month, day, hour, minute, second);
			// ArrayToFile(path, waveData, VAL_DOUBLE, npoints, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_CONST_WIDTH, 10, VAL_ASCII, VAL_TRUNCATE);
			
			GetCtrlDisplayBitmap(panel, PANEL_GRAPH_RAW_DATA, 1, &bitmapID);
			SaveBitmapToJPEGFile(bitmapID, path, JPEG_PROGRESSIVE, 100);
			DiscardBitmap(bitmapID);
			
			sprintf(path, "DataFiltered_%d.%d.%d_%d-%d-%d.jpeg", year, month, day, hour, minute, second);
			GetCtrlDisplayBitmap(panel, PANEL_GRAPH_FILTERED_DATA, 1, &bitmapID);
			SaveBitmapToJPEGFile(bitmapID, path, JPEG_PROGRESSIVE, 100);
			DiscardBitmap(bitmapID);
			
			MessagePopup("Done", "Imaginile au fost salvate!");
			break;
	}
	return 0;
}


int CVICALLBACK AnvelopaCB (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//PlotY(panel, PANEL_ANVELOPA, envelopeData, npoints, VAL_DOUBLE, VAL_THIN_LINE, 
				//  VAL_EMPTY_SQUARE, VAL_THIN_LINE, VAL_CONNECTED_POINTS, VAL_BLUE);
	
			
			
			//double t[1000]; // vector de timp
			//double x[1000]; // semnalul original
			//double envelope[1000]; // anvelopa Hilbert
			time_array=Create_Time_Vector();
			
			PlotXY(panelHandle, PANEL_ANVELOPA, time_array, waveData, npoints, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_BLUE);
			PlotXY(panelHandle, PANEL_ANVELOPA, time_array, envelopeData, npoints, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);
			break;
	}
	return 0;
}


int CVICALLBACK SwitchCB (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(panel == panelHandle)
			{
				SetCtrlVal(freqPanel, FREQ_PANEL_SWITCH, 1);
				DisplayPanel(freqPanel);
				HidePanel(panel);
			}
			else
			{
				SetCtrlVal(panelHandle, PANEL_SWITCH, 0);
				DisplayPanel(panelHandle);
				HidePanel(panel);
			}
			break;
	}
	return 0;
}

