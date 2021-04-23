from fbs_runtime.application_context.PyQt5 import ApplicationContext

from popsimpy.main import MainWindow

if __name__ == "__main__":
    appctxt = ApplicationContext()
    main_window = MainWindow()
    main_window.show()
    appctxt.app.exec_()
