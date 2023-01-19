import matplotlib.pyplot as plt

# Intancie un sous-graph dans la figure en cours
# ligne, colonne, index
# ligne : combien de lignes
# colonne : combien de colonnes
# index : ou placera t'on le graph dans ce layout.
plt.subplot(2, 4, 1) # 2 lignes, 4 colonnes, met le graphe en index 1

# Recupere les Axes en cours et stock dans ax1
ax1 = plt.gca()

# Nouveau sous-graphe
plt.subplot(1, 2, 2) # 1 ligne, 2 colonnes, met le graphe en index 2

# Recupere les Axes en cours et stock dans ax2
ax2 = plt.gca()

# Definie la data directement dans les axes stockes en memoire
ax1.plot([1, 2, 3], [0, 0.5, 0.2])
ax2.plot([3, 2, 1], [0, 0.5, 0.2])

plt.show()