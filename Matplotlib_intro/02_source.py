import matplotlib.pyplot as plt

# Recupere la figure contenue dans Pyplot
fig = plt.figure()

#Recupere les axes contenus dans la figure
ax = fig.subplots()

#Initialise les données contenues dans les Axes [X's],[Y's]
ax.plot([1, 2, 3, 4], [0, 0.5, 1, 0.2])

#Dessine le graphe
plt.show()
