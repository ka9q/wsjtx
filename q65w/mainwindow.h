#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGui>
#include <QtWidgets>
#include <QPointer>
#include <QScopedPointer>
#include <QLabel>
#include <QDateTime>
#include <QHash>
#include "getfile.h"
#include "soundin.h"
#include "signalmeter.h"
#include "commons.h"
#include "sleep.h"
#include <QtConcurrent/QtConcurrent>

#define NFFT 32768
#define NSMAX 5760000

//--------------------------------------------------------------- MainWindow
namespace Ui {
  class MainWindow;
}

class QTimer;
class Astro;
class WideGraph;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  bool m_network;

public slots:
  void showSoundInError(const QString& errorMsg);
  void showStatusMessage(const QString& statusMsg);
  void dataSink(int k);
  void diskDat();
  void diskWriteFinished();
  void decoderFinished();
  void freezeDecode(int n);
  void guiUpdate();

private:
  virtual void keyPressEvent (QKeyEvent *) override;
  virtual bool eventFilter (QObject *, QEvent *) override;
  virtual void closeEvent (QCloseEvent *) override;

private slots:
  void on_monitorButton_clicked();
  void on_actionExit_triggered();
  void on_actionAbout_triggered();
  void on_actionLinrad_triggered();
  void on_actionCuteSDR_triggered();
  void on_tolSpinBox_valueChanged(int arg1);
  void on_actionAstro_Data_triggered();
  void on_stopButton_clicked();
  void on_actionWide_Waterfall_triggered();
  void on_actionOpen_triggered();
  void on_actionOpen_next_in_directory_triggered();
  void on_actionDecode_remaining_files_in_directory_triggered();
  void on_actionDelete_all_iq_files_in_SaveDir_triggered();
  void on_actionNo_Deep_Search_triggered();
  void on_actionNormal_Deep_Search_triggered();
  void on_actionAggressive_Deep_Search_triggered();
  void on_actionNone_triggered();
  void on_actionSave_all_triggered();
  void on_DecodeButton_clicked();
  void decode();
  void decodeBusy(bool b);
  void on_EraseButton_clicked();
  void on_lookupButton_clicked();
  void on_addButton_clicked();
  void on_dxCallEntry_textChanged(const QString &arg1);
  void on_dxGridEntry_textChanged(const QString &arg1);
  void bumpDF(int n);
  void on_actionSettings_triggered();
  void on_NBcheckBox_toggled(bool checked);
  void on_NBslider_valueChanged(int value);
  void on_actionAFMHot_triggered();
  void on_actionBlue_triggered();
  void on_actionQ65A_triggered();
  void on_actionQ65B_triggered();
  void on_actionQ65C_triggered();
  void on_actionQ65D_triggered();
  void on_actionQ65E_triggered();

private:
  Ui::MainWindow *ui;
  QString m_appDir;
  QString m_settings_filename;
  QScopedPointer<Astro> m_astro_window;
  QScopedPointer<WideGraph> m_wide_graph_window;
  QPointer<QTimer> m_gui_timer;
  qint64  m_msErase;
  qint32  m_idInt;
  qint32  m_waterfallAvg;
  qint32  m_DF;
  qint32  m_tol;
  qint32  m_QSOfreq0;
  qint32  m_astroFont;
  qint32  m_timeout;
  qint32  m_dPhi;
  qint32  m_fCal;
  qint32  m_txFreq;
  qint32  m_setftx;
  qint32  m_ndepth;
  qint32  m_sec0;
  qint32  m_nutc0;
  qint32  m_nrx;
  qint32  m_hsym0;
  qint32  m_paInDevice;
  qint32  m_udpPort;
  qint32  m_NBslider;
  qint32  m_nsum;
  qint32  m_nsave;
  qint32  m_TRperiod;
  qint32  m_modeQ65;
  qint32  m_RxState;
  qint32  m_dB;
  qint32  m_fetched=0;

  double  m_fAdd;
  double  m_xavg;

  bool    m_monitoring;
  bool    m_diskData;
  bool    m_loopall;
  bool    m_decoderBusy;
  bool    m_restart;
  bool    m_call3Modified;
  bool    m_startAnother;
  bool    m_saveAll;
  bool    m_onlyEME;
  bool    m_kb8rq;
  bool    m_NB;
  bool    m_fs96000;

  float   m_gainx;
  float   m_gainy;
  float   m_phasex;
  float   m_phasey;
  float   m_pctZap;

  QRect   m_wideGraphGeom;

  QLabel* lab1;                            // labels in status bar
  QLabel* lab4;
  QLabel* lab5;
  QLabel* lab6;
  QLabel* lab7;                   //Why still needed?

  QMessageBox msgBox0;

  QFuture<void>* future1;
  QFuture<void>* future2;
  QFutureWatcher<void>* watcher1;
  QFutureWatcher<void>* watcher2;

  QFutureWatcher<void> watcher3;     //For decoder

  QString m_path;
  QString m_pbdecoding_style1;
  QString m_pbmonitor_style;
  QString m_pbAutoOn_style;
  QString m_myCall;
  QString m_myGrid;
  QString m_hisCall;
  QString m_hisGrid;
  QString m_saveDir;
  QString m_azelDir;
  QString m_dxccPfx;
  QString m_palette;
  QString m_dateTime;
  QString m_mode;
  QString m_colors;                     //Why still needed?
  QString m_editorCommand;              //Why still needed?
  QString m_modeTx;                     //Why still needed?

  QHash<QString,bool> m_worked;

  SignalMeter *xSignalMeter;
  SignalMeter *ySignalMeter;


  SoundInThread soundInThread;             //Instantiate the audio threads

  //---------------------------------------------------- private functions
  void readSettings();
  void writeSettings();
  void createStatusBar();
  void updateStatusBar();
  void msgBox(QString t);
  void lookup();
  bool isGrid4(QString g);
};

extern void getfile(QString fname, bool xpol, int idInt);
extern void savetf2(QString fname, bool xpol);
extern int killbyname(const char* progName);

extern "C" {
//----------------------------------------------------- C and Fortran routines
  void symspec_(int* k, int* ndiskdat, int* nb, int* m_NBslider, int* nfsample,
                float* px, float s[], int* nkhz, int* nhsym,
                int* nzap, float* slimit, uchar lstrong[]);

  void astrosub00_ (int* nyear, int* month, int* nday, double* uth, int* nfreq,
                    const char* mygrid, int* ndop00, int len1);

  void q65c_(int* itimer);
  }

#endif // MAINWINDOW_H
