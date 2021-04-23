"""popsimpy"""

from datetime import datetime
import typing

from PyQt5.QtCore import pyqtBoundSignal
from PyQt5.QtCore import pyqtSignal

PYQT_SIGNAL = typing.Union[pyqtSignal, pyqtBoundSignal]

date_time = datetime.now()
y = str(date_time.year)

__script_name__ = 'popsimpy'
__version__ = '0.0.0'
__description__ = 'A popg clone.'
__author__ = 'Karolis Ramanauskas'
__author_email__ = 'kraman2@uic.edu'
__copyright__ = 'Copyright \u00A9 ' + __author__ + ', ' + y
__license__ = 'Creative Commons Attribution-ShareAlike 4.0 International ' \
              'License: cc-by-sa-4.0'
__url__ = 'https://github.com/karolisr/popsim'

__all__ = [PYQT_SIGNAL]
