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
    # collect data from each csv file
    original_data = pd.read_csv('creditcard.csv').sample(frac=1)

    validation = original_data[:1000]
    original_data = original_data[1000:]

    smote = pd.read_csv('smote.csv', names = original_data.columns.values)

    # concatonate datasets for new smote-enhanced dataset
    frames = [original_data, smote]
    smote_data = pd.concat(frames)

    # seperate training data and labels for each dataset 
    target_original = original_data.pop('Class')
    target_smote = smote_data.pop('Class')
    target_validation = validation.pop('Class')

    # create tensorflow dataset objects from dataframes
    original_dataset = tf.data.Dataset.from_tensor_slices((original_data.values, target_original.values))
    train_dataset_original = original_dataset.shuffle(len(original_data)).batch(32)

    smote_dataset = tf.data.Dataset.from_tensor_slices((smote_data.values, target_smote.values))
    train_dataset_smote = smote_dataset.shuffle(len(smote_data)).batch(32)

    validation_dataset = tf.data.Dataset.from_tensor_slices((validation.values, target_validation.values))
    final_dataset_validation = validation_dataset.shuffle(len(validation)).batch(32)

    return train_dataset_original, train_dataset_smote, final_dataset_validation

def trainModel(data):
    model = getModel()
    model.fit(data, batch_size = 32, epochs = 5)
    return model


base_dataset, enhanced_dataset, validation_dataset = getData()

print("training basic model...")
model_base = trainModel(base_dataset)
print("finished training\n\nmaking prediction...\n\n")
model_base.evaluate(validation_dataset)

print("training enhanced model...")
model_smote = trainModel(enhanced_dataset)
print("finished training\n\nmaking prediction...\n\n")
model_smote.evaluate(validation_dataset)
print("all done!")