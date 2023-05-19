import numpy as np
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
from sklearn.datasets import load_iris

plt.rcParams["figure.figsize"] = (8, 8)

iris = load_iris()
feat = StandardScaler().fit_transform(iris["data"])
label = iris["target"]

pca = PCA(n_components = 4)
pca.fit(feat)
X = pca.fit_transform(feat)

vec = pca.singular_values_
plt.plot(np.arange(len(vec)), vec, marker = "o")
plt.title("PCA Vector", fontsize = 16)
plt.xticks([0,1,2,3])
plt.grid()
plt.show()

color = ["r", "g", "b"]
for (x, y), l in zip(X[:,:2], label):
  plt.scatter(x, y, c = color[l])
plt.xticks([])
plt.yticks([])
plt.show()