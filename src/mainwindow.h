#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <random>

#include <QChartView>
#include <QDebug>
#include <QGraphicsLayout>
#include <QMainWindow>
#include <QMargins>
#include <QPainter>
#include <QSpinBox>
#include <QTimer>
#include <QValueAxis>

#include "pop.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;
  void controls_visibility_changed();
  void show_hide_controls();
  void update_speed();
  void update_ngen();
  void update_npop();
  void update_popsize();
  void update_u();
  void update_v();
  void update_p();
  void update_wAA();
  void update_wAa();
  void update_waa();
  void update_continue_btn_state();
  void prepare_pops();
  void prepare_series();
  void update_force_parameters();
  void continue_sim();
  void remove_all_pops();
  void run_stop_sim();
  void update_sim();

private:
  Ui::MainWindow *ui;
  std::mt19937 *_rgenptr;
  QtCharts::QChartView *_cv;
  int _gen;
  int _npop;
  QVector<FinitePop> _pops;
  InfinitePop *_expectation;
  unsigned int _popsize;
  int _ngen;
  double _u;
  double _v;
  double _p;
  double _wAA;
  double _wAa;
  double _waa;
  QtCharts::QValueAxis *_xax;
  QtCharts::QValueAxis *_yax;
  QtCharts::QChart *_chart;
  QTimer *_timer;
  bool _new_run;
};

#endif // MAINWINDOW_H

#include "./ui_mainwindow.h"