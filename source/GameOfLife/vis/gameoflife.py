import os


try:
    import matplotlib.pyplot as plt
    import seaborn as sns
except ModuleNotFoundError:
    os.system("pip3 install -r requirements.txt")
