import pandas
import sklearn
import pickle

from os.path import dirname, join

def random_forest(age,EF,SC,SS):

    #Generamos el clasificador
    filename = join(dirname(__file__), "classifier.p")
    classifier = pickle.load( open( filename, "rb" ) )

    datos_pandas = pandas.DataFrame()
    datos_pandas['age'] = [age]
    datos_pandas['ejection_fraction'] = [EF]
    datos_pandas['serum_creatinine'] = [SC]
    datos_pandas['serum_sodium'] = [SS]

    #Estandarizamos
    scaler = sklearn.preprocessing.StandardScaler()
    datos_scaled = scaler.fit_transform(datos_pandas)

    #Predecimos
    prediction = classifier.predict(datos_scaled)
    return prediction