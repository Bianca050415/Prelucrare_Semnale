/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  FREQ_PANEL                       1       /* callback function: OnFreqPanelCB */
#define  FREQ_PANEL_SWITCH                2       /* control type: binary, callback function: SwitchCB */
#define  FREQ_PANEL_GRAPH_FILTRED_FFT     3       /* control type: graph, callback function: (none) */
#define  FREQ_PANEL_GRAPH_SPECTRUM_DATA   4       /* control type: graph, callback function: (none) */
#define  FREQ_PANEL_START                 5       /* control type: command, callback function: StartCb */
#define  FREQ_PANEL_POWPEAK               6       /* control type: string, callback function: (none) */
#define  FREQ_PANEL_FREQPEAK              7       /* control type: string, callback function: (none) */
#define  FREQ_PANEL_SAVE                  8       /* control type: command, callback function: SaveSpectrumCB */
#define  FREQ_PANEL_PCT                   9       /* control type: string, callback function: PuncteCB */
#define  FREQ_PANEL_WINDOWV2              10      /* control type: textButton, callback function: WindowV2CB */
#define  FREQ_PANEL_FILTRUV2              11      /* control type: textButton, callback function: FiltruV2CB */
#define  FREQ_PANEL_FIREQUIRPL            12      /* control type: slide, callback function: FirEquiRplCB */
#define  FREQ_PANEL_CURRENTFILTER         13      /* control type: string, callback function: (none) */
#define  FREQ_PANEL_TEXTMSG               14      /* control type: textMsg, callback function: (none) */
#define  FREQ_PANEL_ACHIZITIE             15      /* control type: command, callback function: AchizitieCB */
#define  FREQ_PANEL_TIMER                 16      /* control type: timer, callback function: TimerCB */

#define  PANEL                            2       /* callback function: panelCB */
#define  PANEL_ANVELOPA                   2       /* control type: graph, callback function: AnvelopaCB */
#define  PANEL_GRAPH_FILTERED_DATA        3       /* control type: graph, callback function: FilteredDataGraphCB */
#define  PANEL_GRAPH_RAW_DATA             4       /* control type: graph, callback function: RawDataGraphCB */
#define  PANEL_COMMANDBUTTON_4            5       /* control type: command, callback function: LoadCB */
#define  PANEL_APPLY                      6       /* control type: command, callback function: ApplCB */
#define  PANEL_SAVE                       7       /* control type: command, callback function: SaveCB */
#define  PANEL_COMMANDBUTTON_2            8       /* control type: command, callback function: NextCB */
#define  PANEL_COMMANDBUTTON              9       /* control type: command, callback function: PrevCB */
#define  PANEL_NR_ZERO                    10      /* control type: string, callback function: NrTreceriZeroCB */
#define  PANEL_KURTOSIS                   11      /* control type: string, callback function: KurtosisCB */
#define  PANEL_SKEWNESS                   12      /* control type: string, callback function: SkewnessCB */
#define  PANEL_MEDIANA                    13      /* control type: string, callback function: MedianaCB */
#define  PANEL_MAXIM                      14      /* control type: string, callback function: MaxCB */
#define  PANEL_MINIM                      15      /* control type: string, callback function: MinCB */
#define  PANEL_DISPERSIE                  16      /* control type: string, callback function: DispCB */
#define  PANEL_MEAN                       17      /* control type: string, callback function: MeanCB */
#define  PANEL_ALPHA                      18      /* control type: string, callback function: AlphaCB */
#define  PANEL_WINDOW_SIZE                19      /* control type: ring, callback function: WindowSizeCB */
#define  PANEL_FILTRU                     20      /* control type: ring, callback function: FilterCB */
#define  PANEL_STOP                       21      /* control type: string, callback function: StartStopCB */
#define  PANEL_START                      22      /* control type: string, callback function: StartStopCB */
#define  PANEL_SWITCH                     23      /* control type: binary, callback function: SwitchCB */
#define  PANEL_TEXTMSG                    24      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AchizitieCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AlphaCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AnvelopaCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ApplCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DispCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK FilterCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK FilteredDataGraphCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK FiltruV2CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK FirEquiRplCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK KurtosisCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK LoadCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MaxCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MeanCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MedianaCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MinCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK NextCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK NrTreceriZeroCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnFreqPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PrevCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PuncteCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RawDataGraphCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveSpectrumCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SkewnessCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartCb(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartStopCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SwitchCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TimerCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK WindowSizeCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK WindowV2CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif