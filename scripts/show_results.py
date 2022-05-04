import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('out.csv')
df.plot(y='PAPI_L1_TCM', use_index=True)
plt.show()