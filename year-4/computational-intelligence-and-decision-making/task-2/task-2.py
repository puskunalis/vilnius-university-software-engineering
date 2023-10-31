import pandas as pd
import numpy as np

# Nuskaito ir paruosia irisu duomenu aibe
def fetch_and_prepare_iris_data():
    # Skaitome CSV formato faila
    df = pd.read_csv('iris/iris.data', header=None)

    # Filtruojame duomenis
    filtered_indices = df[df.iloc[:, -1].isin(['Iris-versicolor', 'Iris-virginica'])].index
    df = df.loc[filtered_indices]

    # Pakeiciame klasiu pavadinimus i numerius
    df.iloc[:, -1] = df.iloc[:, -1].map({'Iris-versicolor': 0, 'Iris-virginica': 1})

    return df

# Nuskaito ir paruosia kruties vezio duomenu aibe
def fetch_and_prepare_breast_cancer_data():
    # Skaitome CSV formato faila
    df = pd.read_csv('breast-cancer/breast-cancer-wisconsin.data', header=None)

    # Pasaliname pirma stulpeli
    df = df.iloc[:, 1:]

    # Ismetame eilutes su klaustukais
    indices_to_keep = ~df.isin(['?']).any(axis=1)
    df = df[indices_to_keep]

    # Konvertuojame visus stulpelius i skaiciu formata (problema del buvusiu klaustuku)
    for col in df.columns:
        df[col] = pd.to_numeric(df[col], errors='coerce')

    # Pakeiciame klasiu numerius
    df = df.loc[indices_to_keep].copy()
    df.iloc[:, -1] = df.iloc[:, -1].map({2: 0, 4: 1})

    return df

# Skaido duomenis i mokymo ir testavimo rinkinius
def split_data(train_test_split, df):
    # Maisome duomenis
    df = df.sample(frac=1, random_state=0)

    # Apskaiciuojame indeksa, kuriuo padalinsime duomenis
    split_index = int(train_test_split * len(df))

    # Daliname duomenis
    train_data = df[:split_index]
    test_data = df[split_index:]

    return train_data, test_data

# Neurono mokymas naudojant ADALINE taisykle ir stochastini gradientini nusileidima
def adaline_SGD(train_data, epochs, learning_rate):
    features = train_data.iloc[:, :-1].values
    classes = train_data.iloc[:, -1].values

    # Inicializuojame svorius ir bias
    weights = np.zeros(features.shape[1])
    bias = 0

    # Mokymo ciklas
    error_per_epoch = []
    accuracy_per_epoch = []
    for epoch in range(epochs):
        total_error = 0
        for xi, t in zip(features, classes):
            # Aktyvacijos funkcija yra tiesine
            y = np.dot(xi, weights) + bias
            weights += learning_rate * (t - y) * xi
            bias += learning_rate * (t - y)

            error = (t - y) ** 2
            total_error += error

        error_per_epoch.append(total_error)
        accuracy_per_epoch.append(accuracy(train_data, weights, bias))

    return weights, bias, error_per_epoch, accuracy_per_epoch

# Skaiciuoja klasifikavimo tiksluma
def accuracy(data, weights, bias):
    features = data.iloc[:, :-1].values
    classes = data.iloc[:, -1].values

    y = np.dot(features, weights) + bias

    # Slenkstine funkcija
    y = np.where(y > 0.5, 1, 0)

    return np.mean(y == classes)

# Skaiciuoja vidutine kvadratine paklaida
def mean_squared_error(data, weights, bias):
    features = data.iloc[:, :-1].values
    classes = data.iloc[:, -1].values

    # Aktyvacijos funkcija yra tiesine
    y = np.dot(features, weights) + bias

    # MSE skaiciavimas
    mse = np.mean((classes - y)**2)

    return mse

if __name__ == "__main__":
    #for learning_rate in np.arange(0.0001, 0.0301, 0.0001):
    train_test_split = 0.7 # Dalinimas i mokymo/testavimo aibes 70:30
    epochs = 100  # Epochu skaicius
    learning_rate = 0.0055  # Mokymosi greitis

    # Pasirinkti irisu arba krutu vezio duomenu aibes
    df = fetch_and_prepare_iris_data()
    #df = fetch_and_prepare_breast_cancer_data()

    # Duomenu dalinimas i mokymo ir testavimo aibes
    train_data, test_data = split_data(train_test_split, df)

    # Neurono mokymas
    weights, bias, error_per_epoch, accuracy_per_epoch = adaline_SGD(train_data, epochs, learning_rate)

    # Tikslumo skaiciavimas
    test_accuracy = accuracy(test_data, weights, bias)
    test_mse = mean_squared_error(test_data, weights, bias)

    print(f"Gauti svoriai: {np.round([bias, *weights], decimals=4)}")
    print(f"Gautos paklaidos po kiekvienos epochos mokymo duomenims: {np.round(error_per_epoch, decimals=4)}")
    print(f"Gauta paklaida testavimo duomenims: {test_mse:.4f}")
    print(f"Gautas klasifikavimo tikslumas po kiekvienos epochos mokymo duomenims: {np.round(accuracy_per_epoch, decimals=4)}")
    print(f"Gautas klasifikavimo tikslumas testavimo duomenims: {test_accuracy:.4f}")
