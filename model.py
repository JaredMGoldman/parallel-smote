import tensorflow.keras as tf
from tensorflow.keras.layers import *

model = tf.Sequential()

start = Input(shape = (29,))
a1 = Dense(50,'relu')(start)
a2 = Dense(75, 'relu')(a1)
a3 = Dense(100, 'relu')(a2)
a4 = Dense(75, 'relu')(a3)
a5 = Dense(50, 'relu')(a4)
final = Dense(1, activation = 'softmax')(a5)