#!/bin/env python3

import cv2, sys
import numpy as np

def imgu8(img):
  if img.dtype != np.uint8:
    img = (img/img.max()) * 255
  return np.uint8(img)

def imgfloat(img):
  if img.dtype == np.uint8:
    return np.float32(img)/255
  else:
    return np.float32(img)

def show(figname, img):
  if(img.dtype != np.uint8):
    img = imgu8(img)
  cv2.imshow(figname, img)
  key = cv2.waitKey(0)
  if key == 115: # Key 's'
    cv2.imwrite("fig/"+figname.replace(' ', '_')+".png", img)
  cv2.destroyAllWindows()

sobel_kernel_x = np.array([[-1, 0, 1],
                           [-2, 0, 2],
                           [-1, 0, 1]])
sobel_kernel_y = np.array([[-1,-2,-1],
                           [0, 0, 0,],
                           [1, 2, 1]])

if __name__ == "__main__":
  # Get threshold from commandline argument
  sobel_threshold = int(sys.argv[1])

  img = cv2.imread("fig/lenna.jpg")
  gray = imgfloat(cv2.cvtColor(img, cv2.COLOR_BGR2GRAY))
  img_gaussian = cv2.GaussianBlur(gray,(3,3),0)

  sobelx = np.abs(cv2.filter2D(img_gaussian, -1, sobel_kernel_x))
  sobely = np.abs(cv2.filter2D(img_gaussian, -1, sobel_kernel_y))
  sobelxy = np.sqrt(np.power(sobelx, 2) + np.power(sobely, 2))

  sobelx = imgu8(sobelx / sobelx.max())
  sobely = imgu8(sobely / sobely.max())
  sobelxy = imgu8(sobelxy / sobelxy.max())

  sobelx[sobelx >= sobel_threshold] = 255
  sobelx[sobelx < sobel_threshold] = 0
  sobely[sobely >= sobel_threshold] = 255
  sobely[sobely < sobel_threshold] = 0
  sobelxy[sobelxy >= sobel_threshold] = 255
  sobelxy[sobelxy < sobel_threshold] = 0

  show("sobelx", sobelx)
  show("sobely", sobely)
  show("sobelxy", sobelxy)