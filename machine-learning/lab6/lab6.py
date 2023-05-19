import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from sklearn.metrics import f1_score

data = pd.read_csv("data/city.txt", header = None)

class_cnt = 4

X = data.iloc[:, 1:]
km = KMeans(n_clusters = class_cnt)
km.fit(X)
classes = km.labels_
centers = km.cluster_centers_
np.unique(classes)

exp_sum = np.sum(X, axis=1)
gini = X.iloc[:,0] / exp_sum

exp_cen = np.sum(centers, axis=1)
gini_cen = centers[:, 0] / exp_cen

colors = ['blue', 'orange', 'green', 'red']
for i in range(class_cnt):
  plt.scatter(exp_sum[classes == i], gini[classes == i], marker = 'o', c = colors[i])
  plt.scatter(exp_cen[i], gini_cen[i], marker='o', s=200, c = colors[i])
plt.title("KMeans")
plt.xlabel("Expense Sum")
plt.ylabel("Gini Coefficient")
plt.show()