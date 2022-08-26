#####################
import os
import numpy as np
filename="DTFridgelab"
NumberJobs = 10000 #please check the number of particles you are simulating in each jobs
 
for i in range(NumberJobs):
         # change the JobScripts number
         #os.system("bsub -r < /home/pp59a/Ricochet_jobs/JobScripts1.sh")

         old_name="{}_{}".format(filename,0)
         new_name="{}_{}".format(filename,i)


         #input file
         fin = open("DTFridgelab_0.mac", "rt")
         #output file to write the result to
         if (i !=0):
             fout = open("{}_{}.mac".format(filename,i), "wt")
             for line in fin:
                 fout.write(line.replace(old_name,new_name))
         fin.close()
         if (i!=0):
              #os.system("cat {}_{}_{}.mac".format(filename,i,j))
              fout.close()
