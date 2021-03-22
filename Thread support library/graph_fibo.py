import subprocess
import matplotlib.pyplot as plt
import numpy as np
import sys
import numpy as np
moyenne = 10

Lx=[]

list_mode = sys.argv
nb = int(list_mode[len(list_mode)-1])
list_mode.remove(list_mode[len(list_mode)-1])
list_mode.remove(sys.argv[0])
list_mode = list(set(list_mode))
nb_mode = len(list_mode)
Ly_mode=[]

for _ in range(nb_mode):
    Ly_mode.append([])


for i in range(nb):
    for mode in range(nb_mode):
        result = 0
        for j in range(moyenne):
            process = subprocess.Popen(["./install/bin/"+list_mode[mode],str(i)], stdout=subprocess.PIPE)
            pout, perr = process.communicate()
            result += float(pout.decode("utf-8").split(" ")[6])
        result = (result/moyenne)
        Ly_mode[mode].append(float(result))
    Lx.append(int(pout.decode("utf-8").split(" ")[4]))
        #print("Resultat pour ",i," "*((Puissance_max-1)-k),":",result)


#max_y = max(max(Ly_mode))
#min_y = min(min(Ly_mode))
#max_x = max(Lx)
#min_x = min(Lx)
#plt.axis([min_x, max_x, min_y, max_y])
#plt.yticks(np.linspace(min_y,max_y,10,endpoint=True))
for mode in range(nb_mode):
    plt.plot(Lx, Ly_mode[mode],label=list_mode[mode])
plt.yscale('log')
plt.xscale('log')
plt.xlabel('Nombre de thread')
plt.ylabel('Temps en us')
plt.title("Comparaison des performances")
plt.legend()
plt.show()
