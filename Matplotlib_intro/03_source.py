import matplotlib.pyplot as plt

# Intancie un sous-graph dans la figure en cours
# ligne, colonne, index
# ligne : combien de lignes
# colonne : combien de colonnes
# index : ou placera t'on le graphe dans ce layout.
plt.subplot(2, 4, 1) # 2 lignes, 4 colonnes, met le graphe en index 1

# Definie les données contenue dans les Axes.
# plt pointe vers le dernier subplot déclaré
plt.plot([1, 2, 3], [0, 0.5, 0.2])

# Nouveau sous-graph
plt.subplot(1, 2, 2) # 1 ligne, 2 colonnes, met le graphe en index 2

# Charge les données.
# plt pointe vers le dernier subplot déclaré
plt.plot([3, 2, 1], [0, 0.5, 0.2])

plt.show()