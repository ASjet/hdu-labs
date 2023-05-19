import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn import linear_model

# Read data
prices = pd.read_csv("data/prices.txt")
size = np.array(prices.iloc[:,1])
price = np.array(prices.iloc[:,0])
data_range = [size.min(), size.max()]

# Fit linear model
mod = linear_model.LinearRegression()
mod.fit(size.reshape(-1,1), price)

# Predict result
x = np.arange(data_range[0], data_range[1])
y = mod.predict(x.reshape(-1,1))

# Draw figure
plt.scatter(size,price)
plt.plot(x,y)
plt.xlim([0,1000])
plt.xlabel("面积(m^2)")
plt.ylabel("房价(万)")
plt.title("面积-房价 线性回归预测曲线")
plt.show()