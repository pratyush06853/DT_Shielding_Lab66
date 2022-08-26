#####################
import os
import numpy as np
filename="DoseCalculation"
testx="/IronFilter/det/setTestX"
testy="/IronFilter/det/setTestY"

x =np.linspace(-5, 5, 40)
y =np.linspace(-5, 5, 40)


for i in range(len(x)):
    for j in range(len(y)):
         # change the JobScripts number
         #os.system("bsub -r < /home/pp59a/Ricochet_jobs/JobScripts1.sh")
         oldtestx="{} {} m".format(testx,-5)
         newtestx="{} {} m".format(testx,x[i])

         oldtesty="{} {} m".format(testy,-5)
         newtesty="{} {} m".format(testy,y[j])

         old_name="{}_{}_{}".format(filename,0,0)
         new_name="{}_{}_{}".format(filename,i,j)


         #input file
         fin = open("DoseCalculation_0_0.mac", "rt")
         #output file to write the result to
         if (i !=0 or j!=0):
             fout = open("{}_{}_{}.mac".format(filename,i,j), "wt")
             #for each line in the input file
             #print("{} is replaced by {}".format(oldtestx,newtestx))
             #print("{} is replaced by {}".format(oldtestx,newtestx))
             #print("{} is replaced by {}".format(oldtestx,newtestx))
             for line in fin:
                 fout.write(line.replace(oldtestx,newtestx).replace(oldtesty,newtesty).replace(old_name,new_name))
                 #fout.write(line.replace(oldtestx,newtesty))
                 #fout.write(line.replace(old_name,new_name))
         fin.close()
         if (i!=0 or j!=0):
              #os.system("cat {}_{}_{}.mac".format(filename,i,j))
              fout.close()
