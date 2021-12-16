import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import joblib
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestRegressor
from sklearn.ensemble import RandomForestClassifier
import pickle


def random_forest_entrenamiento():
    data = pd.read_csv('C:/Users/cuent/Desktop/NEURAL NETWORK/python/heart_failure_clinical_records_dataset.csv')
    
    #We divide data to predict and objective data.
    x = data[["age","ejection_fraction","serum_creatinine","serum_sodium"]]
    y = data["DEATH_EVENT"]
    
    #We separate between train and test
    x_train, x_test, y_train, y_test = train_test_split(x, y, test_size = 0.25, random_state = 0)
    
    #We standardize
    scaler = StandardScaler()
    x_train_scaled = scaler.fit_transform(x_train)
    x_test_scaled = scaler.transform(x_test)
    
    #We create the classifier
    classifier = RandomForestClassifier(n_estimators = 600, random_state = 0,
    min_samples_split = 2, min_samples_leaf =10,
    max_features = 'auto', max_depth =20, bootstrap =True)
    
    #We train the model
    classifier.fit(x_train_scaled, y_train)
    prediction = classifier.predict(x_test_scaled)
    

    #We save the model
    pickle.dump( classifier, open( "classifier.p", "wb" ) )
    
   



random_forest_entrenamiento()




