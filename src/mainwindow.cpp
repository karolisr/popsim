#include "mainwindow.h"

MainWindow::~MainWindow() {
  remove_all_pops();
  delete _rgenptr;
  delete _timer;
  delete _xax;
  delete _yax;
  delete _cv;
  delete ui;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  std::random_device rdev;
  _rgenptr = new std::mt19937(rdev());

  _new_run = true;
  _gen = 0;
  _npop = ui->npop_spinbox->value();
  _pops = QVector<FinitePop>();
  _expectation = nullptr;
  _popsize = ui->popsize_spinbox->value();
  _ngen = ui->ngen_spinbox->value();
  _u = ui->u_spinbox->value();
  _v = ui->v_spinbox->value();
  _p = ui->p_spinbox->value();
  _wAA = ui->wAA_spinbox->value();
  _wAa = ui->wAa_spinbox->value();
  _waa = ui->waa_spinbox->value();

  setWindowTitle("PopSim");

  _cv = new QtCharts::QChartView;
  _cv->setRenderHint(QPainter::Antialiasing, true);
  ui->verticalLayout->replaceWidget(ui->tempWidget, _cv);

  _xax = new QtCharts::QValueAxis;
  _xax->setLabelFormat("%d");
  _xax->setRange(0, _ngen);

  _yax = new QtCharts::QValueAxis;
  _yax->setLabelFormat("%0.2f");
  _yax->setRange(0, 1.0);

  _chart = _cv->chart();
  _chart->setMargins(QMargins(5, 5, 5, 5));
  _chart->setContentsMargins(0, 0, 0, 0);
  _chart->layout()->setContentsMargins(0, 0, 0, 0);
  _chart->setBackgroundRoundness(0);
  _chart->legend()->hide();
  _chart->addAxis(_xax, Qt::AlignBottom);
  _chart->addAxis(_yax, Qt::AlignLeft);

  _timer = new QTimer();
  update_speed();

  QObject::connect(_timer, &QTimer::timeout, this, &MainWindow::update_sim);

  QObject::connect(ui->run_stop_btn, &QPushButton::clicked, this,
                   &MainWindow::run_stop_sim);

  QObject::connect(ui->continue_btn, &QPushButton::clicked, this,
                   &MainWindow::continue_sim);

  QObject::connect(ui->speed_dial, &QDial::valueChanged, this,
                   &MainWindow::update_speed);

  QObject::connect(ui->ngen_spinbox,
                   QOverload<int>::of(&QSpinBox::valueChanged), this,
                   &MainWindow::update_ngen);

  QObject::connect(ui->npop_spinbox,
                   QOverload<int>::of(&QSpinBox::valueChanged), this,
                   &MainWindow::update_npop);

  QObject::connect(ui->popsize_spinbox,
                   QOverload<int>::of(&QSpinBox::valueChanged), this,
                   &MainWindow::update_popsize);

  QObject::connect(ui->u_spinbox,
                   QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
                   &MainWindow::update_u);

  QObject::connect(ui->v_spinbox,
                   QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
                   &MainWindow::update_v);

  QObject::connect(ui->p_spinbox,
                   QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
                   &MainWindow::update_p);

  QObject::connect(ui->wAA_spinbox,
                   QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
                   &MainWindow::update_wAA);

  QObject::connect(ui->wAa_spinbox,
                   QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
                   &MainWindow::update_wAa);

  QObject::connect(ui->waa_spinbox,
                   QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
                   &MainWindow::update_waa);

  QObject::connect(ui->actionControls, &QAction::triggered, this,
                   &MainWindow::show_hide_controls);

  QObject::connect(ui->ctrlDockWidget, &QDockWidget::visibilityChanged, this,
                   &MainWindow::controls_visibility_changed);

  ui->continue_btn->setDisabled(true);
  ui->run_stop_btn->setFocus();
}

void MainWindow::controls_visibility_changed() {
  if (ui->ctrlDockWidget->isHidden()) {
    ui->actionControls->setChecked(false);
  } else {
    ui->actionControls->setChecked(true);
  }
}

void MainWindow::show_hide_controls() {
  if (ui->ctrlDockWidget->isHidden()) {
    ui->ctrlDockWidget->show();
  } else {
    ui->ctrlDockWidget->hide();
  }
}

void MainWindow::update_speed() {
  int interval[5] = {272, 136, 68, 34, 17};
  _timer->setInterval(interval[ui->speed_dial->value()]);
}

void MainWindow::update_ngen() {
  _ngen = ui->ngen_spinbox->value();
  _xax->setRange(0, _ngen);
  update_continue_btn_state();
}

void MainWindow::update_npop() { _npop = ui->npop_spinbox->value(); }
void MainWindow::update_popsize() { _popsize = ui->popsize_spinbox->value(); }
void MainWindow::update_u() { _u = ui->u_spinbox->value(); }
void MainWindow::update_v() { _v = ui->v_spinbox->value(); }
void MainWindow::update_p() { _p = ui->p_spinbox->value(); }
void MainWindow::update_wAA() { _wAA = ui->wAA_spinbox->value(); }
void MainWindow::update_wAa() { _wAa = ui->wAa_spinbox->value(); }
void MainWindow::update_waa() { _waa = ui->waa_spinbox->value(); }

void MainWindow::update_continue_btn_state() {
  if (_pops.count() > 0 && (_gen < _ngen)) {
    ui->new_run_frame->setEnabled(true);
    ui->continue_btn->setEnabled(true);
    ui->continue_btn->setFocus();
  } else {
    ui->continue_btn->setEnabled(false);
    ui->new_run_frame->setEnabled(false);
  }
  if (_new_run) {
    ui->continue_btn->setEnabled(false);
    ui->new_run_frame->setEnabled(true);
  }
}

void MainWindow::prepare_pops() {
  _pops.clear();
  for (int i = 0; i < _npop; i++) {
    FinitePop pop = FinitePop(_rgenptr, _popsize, _p, _u, _v, _wAA, _wAa, _waa);
    _pops.append(pop);
  }
  _expectation = new InfinitePop(_p, _u, _v, _wAA, _wAa, _waa);
}

void MainWindow::prepare_series() {
  QPen pen = QPen(QColor(0, 0, 0), 1);
  for (int i = 0; i < _pops.count(); i++) {
    FinitePop &pop = _pops[i];
    QLineSeries *s = pop.history();
    _chart->addSeries(s);
    s->setPen(pen);
    s->attachAxis(_xax);
    s->attachAxis(_yax);
    s->setUseOpenGL(true);
  }

  QPen pen_exp = QPen(QColor(255, 0, 0), 5);
  QLineSeries *s = _expectation->history();
  _chart->addSeries(s);
  s->setPen(pen_exp);
  s->attachAxis(_xax);
  s->attachAxis(_yax);
  s->setUseOpenGL(true);
}

void MainWindow::update_force_parameters() {
  for (int i = 0; i < _pops.count(); i++) {
    FinitePop &pop = _pops[i];
    pop.update_parameters(_popsize, _u, _v, _wAA, _wAa, _waa);
  }

  _expectation->update_parameters(_u, _v, _wAA, _wAa, _waa);
}

void MainWindow::continue_sim() {
  ui->new_run_frame->setDisabled(true);
  ui->ngen_spinbox->setDisabled(true);
  ui->continue_btn->setDisabled(true);
  ui->run_stop_btn->setFocus();
  ui->run_stop_btn->setText("Stop");
  _timer->start();
}

void MainWindow::remove_all_pops() {
  for (int i = 0; i < _pops.count(); i++) {
    FinitePop &pop = _pops[i];
    pop.history()->clear();
  }
  _chart->removeAllSeries();
  _pops.clear();
  delete _expectation;
  _expectation = nullptr;
  delete _expectation;
  _expectation = nullptr;
}

void MainWindow::run_stop_sim() {
  if (_timer->isActive()) {
    _timer->stop();
    ui->npop_spinbox->setEnabled(false);
    ui->p_spinbox->setEnabled(false);
    ui->ngen_spinbox->setEnabled(true);
    ui->run_stop_btn->setFocus();
    update_continue_btn_state();
    ui->run_stop_btn->setText("New Run");
  } else if (!_new_run) {
    _gen = 0;
    ui->gen_lcd->display(_gen);
    ui->continue_btn->setDisabled(true);
    ui->run_stop_btn->setFocus();
    ui->run_stop_btn->setText("Run");
    ui->new_run_frame->setEnabled(true);
    ui->npop_spinbox->setEnabled(true);
    ui->p_spinbox->setEnabled(true);
    _new_run = true;
    remove_all_pops();
  } else {
    _new_run = false;
    ui->run_stop_btn->setFocus();
    ui->run_stop_btn->setText("Stop");
    ui->ngen_spinbox->setDisabled(true);
    ui->new_run_frame->setDisabled(true);
    _ngen = ui->ngen_spinbox->value();
    prepare_pops();
    prepare_series();
    _timer->start();
  }
}

void MainWindow::update_sim() {
  _gen += 1;
  ui->gen_lcd->display(_gen);

  update_force_parameters();

  for (int i = 0; i < _pops.count(); i++) {
    FinitePop &pop = _pops[i];
    pop.next_gen();
  }

  _expectation->next_gen();

  if (_gen >= _ngen) {
    run_stop_sim();
  }
}
