#to generate example data
import numpy as np

#my library.
import physPlot

x = np.linspace(0,10,500)
y = np.cos(x)

physPlot.lineplot(x,y,window_name="My title",line_thickness=5)
