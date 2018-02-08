import matplotlib.pyplot as plt

with open("output.txt") as f:
    content = f.readlines()
# you may also want to remove whitespace characters like `\n` at the end of each line
content = [x.strip() for x in content] 
#print content

x1=[]
y1=[]
y2=[]
y3=[]
y4=[]
y5=[]

#print type(content[1])

content = map(float,content)

i=0
while i<len(content):
	x1.append(content[i])
	y1.append(content[i+1])
	y2.append(content[i+2])
	y3.append(content[i+3])
	y4.append(content[i+4])
	y5.append(content[i+5])
	i=i+6

#print x1
#print y1
# plotting the line 1 points 
plt.plot(x1, y1, label = "FCFS",marker='o',markerfacecolor='black', markersize=6)
 
# plotting the line 2 points 
plt.plot(x1, y2, label = "Round Robin(d=1)",marker='o',markerfacecolor='black', markersize=6)

# plotting the line 3 points 
plt.plot(x1, y3, label = "Round Robin(d=2)",marker='o',markerfacecolor='black', markersize=6)

# plotting the line 4 points 
plt.plot(x1, y4, label = "Round Robin(d=5)",marker='o',markerfacecolor='black', markersize=6)

# plotting the line 5 points 
plt.plot(x1, y5, label = "Pre-emptive SJF",marker='o',markerfacecolor='black', markersize=6)
 
# naming the x axis
plt.xlabel('Number of Processes')
# naming the y axis
plt.ylabel('Average turnaround time')
# giving a title to my graph
plt.title('ATN vs N')
 
# show a legend on the plot
plt.legend()
 
# function to show the plot
plt.show()


