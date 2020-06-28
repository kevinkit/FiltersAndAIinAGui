# -*- coding: utf-8 -*-
"""
Created on Sun Jun 28 16:07:43 2020

@author: Kevin
"""

# from tensorflow.keras.applications import ResNet50
# from tensorflow.keras.preprocessing import image
# from tensorflow.keras.applications.resnet50 import preprocess_input, decode_predictions

SIZE = 224
CHANNELS = 3
#model = ResNet50(weights="imagenet")


from PyQt5.QtCore import QSharedMemory,QBuffer
import numpy as np
from matplotlib import pyplot as plt
import cv2


mem = QSharedMemory("image4")
mem.attach()

while True:
    mem.lock()
    t = np.array(mem.constData().asarray())
    n_t = t[0:SIZE*SIZE*CHANNELS]
    plt.imshow(n_t.reshape((SIZE,SIZE,-1)))
    cv2.imwrite("test123.png",n_t.reshape((SIZE,SIZE,-1)))
    mem.unlock()
    break

mem.unlock();
mem.detach();
#del model