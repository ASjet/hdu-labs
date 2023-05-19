import re
import os
import cv2
import numpy as np
from pathlib import Path
import matplotlib.pyplot as plt

filling_window = "Filling"
fig_path = "./fig/"
img_ptn = re.compile(".*\.[png|jpg|bmp]")

fig = Path(fig_path)

mor_fill_kernel = np.array([
    [0, 1, 0],
    [1, 1, 1],
    [0, 1, 0]
], dtype=np.uint8)

# Matplotlib runtime configuration


def figSize(height: int, width: int) -> None:
    plt.rcParams["figure.figsize"] = (width, height)


def figCmap(colormap: str) -> None:
    plt.set_cmap(colormap)

# Matplotlib plot wrapper


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
    plt.show()


def imgHist(imgs: list[np.ndarray]) -> None:
    cnt = len(imgs)
    x = np.arange(256)
    for i in range(cnt):
        plt.subplot(2, cnt, i + 1)
        # plt.hist(imgs[i].ravel(), 256, [0, 255])
        h = hist(imgu8(imgs[i]))
        plt.bar(x, h)
        plt.ylim([0, 1])
        noTicks()
        plt.subplot(2, cnt, cnt + i + 1)
        imgPlot(imgs[i])

# Path operation


def missing(path: Path) -> None:
    print(f"'{path.resolve()}' not exists")
    os._exit(0)


def check(path: Path) -> None:
    if not path.exists():
        missing(path)


def mkdir(path: Path) -> None:
    if not path.exists():
        path.mkdir(parents=True)

# Image convert


def imgu8(img: np.ndarray, norm=True) -> np.ndarray:
    if img.dtype != np.uint8:
        if norm:
            img /= img.max()
        else:
            img[img > 1.0] = 1.0
        img *= 255
    return np.uint8(img)


def imgfloat(img: np.ndarray, norm=True) -> np.ndarray:
    if img.dtype == np.uint8:
        return np.float(32) / 255
    else:
        return np.float32(img)


def bgr2rgb(img: np.ndarray) -> np.ndarray:
    return cv2.cvtColor(img, cv2.COLOR_BGR2RGB)


def rgb2bgr(img: np.ndarray) -> np.ndarray:
    return cv2.cvtColor(img, cv2.COLOR_RGB2BGR)


def bgr2gray(img: np.ndarray) -> np.ndarray:
    return cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)


def extCh(img: np.ndarray) -> np.ndarray:
    return cv2.merge((img, img, img))

# Image IO


def imgRead(img_name: str, dir: Path = fig) -> np.ndarray:
    img_path = dir / img_name
    check(img_path)
    path = str(img_path.resolve())
    img = cv2.imread(path)
    return imgu8(img)


def imgReadi(index: int) -> np.ndarray:
    imgs: list[Path] = []
    for f in fig.iterdir():
        if f.is_file() and img_ptn.match(f.name):
            imgs.append(f)
    return imgRead(imgs[index].name)


def imgWrite(img_name: Path, img: np.ndarray, dir: Path = fig) -> np.ndarray:
    mkdir(dir)
    path = str((dir / img_name).resolve())
    if not cv2.imwrite(path, img):
        print(f"Cannot write {type(img)} to '{path}'")


def imgDisp(figname: str, img: np.ndarray) -> None:
    img = imgu8(img)
    cv2.imshow(figname, img)
    key = cv2.waitKey(0)
    if key == 115:  # Key 's'
        imgWrite(f"{figname.replace(' ', '_')}.png", img)
    cv2.destroyWindow(figname)

# Analysis


def chView(img: np.ndarray, flatten=False) -> np.ndarray:
    b, g, r = cv2.split(img)
    res = [np.hstack([img, extCh(r)]), np.hstack([extCh(g), extCh(b)])]
    if flatten:
        return np.hstack(res)
    else:
        return np.vstack(res)


def drawGrid(img: np.ndarray, x_interval: float, y_interval: float, color=(0, 0, 255)) -> np.ndarray:
    res = img.copy()
    height, width = img.shape[:2]
    x_int = np.intp(width * x_interval)
    y_int = np.intp(height * y_interval)
    res[:, ::x_int] = color
    res[::y_int, :] = color
    return res

# Basic


def binary(img: np.ndarray, threshold: int, maxval: int = 255) -> np.ndarray:
    type = cv2.THRESH_BINARY if threshold > 0 else cv2.THRESH_BINARY+cv2.THRESH_OTSU
    r, b = cv2.threshold(img, threshold, maxval, type=type)
    assert(r)
    return b


def hist(img: np.ndarray) -> np.ndarray:
    h, b = np.histogram(img, 256, (0, 255))
    return h / h.max()


def resize(img: np.ndarray, factor: np.float64) -> np.ndarray:
    newsize = np.int32(np.array(img.shape[:2])/factor)[::-1]
    return cv2.resize(img, tuple(newsize))


def rotate(image: np.ndarray, angle: int) -> np.ndarray:
    image_center = tuple(np.array(image.shape[1::-1]) / 2)
    rot_mat = cv2.getRotationMatrix2D(image_center, angle, 1.0)
    result = cv2.warpAffine(
        image, rot_mat, image.shape[1::-1], flags=cv2.INTER_LINEAR)
    return result


def transform(img: np.ndarray, x: np.float64, y: np.float64,
              wid: np.float64, hei: np.float64) -> list[int, int, int, int]:
    height, width = img.shape[:2]
    x1 = max(int(width * (x - (wid/2))), 0)
    x2 = min(int(width * (x + (wid/2))), width-1)
    y1 = max(int(height * (y - (hei/2))), 0)
    y2 = min(int(height * (y + (hei/2))), height-1)
    return x1, x2, y1, y2


def crop(img: np.ndarray, x: np.float64, y: np.float64, wid: np.float64,
         hei: np.float64) -> np.ndarray:
    x1, x2, y1, y2 = transform(img, x, y, wid, hei)
    return img[y1:y2, x1:x2]


# Morphology


def morOpen(img: np.ndarray, kernel: np.ndarray, iterations: int = 1) -> np.ndarray:
    erd = cv2.erode(img, kernel, iterations=iterations)
    dlt = cv2.dilate(erd, kernel, iterations=iterations)
    return dlt


def morClose(img: np.ndarray, kernel: np.ndarray, iterations: int = 1) -> np.ndarray:
    dlt = cv2.dilate(img, kernel, iterations=iterations)
    erd = cv2.erode(dlt, kernel, iterations=iterations)
    return erd


def internalEdge(img: np.ndarray, kernel: np.ndarray) -> np.ndarray:
    erd = cv2.erode(img, kernel)
    return img ^ erd


def externalEdge(img: np.ndarray, kernel: np.ndarray) -> np.ndarray:
    dlt = cv2.dilate(img, kernel)
    return img ^ dlt


def mor_edge(img: np.ndarray, kernel: np.ndarray) -> np.ndarray:
    i_edge = internalEdge(img, kernel)
    e_edge = externalEdge(img, kernel)
    return i_edge | e_edge


def morFill(edge: np.ndarray, seed_pos: tuple, debug=False) -> np.ndarray:
    """
    edge is white edge with black background
    """
    A = np.uint8(edge)
    A_c = 255 - A
    prex = np.zeros_like(edge, dtype=np.uint8)
    prex[seed_pos[0], seed_pos[1]] = 255
    while True:
        x = cv2.dilate(prex, mor_fill_kernel) & A_c
        if debug:
            cv2.imshow(filling_window, 255-x)
            key = cv2.waitKey(10)
            if key == 32:
                cv2.destroyWindow(filling_window)
                break
        if np.array_equal(x, prex):
            break
        prex = x
    return 255 - prex

# BoundingBox


def boundingBox(img: np.ndarray) -> list:
    height, width = img.shape
    x_min = width
    y_min = height
    x_max = 0
    y_max = 0
    for i in range(height):
        if(img[i, :].any() > 0):
            y_min = min(y_min, i)
            y_max = max(y_max, i)
    for i in range(width):
        if(img[:, i].any() > 0):
            x_min = min(x_min, i)
            x_max = max(x_max, i)
    x = (x_min+x_max) / 2 / width
    y = (y_min+y_max) / 2 / height
    w = (x_max-x_min) / width
    h = (y_max-y_min) / height
    return [x, y, w, h]


def getBox(img: np.ndarray) -> np.ndarray:
    """img must be 3-channel"""
    counts, thres = cv2.findContours(
        img, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    boxs = []
    for c in counts:
        rect = cv2.minAreaRect(c)
        box = np.int0(cv2.boxPoints(rect))
        boxs.append(box)

    return boxs


def cropBox(img: np.ndarray, box: np.ndarray) -> np.ndarray:
    """img must be 3-channel"""
    mask = np.zeros_like(img, dtype=np.uint8)
    cv2.fillPoly(mask, [box], (255, 255, 255))
    cord = [np.min(box[:, 1]), np.max(box[:, 1]),
            np.min(box[:, 0]), np.max(box[:, 0])]
    res = img & mask

    return res[cord[0]:cord[1], cord[2]:cord[3]]


def perspectiveTransform(img: np.ndarray) -> np.ndarray:
    """img must be 3-channel"""
    h, w = img.shape[:2]
    gray = bgr2gray(img)
    cnts, thres = cv2.findContours(
        gray, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    rect = cv2.minAreaRect(cnts[0])
    pst1 = np.float32(np.int0(cv2.boxPoints(rect)))
    if rect[-1] > 45:
        pst2 = np.array([[0, 0], [w-1, 0], [w-1, h-1],
                        [0, h-1]], dtype=np.float32)
    else:
        pst2 = np.array([[0, h-1], [0, 0], [w-1, 0],
                        [w-1, h-1]], dtype=np.float32)

    M = cv2.getPerspectiveTransform(pst1, pst2)
    res = cv2.warpPerspective(img, M, (w, h))
    return res
