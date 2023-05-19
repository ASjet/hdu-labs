import cv2
import numpy as np
print(cv2.__version__)

# folder = "1-images/"
folder = ""
imgs = [
  folder+"1-1-1.png",
  folder+"1-1-2.jpg",
  folder+"1-1-3.jpg",
  folder+"1-2.bmp"
]

## Image i/o wrapper

def readi(index):
  name = imgs[index]
  img = cv2.imread(name)
  return name.split('.')[0], img

def show(figname, img, save=False):
  if save:
    if(img.dtype != np.uint8):
      img = np.uint8((img - img.min()) / img.max() * 255)
    cv2.imwrite(figname.replace(' ', '_')+".png", img)
  cv2.imshow(figname, img)
  cv2.waitKey(0)
  cv2.destroyWindow(figname)

## Image operation warpper

def imgop1(index, op, arg, save=False):
  name, img = readi(index)
  result, msg = op(img, arg)
  figname = "img{} op {}".format(name, msg)
  print(figname)
  show(figname, result, save)

def imgop2(ia, ib, op, save=False):
  namea, imga = readi(ia)
  nameb, imgb = readi(ib)
  result, msg = op(imga, imgb)
  figname = "img{} {} img{}".format(namea, msg, nameb)
  print(figname)
  show(figname, result, save)

## Display

def display(index):
  name, img = readi(index)
  print(name)
  show(name, img)

def displayAll():
  for name in imgs:
    img = cv2.imread(name)
    print(name)
    show(name, img)

## 1-image operator

def op1cut(img, arg):
  y, x, saveName = arg
  cutted = img[x[0]:x[1], y[0]:y[1], :]
  print("Raw image size: {}".format(img.shape))
  print("Cutted image size: {}".format(cutted.shape))
  if(saveName != None):
    cv2.imwrite(saveName, cutted)
    print("save to {}".format(saveName))
  return cutted, "cut x[{},{}] y[{},{}]".format(x[0],x[1],y[0],y[1])

def op1gamma(img, gma):
  c = 1
  img = img / 255
  M = np.ones_like(img) * gma
  result = c * np.power(img, M)
  return result, "c={} gamma={}".format(c, gma)

def op1resize(img, mag):
  y, x = np.array(img.shape[:2]) * mag
  result = cv2.resize(img, (int(x), int(y)))
  return result, "resize {}x".format(mag)

def op1rotate(img, angle):
  if(angle == 90):
    result = cv2.rotate(img, cv2.ROTATE_90_CLOCKWISE)
  elif(angle == 180):
    result = cv2.rotate(img, cv2.ROTATE_180)
  return result, "ang{} rotated".format(angle)

def op1bitnot(img, arg):
  return np.bitwise_not(img), "bitwise_not"

## 2-image operator

def op2add(a, b):
  return a + b, "add"

def op2sub(a, b):
  return a - b, "sub"

def op2dot(a, b):
  return a * b, "dot"

def op2bitand(a, b):
  return np.bitwise_and(a, b), "bitwise_and"

def op2bitor(a, b):
  return np.bitwise_or(a, b), "bitwise_or"

def op2bitxor(a, b):
  return np.bitwise_xor(a, b), "bitwise_xor"




if __name__ == "__main__":
  save = True

  print("==>lab1-{1,2,3}")
  displayAll()

  print("==>lab1-4")
  # index, x1, x2, y1, y2, savename = input("cutimg(index, x1, x2, y1, y2, saveName):").strip().split(' ')
  # index, x1, x2, y1, y2 = int(index), int(x1), int(x2), int(y1), int(y2)
  index, x1, x2, y1, y2, savename = 2, 100, 200, 100, 250, "cut2_100x150.png"
  imgop1(index, op1cut, ((x1, x2), (y1, y2), savename), save)

  print("==>lab1-5")
  display(3)
  for i in [3, 4, 5]:
    imgop1(3, op1gamma, i, save)

  print("==>lab1-6")
  # ia, ib = input("imgop(indexa, indexb):").strip().split(' ')
  # ia, ib = int(ia), int(ib)
  ia, ib = 0, 2
  na, nb = imgs[ia], imgs[ib]

  imgop2(ia, ib, op2add, save)
  imgop2(ia, ib, op2sub, save)
  imgop2(ia, ib, op2dot, save)

  imgop1(ib, op1resize, 0.5, save)
  imgop1(ib, op1resize, 2, save)

  imgop1(ib, op1rotate, 90, save)
  imgop1(ib, op1rotate, 180, save)

  print("==>lab1-7")
  imgop2(ia, ib, op2bitand, save)
  imgop2(ia, ib, op2bitor, save)
  imgop1(ib, op1bitnot, None, save)
  imgop2(ia, ib, op2bitxor, save)