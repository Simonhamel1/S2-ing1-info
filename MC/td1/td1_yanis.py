from math import exp
##########################################################################
# loi de poisson
##########################################################################

import numpy as np

def proba_poisson_egal(lam, k):
    current_term = exp(-lam)
    
    for i in range(1, k + 1):
        current_term *= lam / i
        if i == k:
            return current_term
    
    return current_term


def proba_poisson_inferieur(lam, k):
    current_term = exp(-lam)
    cumulative_proba = current_term

    for i in range(1, k + 1):
        current_term *= lam / i
        cumulative_proba += current_term
        
    return cumulative_proba

tab1 = [proba_poisson_egal(7, k) for k in range(0, 20)]
tab2 = [proba_poisson_inferieur(7, k) for k in range(0, 20)]

# Theorique 
esperance_theo = 7
variance_theo = 7

# empirique
esperance_emp = 0
variance_emp = 0

for k in range(0, 20):
    esperance_emp += k * tab1[k]
    variance_emp += (k ** 2) * tab1[k]

variance_emp -= esperance_emp ** 2

print(f"esperance theorique : {esperance_theo}")
print(f"esperance empirique : {esperance_emp:.4f}")
print(f"variance theorique : {variance_theo}")
print(f"variance empirique : {variance_emp:.4f}")

import matplotlib.pyplot as plt
plt.bar(range(0, 20), tab2, color='r', alpha=0.8)
plt.bar(range(0, 20), tab1, color='b')
plt.title(f'Loi de Poisson avec λ = 7')
plt.xlabel('k')
plt.ylabel('Probabilité')
plt.legend(['P(X ≤ k)', 'P(X = k)'])
plt.grid(axis='y', alpha=0.3)
plt.grid(axis='x', alpha=0.3)
plt.show()


##########################################################################
# loi binomiale
##########################################################################

def proba_binomiale_egal(n, p, k):
    current_term = (1 - p) ** n
    
    if k == 0:
        return current_term
    
    ratio = p / (1 - p)
    
    for i in range(1, k + 1):
        current_term *= (n - i + 1) / i * ratio
        
    return current_term


def proba_binomiale_inferieur(n, p, k):
    current_term = (1 - p) ** n
    cumulative_proba = current_term
    
    ratio = p / (1 - p)

    for i in range(1, k + 1):
        current_term *= (n - i + 1) / i * ratio
        cumulative_proba += current_term
        
    return cumulative_proba

n = 10
p = 0.5

tab1 = [proba_binomiale_egal(n, p, k) for k in range(0, n + 1)]
tab2 = [proba_binomiale_inferieur(n, p, k) for k in range(0, n + 1)]

# Théorique
esperance_theo = n * p
variance_theo = n * p * (1 - p)

# Empirique (calculé à partir de notre distribution tab1)
esperance_emp = 0
variance_emp = 0

for k in range(0, n + 1):
    esperance_emp += k * tab1[k]
    variance_emp += (k ** 2) * tab1[k]

variance_emp -= esperance_emp ** 2

print(f"\nEspérance théorique : {esperance_theo:.4f}")
print(f"Espérance empirique : {esperance_emp:.4f}")
print(f"Variance théorique  : {variance_theo:.4f}")
print(f"Variance empirique  : {variance_emp:.4f}")


plt.bar(range(0, 10 + 1), tab2, color='r', alpha=0.8, label='P(X ≤ k)')
plt.bar(range(0, 10 + 1), tab1, color='b', label='P(X = k)')
plt.title(f'Loi Binomiale avec n=10, p=0.5')
plt.xlabel('k')
plt.ylabel('Probabilité')
plt.legend()
plt.grid(axis='y', alpha=0.3)
plt.show()    
