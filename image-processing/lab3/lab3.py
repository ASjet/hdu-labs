import numpy as np
import matplotlib.pyplot as plt
import cv2

imgs = [
  "fig/rgb.png",
  "fig/2-1.jpg"
]

def readi(index):
  name = imgs[index]
  img = cv2.imread(name)
  return img

def imgu8(img):
  if img.dtype != np.uint8:
    img = img * 255
    img[img > 255] = 255
  return np.uint8(img)

def imgfloat(img):
  if img.dtype == np.uint8:
    return np.float64(img)/255
  else:
    return np.float64(img)

def show(figname, img, save=False):
  if save:
    if(img.dtype != np.uint8):
      img = imgu8(img)
    cv2.imwrite("fig/"+figname.replace(' ', '_')+".png", img)
  cv2.imshow(figname, img)
  cv2.waitKey(0)
  cv2.destroyWindow(figname)


def hist(img):
  cnt = {}
  flatten = imgu8(img).flatten()
  for elem in flatten:
    if cnt.get(elem):
      cnt[elem] += 1
    else:
      cnt[elem] = 1
  y = [cnt[e] if cnt.get(e) else 0 for e in range(0,256)]
  return y

def equa(img):
  H = hist(img)
  sum_H = np.sum(H)
  eqmap = np.zeros_like(H)
  p = 0
  for i, e in enumerate(H):
    p += e/sum_H
    eqmap[i] = int(p*255)
  eqm = lambda x: eqmap[x]
  return np.uint8(eqm(img))


img = readi(1)
eqd = equa(img)
x = np.arange(0,256)
h = hist(img)
h1 = hist(eqd)
plt.bar(x,h)
plt.xlim([0,255])
plt.bar(x,h1)
plt.xlim([0,255])
plt.show()
show("raw", img)
show("eqd", eqd)