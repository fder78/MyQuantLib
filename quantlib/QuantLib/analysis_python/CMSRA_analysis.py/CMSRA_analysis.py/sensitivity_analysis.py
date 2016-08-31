import pandas as pd
import numpy as np
parm = [-5,-1,1,5]
data = pd.DataFrame()
for i in parm:
    d = pd.read_csv("results%d.csv"%i, header=None, index_col=0)
    if i==-10:
        data = d
    else:
        data = pd.concat([data,d])
    
years = [0,1,4,5,7,10,12,15,20,25,30,40,45]
sens = data.ix[:,::-1].diff(axis=1)
sens.iloc[:,0] = data.iloc[:,-1]
sens = sens.ix[:,::-1].T

sens.columns = sens.columns.astype(float)
sens.index = years
#sens.plot(kind='line', legend=False, grid=True)
data[1].plot(kind="bar")

c = np.array([1])
delta = pd.DataFrame(index = sens.index)
gamma = pd.DataFrame(index = sens.index)
for i in c:
    delta[i] = (sens[i] - sens[-i])/2/i
    gamma[i] = (sens[i] + sens[-i])/((i)**2)
delta.plot.bar(x=delta.index)
gamma.plot.bar(x=delta.index)