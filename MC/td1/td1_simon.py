import numpy as np

import matplotlib.pyplot as plt

 

def tirage_discret(valeurs, probabilites):
	u = np.random.random()
	cumul = probabilites[0]
	i = 0
	while u > cumul:
		i += 1
		cumul += probabilites[i]
	return valeurs[i]

 

def echantillon_discret(N, valeurs, probabilites):
	ech = []
	for _ in range(N):
		ech.append(tirage_discret(valeurs, probabilites))
	return np.array(ech)

 

def proba_poisson(lambda_, kmax):
	valeurs = np.arange(0, kmax + 1)
	probas = np.zeros(kmax + 1)
	probas[0] = np.exp(-lambda_)
	for k in range(kmax):
		probas[k + 1] = probas[k] * (lambda_ / (k + 1))
	probas = probas / np.sum(probas)
	return valeurs, probas

 

def proba_binomiale(n, p):
	valeurs = np.arange(0, n + 1)
	probas = np.zeros(n + 1)
	probas[0] = (1 - p) ** n
	for k in range(n):
		probas[k + 1] = probas[k] * ((n - k) / (k + 1)) * (p / (1 - p))
	return valeurs, probas

 

def affichage_resultats(titre, ech, valeurs, probas_th):
	N = len(ech)
	moy_th = np.sum(valeurs * probas_th)
	var_th = np.sum(valeurs**2 * probas_th) - moy_th**2
	moy_emp = np.mean(ech)
	var_emp = np.var(ech)
	
	print("==============================================")
	print(titre)
	print("Moyenne théorique =", moy_th)
	print("Variance théorique =", var_th)
	print("Moyenne empirique =", moy_emp)
	print("Variance empirique =", var_emp)
	
	freq_emp = np.array([(ech == v).sum() / N for v in valeurs])
	
	plt.figure()
	plt.bar(valeurs, probas_th, alpha=0.6)
	plt.bar(valeurs, freq_emp, alpha=0.6)
	plt.show()

 

N = 1000

 

lambda_poisson = 5

kmax = 20

valP, probaP = proba_poisson(lambda_poisson, kmax)

echP = echantillon_discret(N, valP, probaP)

affichage_resultats("Loi de Poisson (lambda = 5)", echP, valP, probaP)

 

n = 18

p = 0.4

valB, probaB = proba_binomiale(n, p)

echB = echantillon_discret(N, valB, probaB)

affichage_resultats("Loi Binomiale", echB, valB, probaB)