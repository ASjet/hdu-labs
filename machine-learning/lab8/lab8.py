import cv2
import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

def bgr2gray(img: np.ndarray) -> np.ndarray:
    return cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

def bgr2rgb(img: np.ndarray) -> np.ndarray:
    return cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

def figSize(height: int, width: int) -> None:
    plt.rcParams["figure.figsize"] = (width, height)

def noTicks() -> None:
    plt.xticks([])
    plt.yticks([])

def imgPlot(img: np.ndarray) -> None:
    plt.imshow(bgr2rgb(img))
    noTicks()

def imgPlotTable(imgs: list[np.ndarray], row: int, col: int) -> None:
    cnt = row*col
    for i in range(cnt):
        plt.subplot(row, col, i + 1)
        imgPlot(imgs[i])



def genBand(cnt: int) -> np.ndarray:
  colors = np.arange(0 ,360, 360//cnt)
  band = np.zeros((30,360,3))
  for i, c in enumerate(colors):
    band[:, i*(360//cnt):(i+1)*(360//cnt)+1, :] = [c, 1.0, 1.0]
  return cv2.cvtColor(np.float32(band), cv2.COLOR_HSV2RGB)

lenna = cv2.imread("lenna.jpg")
gray = bgr2gray(lenna)
km = KMeans()
km.fit(gray.reshape(np.prod(gray.shape), 1))
result = np.reshape(km.labels_, gray.shape)
classes = np.unique(result)

h, w = result.shape
colors = np.arange(len(classes)) * (360 // len(classes))
band = genBand(len(classes))
res = np.zeros((h,w,3), dtype=np.float32)
for i,c in enumerate(classes):
  res[result == c] = [colors[i], 1.0, 1.0]
res = cv2.cvtColor(res, cv2.COLOR_HSV2RGB)
figSize(5,20)
imgPlot(band)
plt.show()
imgPlotTable([lenna, gray, res], 1, 3)