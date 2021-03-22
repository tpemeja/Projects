import subprocess
Puissance_max = 4
import matplotlib.pyplot as plt
import numpy as np
import sys
moyenne = 5
Lx=[]
list_mode = sys.argv
pos = sys.argv[len(list_mode)-1]
list_mode.remove(pos)
list_mode.remove(sys.argv[0])
list_mode = list(set(list_mode))
nb_mode = len(list_mode)
Ly_mode=[]
for _ in range(nb_mode):
    Ly_mode.append([])

for k in range(Puissance_max):
    for i in range(10**k,10**(k+1),10**k):
        Lx.append(i)
        for mode in range(nb_mode):
            result = 0
            for j in range(moyenne):
                process = subprocess.Popen(["./install/bin/"+list_mode[mode],str(i)], stdout=subprocess.PIPE)
                pout, perr = process.communicate()
                result += float(pout.decode("utf-8").split(" ")[int(pos)])
            result = (result/moyenne)
            Ly_mode[mode].append(result)
        #print("Resultat pour ",i," "*((Puissance_max-1)-k),":",result)

max_y = max(max(Ly_mode))
min_y = min(min(Ly_mode))
max_x = max(Lx)
min_x = min(Lx)
plt.axis([min_x, max_x, min_y, max_y])
plt.yticks(np.linspace(min_y,max_y,10,endpoint=True))
for mode in range(nb_mode):
    plt.plot(Lx, Ly_mode[mode],label=list_mode[mode])
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Nombre de threads')
plt.ylabel('Temps en us')
plt.title("Comparaison des performances")
plt.legend()
plt.show()
