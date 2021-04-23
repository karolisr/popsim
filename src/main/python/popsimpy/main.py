from typing import cast

from PyQt5.QtChart import QChart
from PyQt5.QtChart import QChartView
from PyQt5.QtChart import QValueAxis
from PyQt5.QtCore import QMargins
from PyQt5.QtCore import QTimer
from PyQt5.QtGui import QColor
from PyQt5.QtGui import QPainter
from PyQt5.QtGui import QPen
from PyQt5.QtWidgets import QMainWindow
from PyQt5.QtWidgets import QGraphicsView

from popsimpy import PYQT_SIGNAL
from popsimpy.sim import Pop
from popsimpy.sim import Expectation
from popsimpy.ui.main_window import Ui_MainWindow


def interval(val: int) -> int:
    assert 0 <= val <= 4
    rates = [272, 136, 68, 34, 17]
    return rates[val]


class MainWindow(QMainWindow, Ui_MainWindow):

    def __init__(self, parent=None):
        super().__init__(parent)
        self.setupUi(self)

        # Other
        self.gen = 0
        self.npop = self.npop_spinbox.value()
        self.pops = []
        self.expectation = None
        self.popsize = self.popsize_spinbox.value()
        self.ngen = self.ngen_spinbox.value()
        self.u = self.u_spinbox.value()
        self.v = self.v_spinbox.value()
        self.p = self.p_spinbox.value()
        self.wAA = self.wAA_spinbox.value()
        self.wAa = self.wAa_spinbox.value()
        self.waa = self.waa_spinbox.value()

        # QMainWindow
        self.setWindowTitle('PopSim')

        # QChartView
        self.cv = QChartView()
        self.cv.setRenderHint(QPainter.Antialiasing, True)
        # self.cv.setOptimizationFlag(QGraphicsView.OptimizationFlag(2), False)
        # self.cv.setOptimizationFlag(QGraphicsView.OptimizationFlag(4), False)
        # self.cv.setOptimizationFlag(QGraphicsView.OptimizationFlag(8), False)
        self.verticalLayout.replaceWidget(self.tempWidget, self.cv)

        # Initial x, y axes
        self.xax = QValueAxis()
        # self.xax.setTitleText('Generation')
        self.xax.setLabelFormat('%d')
        self.xax.setRange(0, self.ngen)

        self.yax = QValueAxis()
        # self.yax.setTitleText('p')
        self.yax.setLabelFormat('%0.2f')
        self.yax.setRange(0, 1.0)

        # QChart
        self.chart = self.cv.chart()
        self.chart = cast(QChart, self.chart)
        #                              l  t  r  b
        self.chart.setMargins(QMargins(5, 5, 5, 5))
        self.chart.setContentsMargins(0, 0, 0, 0)
        self.chart.layout().setContentsMargins(0, 0, 0, 0)
        self.chart.setBackgroundRoundness(0)
        self.chart.legend().hide()
        self.chart.setAxisX(self.xax)
        self.chart.setAxisY(self.yax)
        # self.chart.setTheme(0)

        # QTimer
        self.timer = QTimer()
        self.timer.timeout = cast(PYQT_SIGNAL, self.timer.timeout)
        self.timer.timeout.connect(self.update_sim)
        self.update_speed()
        # self.timer.setInterval(self.speed_dial.value())

        # Connections
        self.run_stop_btn.clicked.connect(self.run_stop_sim)
        self.continue_btn.clicked.connect(self.continue_sim)
        self.speed_dial.valueChanged.connect(self.update_speed)
        self.ngen_spinbox.valueChanged.connect(self.update_ngen)
        self.npop_spinbox.valueChanged.connect(self.update_npop)
        self.popsize_spinbox.valueChanged.connect(self.update_popsize)
        self.u_spinbox.valueChanged.connect(self.update_u)
        self.v_spinbox.valueChanged.connect(self.update_v)
        self.p_spinbox.valueChanged.connect(self.update_p)
        self.wAA_spinbox.valueChanged.connect(self.update_wAA)
        self.wAa_spinbox.valueChanged.connect(self.update_wAa)
        self.waa_spinbox.valueChanged.connect(self.update_waa)

        self.continue_btn.setDisabled(True)
        self.run_stop_btn.setFocus(True)

        self.new_run = True

    def update_speed(self):
        self.timer.setInterval(interval(self.speed_dial.value()))

    def update_ngen(self):
        self.ngen = self.ngen_spinbox.value()
        self.xax.setRange(0, self.ngen)
        self.update_continue_btn_state()

    def update_npop(self):
        self.npop = self.npop_spinbox.value()

    def update_popsize(self):
        self.popsize = self.popsize_spinbox.value()

    def update_u(self):
        self.u = self.u_spinbox.value()

    def update_v(self):
        self.v = self.v_spinbox.value()

    def update_p(self):
        self.p = self.p_spinbox.value()

    def update_wAA(self):
        self.wAA = self.wAA_spinbox.value()

    def update_wAa(self):
        self.wAa = self.wAa_spinbox.value()

    def update_waa(self):
        self.waa = self.waa_spinbox.value()

    def update_continue_btn_state(self):
        if len(self.pops) > 0 and self.gen < self.ngen:
            self.new_run_frame.setEnabled(True)
            self.continue_btn.setEnabled(True)
            self.continue_btn.setFocus()
        else:
            self.continue_btn.setEnabled(False)
            self.new_run_frame.setEnabled(False)

        if self.new_run is True:
            self.continue_btn.setEnabled(False)
            self.new_run_frame.setEnabled(True)

    def prepare_pops(self):
        pops = []
        for i in range(self.npop):
            pop = Pop(self.popsize, self.p, self.u, self.v,
                      self.wAA, self.wAa, self.waa)
            pops.append(pop)
        self.pops = pops
        self.expectation = Expectation(self.p, self.u, self.v,
                                       self.wAA, self.wAa, self.waa)

    def prepare_series(self):
        pen = QPen(QColor(0, 0, 0), 1)
        pen_exp = QPen(QColor(255, 0, 0), 5)
        for pop in self.pops:
            pop.history.setPen(pen)
            self.chart.addSeries(pop.history)
            self.chart.setAxisX(self.xax, pop.history)
            self.chart.setAxisY(self.yax, pop.history)
            pop.history.setUseOpenGL(True)

        self.expectation.history.setPen(pen_exp)
        self.chart.addSeries(self.expectation.history)
        self.chart.setAxisX(self.xax, self.expectation.history)
        self.chart.setAxisY(self.yax, self.expectation.history)
        self.expectation.history.setUseOpenGL(True)

    def update_force_parameters(self):
        for pop in self.pops:
            pop.size = self.popsize
            pop.u = self.u
            pop.v = self.v
            pop.wAA = self.wAA
            pop.wAa = self.wAa
            pop.waa = self.waa

        self.expectation.u = self.u
        self.expectation.v = self.v
        self.expectation.wAA = self.wAA
        self.expectation.wAa = self.wAa
        self.expectation.waa = self.waa

    def continue_sim(self):
        self.new_run_frame.setDisabled(True)
        self.ngen_spinbox.setDisabled(True)
        self.continue_btn.setDisabled(True)
        self.run_stop_btn.setFocus()
        self.run_stop_btn.setText('Stop')
        self.timer.start()

    def remove_all_pops(self):
        if self.expectation is not None and \
                self.expectation.history in self.chart.series():
            self.expectation.history.clear()
            self.expectation._history = None

        for pop in self.pops:
            pop.history.clear()
            pop._history = None

        self.expectation = None
        self.pops.clear()
        self.chart.removeAllSeries()

    def run_stop_sim(self):
        if self.timer.isActive():
            self.timer.stop()
            self.npop_spinbox.setEnabled(False)
            self.p_spinbox.setEnabled(False)
            self.ngen_spinbox.setEnabled(True)
            self.run_stop_btn.setFocus()
            self.update_continue_btn_state()
            self.run_stop_btn.setText('New Run')

        elif self.new_run is False:
            self.gen = 0
            self.gen_lcd.display(self.gen)
            self.continue_btn.setDisabled(True)
            self.run_stop_btn.setFocus()
            self.run_stop_btn.setText('Run')
            self.new_run_frame.setEnabled(True)
            self.npop_spinbox.setEnabled(True)
            self.p_spinbox.setEnabled(True)
            self.new_run = True
            self.remove_all_pops()

        else:
            self.new_run = False
            self.run_stop_btn.setFocus()
            self.run_stop_btn.setText('Stop')
            self.ngen_spinbox.setDisabled(True)
            self.new_run_frame.setDisabled(True)
            self.ngen = self.ngen_spinbox.value()
            self.prepare_pops()
            self.prepare_series()
            self.timer.start()

    def update_sim(self):
        self.gen += 1
        self.gen_lcd.display(self.gen)

        self.update_force_parameters()

        for pop in self.pops:
            pop.next_gen()

        self.expectation.next_gen()

        if self.gen >= self.ngen:
            self.run_stop_sim()

    def closeEvent(self, event):
        self.timer.timeout.disconnect(self.update_sim)
        self.timer.stop()
        self.remove_all_pops()
        super(QMainWindow, self).closeEvent(event)
