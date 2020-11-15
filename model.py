import tensorflow as tf
from tensorflow.keras.layers import Dense
import pandas as pd
import os

def getModel():
    model = tf.keras.Sequential([
    Dense(50, activation = 'relu'),
    Dense(75, activation = 'relu'),
    Dense(100, activation = 'relu'),
    Dense(75, activation = 'relu'),
    Dense(50, activation = 'relu'),
    Dense(1, activation = 'softmax')
    ])
    
    model.compile(optimizer='adam', loss=tf.keras.losses.BinaryCrossentropy(from_logits=True), metrics=['accuracy'])

    return model

def getData():
    data = pd.read_csv('creditcard.csv')
    target = data.pop('Class')
    dataset = tf.data.Dataset.from_tensor_slices((data.values, target.values))
    train_dataset = dataset.shuffle(len(data)).batch(32)
    return train_dataset

dataset = getData()
model = getModel()
model.fit(dataset, batch_size=32, epochs=10)
