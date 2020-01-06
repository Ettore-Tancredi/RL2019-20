import cv2
from matplotlib import pyplot as plt
import numpy as np

PATH = 'silver_ball.jpg'    

img = cv2.imread(PATH, cv2.IMREAD_GRAYSCALE)
plt.imshow(img, cmap='gray')
circles = cv2.HoughCircles(img, cv2.HOUGH_GRADIENT, 1, 20, param1=130, param2=30, minRadius=0, maxRadius=0)
if circles is not None:
    for x, y, r in circles[0]:
        c = plt.Circle((x, y), r, fill=False, lw=3, ec='C1')
        plt.gca().add_patch(c)
plt.gcf().set_size_inches((12, 8))
plt.show()