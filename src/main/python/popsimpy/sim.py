import ctypes

from PyQt5.QtChart import QLineSeries

# Needed here to locate libRmath
from fbs_runtime.application_context import get_application_context
from fbs_runtime.application_context.PyQt5 import ApplicationContext

# Load libRmath
APPCTXT = get_application_context(ApplicationContext)
libRmath_path = APPCTXT.get_resource('libRmath.dylib')
LIBRMATH = ctypes.CDLL(libRmath_path)

RBINOM_R = LIBRMATH.rbinom
RBINOM_R.argtypes = [ctypes.c_double, ctypes.c_double]
RBINOM_R.restype = ctypes.c_double
rbinom = RBINOM_R


def next_p(p: float, u: float = 0, v: float = 0,
           wAA: float = 1, wAa: float = 1, waa: float = 1):

    pu = p * u
    pv = (1 - p) * v
    puv = p - pu + pv

    puv_sq = puv ** 2
    one_minus_puv = 1 - puv

    wbar = puv_sq * wAA + 2 * puv * one_minus_puv * wAa + \
        (one_minus_puv ** 2) * waa

    puvw = (puv_sq * wAA + puv * one_minus_puv * wAa) / wbar

    return puvw


def next_p_finite(size: int, p: float, u: float = 0, v: float = 0,
                  wAA: float = 1, wAa: float = 1, waa: float = 1):

    puvw = next_p(p, u, v, wAA, wAa, waa)
    allele_count = 2 * size

    return rbinom(allele_count, puvw) / allele_count


class Pop:
    _size: int
    _p: float
    _u: float
    _v: float
    _wAA: float
    _wAa: float
    _waa: float
    _ngen: int
    _history: QLineSeries

    def __init__(self, size: int, p: float, u: float = 0, v: float = 0,
                 wAA: float = 1, wAa: float = 1, waa: float = 1) -> None:

        self._size = size
        self._p = p
        self._u = u
        self._v = v
        self._wAA = wAA
        self._wAa = wAa
        self._waa = waa
        self._ngen = 0

        self._history = QLineSeries()
        self._history.append(self.ngen, self.p)

    @property
    def size(self) -> int:
        return self._size

    @size.setter
    def size(self, value) -> None:
        self._size = value

    @property
    def p(self) -> float:
        return self._p

    @property
    def u(self) -> float:
        return self._u

    @u.setter
    def u(self, value) -> None:
        self._u = value

    @property
    def v(self) -> float:
        return self._v

    @v.setter
    def v(self, value) -> None:
        self._v = value

    @property
    def wAA(self) -> float:
        return self._wAA

    @wAA.setter
    def wAA(self, value) -> None:
        self._wAA = value

    @property
    def wAa(self) -> float:
        return self._wAa

    @wAa.setter
    def wAa(self, value) -> None:
        self._wAa = value

    @property
    def waa(self) -> float:
        return self._waa

    @waa.setter
    def waa(self, value) -> None:
        self._waa = value

    @property
    def ngen(self) -> int:
        return self._ngen

    @property
    def history(self) -> QLineSeries:
        return self._history

    def next_gen(self) -> None:

        self._p = next_p_finite(self.size, self.p, self.u, self.v,
                                self.wAA, self.wAa, self.waa)

        self._ngen += 1
        self._history.append(self.ngen, self.p)


class Expectation:
    _p: float
    _u: float
    _v: float
    _wAA: float
    _wAa: float
    _waa: float
    _ngen: int
    _history: QLineSeries

    def __init__(self, p: float, u: float = 0, v: float = 0,
                 wAA: float = 1, wAa: float = 1, waa: float = 1) -> None:

        self._p = p
        self._u = u
        self._v = v
        self._wAA = wAA
        self._wAa = wAa
        self._waa = waa
        self._ngen = 0

        self._history = QLineSeries()
        self._history.append(self.ngen, self.p)

    @property
    def p(self) -> float:
        return self._p

    @property
    def u(self) -> float:
        return self._u

    @u.setter
    def u(self, value) -> None:
        self._u = value

    @property
    def v(self) -> float:
        return self._v

    @v.setter
    def v(self, value) -> None:
        self._v = value

    @property
    def wAA(self) -> float:
        return self._wAA

    @wAA.setter
    def wAA(self, value) -> None:
        self._wAA = value

    @property
    def wAa(self) -> float:
        return self._wAa

    @wAa.setter
    def wAa(self, value) -> None:
        self._wAa = value

    @property
    def waa(self) -> float:
        return self._waa

    @waa.setter
    def waa(self, value) -> None:
        self._waa = value

    @property
    def ngen(self) -> int:
        return self._ngen

    @property
    def history(self) -> QLineSeries:
        return self._history

    def next_gen(self) -> None:
        self._p = next_p(self.p, self.u, self.v, self.wAA, self.wAa, self.waa)
        self._ngen += 1
        self._history.append(self.ngen, self.p)
