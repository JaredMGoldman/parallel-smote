from matplotlib import pyplot as plt
import numpy as np
import sys

def __main__():
  analyze(sys.argv[1])


def analyze(csv_file):
  # each line is N,p,patime,seqtime
  mat = np.genfromtxt(csv_file, delimiter=',')
  n_dict = {}
  p_dict = {}
  for arr in mat:
    if arr[0] not in n_dict:
      n_dict[arr[0]] = 1
    if arr[1] not in p_dict:
      p_dict[arr[1]] = 1
  ps = p_dict.keys()
  ps = list(ps)
  ps.sort()
  ns = n_dict.keys()
  ns = list(ns)
  ns.sort()

  for i in range(len(ps)):
    p_dict[ps[i]] = i
  for i in range(len(ns)):
    n_dict[ns[i]] = i

  data = np.zeros((len(ns),len(ps)))
  for arr in mat:
     data[n_dict[arr[0]],p_dict[arr[1]]] = arr[2]
  for i,arr in enumerate(data):
    n = ns[i]
    for j,elt in enumerate(arr):
      data[i,j] = (n*n / 1000000) / (elt + 0.001)
  seqData = np.zeros(len(ns))
  for i,arr in enumerate(mat):
    seqData[n_dict[arr[0]]] += arr[3]
  for i in range(len(ns)):
    seqData[i] = (ns[i] * ns[i] / 1000000) / (seqData[i] / len(ps))

  plt.figure()
  plot_series = []
  for i,arr in enumerate(data):
    line, = plt.plot(ps,arr,'-o',label="n=" + str(ns[i]))
    plot_series.append(line)
  plot_series = plot_series[::-1]
  ax = plt.gca()
  ax.set_xticks(ps)
  ax.set_yscale('log')
  plt.title("Computation Rate of SMOTE Algorithm")
  plt.xlabel("num processors")
  plt.ylabel("MFLOPS")
  plt.legend(handles=plot_series,fancybox=True,shadow=True)
  plt.show()

  plt.figure()
  plot2_series = []
  for i,arr in enumerate(data.T):
    line, = plt.plot(ns,arr,'-o',label="p=" + str(ps[i]))
    plot2_series.append(line)
  seqLine, = plt.plot(ns,seqData,'-o',label="sequential")
  plot2_series = plot2_series[::-1]
  plot2_series.append(seqLine)
  plt.title("Speedup of SMOTE Algorithm")
  plt.xlabel("n")
  plt.ylabel("MFLOPS")
  plt.legend(handles=plot2_series,fancybox=True,shadow=True)
  plt.show()

  exit()


if __name__ == "__main__":
  __main__()
