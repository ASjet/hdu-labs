import enum
import numpy as np
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


def chshow(img, chs):
  if img.dtype != np.uint8:
    img = imgu8(img)
  chs = np.array(chs)
  if chs.dtype != np.uint8:
    chs = imgu8(chs)

  c1 = cv2.cvtColor(chs[0], cv2.COLOR_GRAY2BGR)
  c2 = cv2.cvtColor(chs[1], cv2.COLOR_GRAY2BGR)
  c3 = cv2.cvtColor(chs[2], cv2.COLOR_GRAY2BGR)
  res1 = np.hstack((img,c1))
  res2 = np.hstack((c2, c3))
  res = np.vstack((res1,res2))
  return res


def bgr2hsi(img):
  img = imgfloat(img)
  b = img[:,:,0]
  g = img[:,:,1]
  r = img[:,:,2]

  H = np.zeros_like(r)
  S = np.zeros_like(r)
  I = np.zeros_like(r)


  for i in range(img.shape[0]):
    for j in range(img.shape[1]):
      b, g, r = img[i,j]
      I[i,j] = np.mean(img[i,j])
      if r == b and r == g and g == b:
        S[i,j] = 0
      else:
        S[i,j] = 1 - 3*np.min([r,g,b])/np.sum([r,g,b])

      cosv = 0.5*((r-g) + (r-b))/(np.sqrt(np.power(r-g,2) + (r-b)*(g-b)))
      theta = np.rad2deg(np.arccos(cosv))
      if b > g:
        theta = 360 - theta
      H[i,j] = theta / 360

  return H,S,I

def hsi2bgr(H, S, I):
  R = np.zeros_like(H)
  G = np.zeros_like(H)
  B = np.zeros_like(H)
  H = H * 360

  for i,row in enumerate(H):
    for j,h in enumerate(row):
      ic = I[i,j]
      sc = S[i,j]
      if sc == 0:
        r = ic
        g = ic
        b = ic
      else:
        if h < 120:
          b = ic * (1 - sc)
          r = ic * (1 + sc*np.cos(np.deg2rad(h))/np.cos(np.deg2rad(60-h)))
          g = 3*ic - (r+b)
        elif h >= 120 and h < 240:
          h = h - 120
          r = ic * (1 - sc)
          g = ic * (1 + sc*np.cos(np.deg2rad(h))/np.cos(np.deg2rad(60-h)))
          b = 3*ic - (r+g)
        else:
          h = h - 240
          g = ic * (1 - sc)
          b = ic * (1 + sc*np.cos(np.deg2rad(h))/np.cos(np.deg2rad(60-h)))
          r = 3*ic - (g+b)
      R[i,j] = r
      G[i,j] = g
      B[i,j] = b

  return imgu8(cv2.merge((B,G,R)))

def brighter(img, arg):
  h, s, i = bgr2hsi(img)
  i = i*(1+arg)
  i[i>1] = 1
  return hsi2bgr(h, s, i)

def sat(img, arg):
  h, s, i = bgr2hsi(img)
  s = s*(1+arg)
  s[s>1] = 1
  return hsi2bgr(h, s, i)


if __name__ == "__main__":
  save = True
  img = readi(1)
  b,g,r = cv2.split(img)
  h,s,i = bgr2hsi(img)
  hsi = imgu8(cv2.merge((h,s,i)))
  rgb2hsi2rgb = hsi2bgr(h,s,i)
  sprgb = chshow(img, [r,g,b])
  sphsi = chshow(img, [h,s,i])

  b = 0.2
  s = 0.2
  bright = brighter(img, b)
  saturation = sat(img, s)

  show("R-G-B", sprgb, save)
  show("H-S-I", sphsi, save)
  show("rgb2hsi2rgb", np.hstack((img, hsi, rgb2hsi2rgb)), save)
  show("Brightness {}%".format(int(b*100)), np.hstack((img, bright)), save)
  show("Saturation {}%".format(int(s*100)), np.hstack((img, saturation)), save)

