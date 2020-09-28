
# Check the versions of libraries
# test git with new macbook pro installation
# Python version
import sys
print('Python: {}'.format(sys.version))
# scipy
import scipy
print('scipy: {}'.format(scipy.__version__))
# numpy
import numpy
print('numpy: {}'.format(numpy.__version__))
# matplotlib
import matplotlib
print('matplotlib: {}'.format(matplotlib.__version__))
# pandas
import pandas
print('pandas: {}'.format(pandas.__version__))
# scikit-learn
import sklearn
print('sklearn: {}'.format(sklearn.__version__))


# Load libraries
from pandas import read_csv
from pandas.plotting import scatter_matrix
from matplotlib import pyplot
from sklearn.model_selection import train_test_split
from sklearn.model_selection import cross_val_score
from sklearn.model_selection import StratifiedKFold
from sklearn.metrics import classification_report
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.naive_bayes import GaussianNB
from sklearn.svm import SVC
# Additional Declare
import os
import time
clear = lambda: os.system('clear')

# Load dataset
url = "iris.csv"
names = ['sepal-length', 'sepal-width', 'petal-length', 'petal-width', 'class']
dataset = read_csv(url, names=names)

print("\n............................................................\n")

print(type(dataset))

print("\n............................................................\n")

print(dataset)

print("\n............................ Detail .........................\n")
print(f"Shape     : {dataset.shape}\n")
print(f"Head [3]  : \n\n{dataset.head(3)}\n")
print(f"Describe  : \n\n{dataset.describe()}\n")
print(f"Group by  : \n\n{dataset.groupby('class').size()}\n")

x = input("...Press any key to continue...")
clear()


while(1):
    print("\n......................... Visualization .....................\n")
    choice = input("Input choice :")
    if choice == '1': 
        dataset.plot(kind='box', subplots=True, layout=(2,2), sharex=False, sharey=False)
        pyplot.show()
    elif choice == '2': 
        dataset.hist()
        pyplot.show()
    elif choice == '3':
        scatter_matrix(dataset)
        pyplot.show()
    elif choice == 'exit':
        clear()
        break
    clear()
    


