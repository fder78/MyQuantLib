import pandas as pd
import numpy as np
data = pd.read_csv("results.csv", index_col=0)
sens = data.ix[:,::-1].diff(axis=1)
#sens["total"] = data["0"]
sens.ix[:,0] = data.ix[:,-1]
sens = sens.ix[:,::-1].T
sens.columns = sens.columns.astype(float) / 10.0
sens.index = sens.index.astype(float)
sens.plot(kind='line', legend=False, grid=True)

c = np.array([10,25,50,75,100]) / 10.0
delta = pd.DataFrame(index = sens.index)
gamma = pd.DataFrame(index = sens.index)
for i in c:
    delta[i] = (sens[i] - sens[-i])/2/i*10
    gamma[i] = (sens[i] + sens[-i])/((i/10)**2)
delta.plot.bar(x=delta.index)
gamma.ix[:,2.5:10].plot(kind='bar')