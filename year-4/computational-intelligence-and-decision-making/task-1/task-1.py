import math
import random

# Slenkstine aktyvacijos funkcija
def binary_step_activation(a):
    return 0 if a < 0 else 1

# Sigmoidine aktyvacijos funkcija
def sigmoid_activation(a):
    return round(1 / (1 + math.exp(-a)))

# Klasifikavimo funkcija
def classify_data_point(f, w0, weights, points):
    return f(w0 + sum(w * x for w, x in zip(weights, points)))

def classify_dataset(classification_data, activation_function, w0, w1, w2):
    # Aktyvacijos funkcija paduodama kaip simboliu eilute
    if activation_function == "binary":
        selected_activation_function = binary_step_activation
    elif activation_function == "sigmoid":
        selected_activation_function = sigmoid_activation
    else:
        print("Invalid activation function selected, must be 'binary' or 'sigmoid'.")
        return

    classes = ()

    # Klasifikavimas ir rezultatu spausdinimas
    for x1, x2 in classification_data:
        result = classify_data_point(selected_activation_function, w0, (w1, w2), (x1, x2))
        classes += (result,)
    
    return classes

# Paleidimas: python task-1.py
if __name__ == "__main__":
    # Programos argumentai
    classification_data = [(-0.2, 0.5), (0.2, -0.7), (0.8, -0.8), (0.8, 1)]
    data_classes = (0, 0, 1, 1)
    activation_function = "sigmoid"
    weights_interval = 100
    weights_to_find = 10

    # Rasti svoriu reiksmiu rinkinius
    for _ in range(weights_to_find):
        classes = []
        while classes != data_classes:
            # Sugeneruoti atsitiktina poslinki ir svorius
            w0 = random.randint(-weights_interval, weights_interval)
            w1 = random.randint(-weights_interval, weights_interval)
            w2 = random.randint(-weights_interval, weights_interval)

            classes = classify_dataset(classification_data, activation_function, w0, w1, w2)
        
        print(f"Classes correct using {activation_function} activation function with weights w0={w0}, w1={w1}, w2={w2}")