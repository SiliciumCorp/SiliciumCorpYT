import matplotlib.pyplot as plt
import numpy as np
import random
import time

# col_width : nombre de colonne dans notre tableau 2D
# row_height : nombre de lignes dans notre tableau 2D
col_width, row_height = 50, 50

# Instancie et initialize Image pour devenir un Numpy.array rempli de 1
image = np.ones((col_width, row_height))

# Instancie et initialise Image pour devenir un Numpy.array rempli de valeur aléatoires comprise entre 0 et 1
# image = np.random.random(col_width*row_height)
# image = image.reshape((col_width, row_height))

# Version Python "equivalente" a np.ones()
'''
image = []
for i in range(row_height):
    col = []
    for j in range(col_width):
        col.append(1)
    image.append(col)
'''

#Definie la taille de la figure en pouces, et en pixel par pouces
plt.rcParams["figure.figsize"] = (12,12)
plt.rcParams["figure.dpi"] = 60

# Permet de définir les marges entre le bord de la fenetre et la figure
plt.subplots_adjust(left=0.01, right=0.99, top=0.99, bottom=0.01)

# Force les axes à etre egaux. ATTENTION, cette option s'applique pour les configurations carrés
plt.axis('equal')

# Dégage les ticks de la figure
plt.xticks([])
plt.yticks([])

# Déclare un tableau 2D de type pcolormesh
plt.pcolormesh(image, cmap="gray_r", edgecolors='lightgray', linewidths=0.5)

plt.show()