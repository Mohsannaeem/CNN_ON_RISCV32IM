#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Wed Oct  7 18:47:15 2020

@author: mohsan
"""
from __future__ import print_function
import numpy as np
np.random.seed(1337)  # for reproducibility
from keras.datasets import mnist
from keras.models import Sequential,load_model
from keras.layers.core import Dense, Dropout, Activation, Flatten
from keras.layers.convolutional import Convolution2D, MaxPooling2D
from keras.utils import np_utils
import matplotlib.pyplot as plt #for plotting
from sklearn.model_selection import train_test_split
batch_size = 128
nb_classes = 10
nb_epoch = 1
# input image dimensions
img_rows, img_cols = 28, 28
# number of convolutional filters to use
nb_filters = 4
# size of pooling area for max pooling
nb_pool = 2
# convolution kernel size
nb_conv = 3
# the data, shuffled and split between train and test sets
(X_train, Y_train), (X_test, Y_test) = mnist.load_data()
X_train = X_train.reshape(X_train.shape[0], 1, img_rows, img_cols)
#X_test = X_test.reshape(X_test.shape[0], 1, img_rows, img_cols)
X_train = X_train.astype('float32')
#X_test = X_test.astype('float32')
X_train /= 255
#X_test /= 255
#print('X_train shape:', X_train.shape)
#print(X_train.shape[0], 'train samples')
#print(X_test.shape[0], 'test samples')
# convert class vectors to binary class matrices
Y_train = np_utils.to_categorical(Y_train, nb_classes)
#Y_test = np_utils.to_categorical(Y_test, nb_classes)
X_train, X_val, Y_train, Y_val = train_test_split(X_train, Y_train, test_size=0.2, random_state=1)
# load the saved model
#plt.imshow(X_train[:1], cmap=plt.get_cmap('gray'))
#plt.show();
model = load_model('./my_nn_model.h5')
print('Prediction on saved sample:')
print(str(model.predict(X_train[:1])))
print(Y_train[:1]);
