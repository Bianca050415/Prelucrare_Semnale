#include <stdlib.h>
#include <analysis.h>

#include <analysis.h>
#include <formatio.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "User Interface Application.h"
#include "toolbox.h"

//==============================================================================
// Constants
#define SAMPLE_RATE		0
#define NPOINTS			1

#define FIR 0
#define CH_H 1

#define FILTER_LPF		0
#define FILTER_BPF		1
#define FILTER_BSF		2
#define FILTER_HPF		3
//==============================================================================
// Types

//==============================================================================
// Static global variables
double *waveData_ = 0;
double *inputSecond=0;
//double**inputPerSecond=0;
int npoints_ = 0;
int waveInfo_[2]; //waveInfo[0] = sampleRate
				 //waveInfo[1] = number of elements
double FIRcoef[65];
double*filteredSignal=0;
double sampleRate_=0.0;
int startt=0,finishh;
int StartPressed=0;
//==============================================================================
// Static functions

//==============================================================================
// Global variables
int FirType;
int filter_type, window_type, N=1;
char *str2=0;
double *autoSpectrum;
double df=0.0;
double frequencyPeak=0.0, powerPeak=0.0;
double*spectrul_rezultat;
double fpass=1500;
double fstop=1700;
double delta = 0.0;
double f1 = 1000.0; //Highest frequency of the lower stop band. The lower stop band is [0, f1]. 
double f2 = 1500.0; //Lowest frequency of the pass band. The pass band is [f2, f3]. 
double f3 = 1700.0; //Highest frequency of the pass band. The pass band is [f2, f3]. 
double f4 = 2000.0; //Lowest frequency of the upper stop band. The upper stop band is [f4, samplingFreq/2]. 
int filterOrder = 1;
int ncoef = 65;
int points_per_second;
char str[100], str1[100];
WindowConst wndConst;
int DataLoaded=0;
int puncte_nemodificate=0;
#define MAX 2048
double x[MAX];
//==============================================================================
// Global functions
void arrayCalc(double*original, int n, int start){
	
	for(int i=0;i<n;i++){
		inputSecond[i]=original[start+i];	
	}
	//return inputSecond;
}

int string_to_int(const char* str) {
    int num = 0;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            num = num * 10 + (str[i] - '0');
        } else {          
            return -1;  
        }
        i++;
    }
    return num;
}



int CVICALLBACK OnFreqPanelCB (int panel, int event, void *callbackData,
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



int CVICALLBACK AchizitieCB (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			FileToArray("wafeInfo_6_seconds.txt", waveInfo_, VAL_INTEGER, 2, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
			sampleRate_ = waveInfo_[SAMPLE_RATE];
			npoints_ = waveInfo_[NPOINTS];
			
			//points_per_second = (npoints_) / 6;
			
			waveData_ = (double *) calloc(npoints_, sizeof(double));
			FileToArray("waveData_6_seconds.txt", waveData_, VAL_DOUBLE, npoints_, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
			
		
			DataLoaded=1;
			break;
	}
	return 0;
}

int CVICALLBACK TimerCB (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	
		switch (event)
		{
			case EVENT_TIMER_TICK:/*
				if(DataLoaded&&StartPressed){
					if(puncte_nemodificate==0){
						//inputSecond=arrayCalc(waveData_,finishh,startt);
						arrayCalc(waveData_,finishh,startt);
					}
					else{
						//free(inputSecond);
						StartPressed=0;startt=0;finishh=N;
						
					}
					switch(window_type){
					case 0:
						//MessagePopup("RECTANGLE", "");
						ScaledWindowEx (inputSecond, points_per_second, RECTANGLE, 0, &wndConst);
						break;
					case 1:
						//MessagePopup("BLKHARRIS", "");
						ScaledWindowEx (inputSecond, points_per_second, BLKHARRIS, 0, &wndConst);	
						break;
					}
					autoSpectrum=(double *) calloc(points_per_second, sizeof(double));

					switch(N){
						case 1024:
							//MessagePopup("1024", "");
							AutoPowerSpectrum (inputSecond, POWER_2_10, 1.0/points_per_second, autoSpectrum, &df);
							break;
						case 2048:
							//MessagePopup("2048", "");
							AutoPowerSpectrum (inputSecond, POWER_2_11, 1.0/points_per_second, autoSpectrum, &df);
							break;
						case 4096:
							//MessagePopup("4096", "");
							AutoPowerSpectrum (inputSecond, POWER_2_12, 1.0/points_per_second, autoSpectrum, &df);
							break;
						default:
							MessagePopup("ERROR", "NU ESTE VALIDA OPTIUNEA");
					}
					
					
					
					PowerFrequencyEstimate (autoSpectrum, points_per_second, -1.0, wndConst, df, 7, &frequencyPeak, &powerPeak);
					sprintf(str, "%.2f", frequencyPeak); 
					SetCtrlVal(panel, FREQ_PANEL_FREQPEAK,str);
					sprintf(str1, "%.2f", powerPeak);
					SetCtrlVal(panel, FREQ_PANEL_POWPEAK,str1);
					
					char unitString[32]={0};
					spectrul_rezultat = (double *) calloc(points_per_second, sizeof(double));
					SpectrumUnitConversion (autoSpectrum, points_per_second, SPECTRUM_POWER, SCALING_MODE_LINEAR, DISPLAY_UNIT_VRMS, 
											1.0, wndConst, spectrul_rezultat, unitString);
					
					
					DeleteGraphPlot (panel, FREQ_PANEL_GRAPH_SPECTRUM_DATA, -1, VAL_IMMEDIATE_DRAW);	
		    		PlotWaveform( panel, FREQ_PANEL_GRAPH_SPECTRUM_DATA, spectrul_rezultat, points_per_second/4 ,VAL_DOUBLE, 1.0, 0.0, 0.0, df,
		                                    VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID,  VAL_CONNECTED_POINTS, VAL_DK_GREEN);
					if(finishh+N<npoints_){
						startt+=N;
						finishh+=N;
					}
					else{
						startt=0;finishh=N;
					}
					
					Timer();
				}*/
			break;
				
		}
	
	return 0;
}


int CVICALLBACK StartCb (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			startt=0;finishh=N;	
			 puncte_nemodificate=0;
			
			//SuspendTimerCallbacks();
			 
			 
			filteredSignal = (double *) calloc((ncoef+npoints_-1), sizeof(double));
			delta=1/sampleRate_;
			switch(filter_type){
				case FIR: 
					
					switch(FirType){
						case FILTER_LPF:
											
							EquiRpl_LPF (sampleRate_, f1, f2, ncoef, FIRcoef, &delta);
							Convolve(FIRcoef, ncoef, waveData_ ,npoints_, filteredSignal);
							break;
						case FILTER_BPF:
							EquiRpl_BPF(sampleRate_, f1, f2, f3, f4, ncoef, FIRcoef, &delta);
							Convolve(waveData_, npoints_, FIRcoef, ncoef, filteredSignal);
							break;
						case FILTER_BSF:
							EquiRpl_BSF(sampleRate_, f1, f2, f3, f4, ncoef, FIR_Coef, &delta);
							Convolve(waveData_, npoints_, FIRcoef, ncoef, filteredSignal);							
							break;
						case FILTER_HPF:
							EquiRpl_HPF(sampleRate_, f1, f2, ncoef, FIR_Coef, &delta);
					        Convolve(waveData_, npoints_, FIR_Coef, ncoef, filteredSignal);
							break;
					}
					break;
				case CH_H:
					SetCtrlVal(panel, FREQ_PANEL_CURRENTFILTER, "Chebyshev I trece sus");
					//CHEBYSHEV I trece sus
					Ch_HPF(waveData_, npoints_, sampleRate_, fpass, 0.1, 3, filteredSignal);
					break;
			}
			DeleteGraphPlot (panel, FREQ_PANEL_GRAPH_FILTRED_FFT, -1, VAL_IMMEDIATE_DRAW);
			PlotY(panel, FREQ_PANEL_GRAPH_FILTRED_FFT, filteredSignal, ncoef+npoints_-1, VAL_DOUBLE,
				  VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
			
			
			//ResumeTimerCallbacks();
			
			points_per_second=N;
			if(inputSecond!=NULL){
				free(inputSecond);	
			}
			inputSecond= (double *) malloc((points_per_second+2)*sizeof(double));	
			arrayCalc(waveData_,finishh,startt);
			switch(window_type){
					case 0:
						//MessagePopup("RECTANGLE", "");
						ScaledWindowEx (inputSecond, points_per_second, RECTANGLE, 0, &wndConst);
						break;
					case 1:
						//MessagePopup("BLKHARRIS", "");
						ScaledWindowEx (inputSecond, points_per_second, BLKHARRIS, 0, &wndConst);	
						break;
					}
					autoSpectrum=(double *) calloc(points_per_second, sizeof(double));

					switch(N){
						case 1024:
							//MessagePopup("1024", "");
							AutoPowerSpectrum (inputSecond, POWER_2_10, 1.0/points_per_second, autoSpectrum, &df);
							break;
						case 2048:
							//MessagePopup("2048", "");
							AutoPowerSpectrum (inputSecond, POWER_2_11, 1.0/points_per_second, autoSpectrum, &df);
							break;
						case 4096:
							//MessagePopup("4096", "");
							AutoPowerSpectrum (inputSecond, POWER_2_12, 1.0/points_per_second, autoSpectrum, &df);
							break;
						default:
							MessagePopup("ERROR", "NU ESTE VALIDA OPTIUNEA");
					}
					
					
					
					PowerFrequencyEstimate (autoSpectrum, points_per_second, -1.0, wndConst, df, 7, &frequencyPeak, &powerPeak);
					sprintf(str, "%.2f", frequencyPeak); 
					SetCtrlVal(panel, FREQ_PANEL_FREQPEAK,str);
					sprintf(str1, "%.2f", powerPeak);
					SetCtrlVal(panel, FREQ_PANEL_POWPEAK,str1);
					
					char unitString[32]={0};
					spectrul_rezultat = (double *) calloc(points_per_second, sizeof(double));
					SpectrumUnitConversion (autoSpectrum, points_per_second, SPECTRUM_POWER, SCALING_MODE_LINEAR, DISPLAY_UNIT_VRMS, 
											1.0, wndConst, spectrul_rezultat, unitString);
					
					
					DeleteGraphPlot (panel, FREQ_PANEL_GRAPH_SPECTRUM_DATA, -1, VAL_IMMEDIATE_DRAW);	
		    		PlotWaveform( panel, FREQ_PANEL_GRAPH_SPECTRUM_DATA, spectrul_rezultat, points_per_second/4 ,VAL_DOUBLE, 1.0, 0.0, 0.0, df,
		                                    VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID,  VAL_CONNECTED_POINTS, VAL_DK_GREEN);
			StartPressed=1;
			break;
	}
	return 0;
}

int CVICALLBACK SaveSpectrumCB (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
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
			sprintf(path, "Spectrum_%d.%d.%d_%d-%d-%d.jpeg", year, month, day, hour, minute, second);
			
			
			GetCtrlDisplayBitmap(panel, FREQ_PANEL_GRAPH_SPECTRUM_DATA, 1, &bitmapID);
			SaveBitmapToJPEGFile(bitmapID, path, JPEG_PROGRESSIVE, 100);
			DiscardBitmap(bitmapID);
			
			GetCtrlDisplayBitmap(panel, FREQ_PANEL_GRAPH_FILTRED_FFT, 1, &bitmapID);
			SaveBitmapToJPEGFile(bitmapID, path, JPEG_PROGRESSIVE, 100);
			DiscardBitmap(bitmapID);
			
			MessagePopup("Done", "Imaginile au fost salvate!");
			break;
	}
	return 0;
}




int CVICALLBACK FiltruV2CB (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, FREQ_PANEL_FILTRUV2, &filter_type);
			switch(filter_type){
				case FIR:
					SetCtrlVal(panel, FREQ_PANEL_CURRENTFILTER, "FIR EquiRpl");
					break;
				case CH_H:
					SetCtrlVal(panel, FREQ_PANEL_CURRENTFILTER, "Chebyshev I trece sus");
					break;
			}
			//printf("tipul filtrului: %d\n", filter_type);
			break;
	}
	return 0;
}

int CVICALLBACK WindowV2CB (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, FREQ_PANEL_WINDOWV2, &window_type);
			//printf("tipul ferestrei: %d\n", window_type);
			break;
	}
	return 0;
}

int CVICALLBACK FirEquiRplCB (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, FREQ_PANEL_FIREQUIRPL, &FirType);
			//printf("tipul FIR: %d\n", FirType);
			break;
	}
	return 0;
}



int CVICALLBACK PuncteCB (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			str2=(char *) calloc(30, sizeof(char));
			GetCtrlVal(panel, FREQ_PANEL_PCT, str2);
			N=string_to_int(str2);
			puncte_nemodificate=0;
			SuspendTimerCallbacks();
			break;
	}
	return 0;
}
