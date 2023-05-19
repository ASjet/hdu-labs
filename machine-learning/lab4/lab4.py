import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from sklearn.impute import SimpleImputer
from sklearn.metrics import f1_score
from sklearn.model_selection import KFold
from sklearn.svm import SVC

# 加载数据
data = pd.read_csv("data/000777.csv")
data = data.iloc[:, 3:]

# X[开盘价、前收盘价、总市值、流通市值]
X = np.array(data.iloc[:, [3,4,10,11]].replace('None', 0), dtype=np.float64)
# Y[1: 涨; -1:跌]
Y = np.array(data.iloc[:, 6].replace('None', 0), dtype=np.float64)
Y[Y > 0] = 1
Y[Y <= 0] = -1
Y = np.int32(Y)

# 分为10折
sp = 10
kf = KFold(n_splits = sp, shuffle = True)
svm = SVC()
res = []
for i, (traini, testi) in enumerate(kf.split(X)):
  trainX = X[traini, :]
  trainY = Y[traini]
  testX = X[testi, :]
  testY = Y[testi]
  svm.fit(trainX, trainY)
  r = f1_score(testY, svm.predict(testX))
  print(f"{i+1}/{sp}: {r}")
  res.append(r)

# 绘制结果图
x = np.arange(len(res))
plt.rcParams['figure.figsize'] = (8,4)
plt.bar(x, res)
plt.plot(x, np.ones_like(x)*np.mean(res), 'r')
plt.ylim([0,1])
plt.xticks(x)
plt.yticks(x/10)
plt.grid()
plt.title("K-Fold Metrics", fontsize = 16)
plt.xlabel("Sample batch", fontsize = 16)
plt.ylabel("F1-Score", fontsize = 16)
plt.legend([ "Mean", "K-Fold"])
plt.show()