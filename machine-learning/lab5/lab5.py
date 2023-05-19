import re
from pathlib import Path
import numpy as np
import matplotlib.pyplot as plt
from sklearn.neural_network import MLPClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import classification_report, f1_score


train_path = Path("./data/train")
test_path = Path("./data/test")
y_ptn = re.compile("(\d{1}).*\.txt")


def load1(path: Path) -> list[np.ndarray, np.ndarray]:
  y = np.zeros(10, dtype=np.uint8)
  y[int(y_ptn.match(path.name).group(1))] = 1
  lines = path.read_text().removesuffix('\n').split('\n')
  for i, line in enumerate(lines):
    lines[i] = list(line)
  x = np.array(lines, dtype=np.uint8)
  return x.ravel(), y


def loadDir(path: Path) -> list[np.ndarray, np.ndarray]:
  X = []
  Y = []
  for i in path.iterdir():
    x, y = load1(i)
    X.append(x)
    Y.append(y)
  return np.vstack(X), np.vstack(Y)

trainX, trainY = loadDir(train_path)
testX, testY = loadDir(test_path)

# MLP
mlp = MLPClassifier(
  hidden_layer_sizes = (100, 100),
  activation = "relu",
  solver = "adam",
  alpha = 0.00001,
  learning_rate = "adaptive",
  learning_rate_init = 0.005,
  max_iter = 200,
  momentum = 0.9
)
mlp.fit(trainX, trainY)
mlp_pred = mlp.predict(testX)
print("MLP F1-Score:", f1_score(testY, mlp_pred, average = 'weighted'), sep=' ')

# KNN
knn = KNeighborsClassifier(n_neighbors=1, n_jobs=-1)
knn.fit(trainX, trainY)
knn_pred = knn.predict(testX)
print("KNN F1-Score:", f1_score(testY, knn_pred, average = 'weighted'), sep=' ')