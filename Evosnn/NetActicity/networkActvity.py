# -*- coding: utf-8 -*-
"""
Created on Wed Nov 15 13:23:34 2017

@author: YAQOOB
"""


import os
import numpy as np
import matplotlib

import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
import scipy.stats as stats





def get_gaussian2x(sample_x):
    return (2*(12*np.exp(-6*(((sample_x-0.7)/0.1)*((sample_x-0.7)/0.1)))+10))/0.24
   #return (1/(math.sqrt(2*np.pi*sigma)))*(np.exp(-(((sample_x-mu)*(sample_x-mu))/(2*s
   #igma*sigma)))))
def get_gaussianx(sample_x):
     return (12*np.exp(-6*(((sample_x-0.7)/0.1)*((sample_x-0.7)/0.1)))+10)/0.24

def get_gaussianhalfx(sample_x):
  return ((12*np.exp(-6*(((sample_x-0.7)/0.1)*((sample_x-0.7)/0.1)))+10)/2)/0.24

 
def plotFiringRate(x,fname):
    x_axis=x[:,0]
    y_axis=x[:,1]/0.24 #firing rate for 240 ms
    
    hist_x = np.arange(0,1,0.01) 
    hist_y = get_gaussianx(hist_x)  
    hist_2y = get_gaussian2x(hist_x)
    hist_3y = get_gaussianhalfx(hist_x)
    left, width = 0.1, 0.75
    bottom, height = 0.1, 0.75
    bottom_h = left_h = left + width + 0.05
    rect_histx = [left, bottom_h+0.05, width, 0.2]
    rect_scatter = [left, bottom, width, height]
    plt.figure(1, figsize=(8, 8))
 
    axHistx = plt.axes(rect_histx)
  
   
    axHistx.hist(x_axis,bins=100,histtype='bar',align='mid',label='input', alpha=0.9)
    axHistx.grid(True,which='major')
    axHistx.minorticks_on()
    
    axScatter = plt.axes(rect_scatter)
    
    axHistx.set_xlim(axScatter.get_xlim())
    #axHistx.xlabel('frequency')
    #axHist.setylim(axScatter.get_ylim())
    
    axScatter.scatter(x_axis,y_axis,color='g',cmap=plt.cm.get_cmap('hot'),linewidth=0.5,edgecolor='w',alpha=1)
    #plotting the Standard Sigmoid Function
    axScatter.plot(hist_x,hist_y,marker='^',color='r',alpha=0.2,linewidth=0.8)
    axScatter.plot(hist_x,hist_2y,marker='^',color='b',alpha=0.2,linewidth=0.8)
    axScatter.plot(hist_x,hist_3y,marker='^',color='y',alpha=0.2,linewidth=0.8)
    plt.title('Generating Sigmoid Function for SNN response in ' + fname)
    plt.xlabel('Input to Network')
    plt.ylabel('Firing Rate (hz)')
   # plt.axis([0,1,0,100])
    plt.grid(True,which='major',color='k')
    plt.minorticks_on()
      
   
    plt.savefig(fname+".png",bbox_inches='tight',dpi=300)
    plt.show()
    plt.close()
    return;
    
    
    
    
def plot(x,fname):
    if len(x) > 605:
           clockVal = len(x)-30
           skipVal =0
           gWidth=30
    else: 
           clockVal =len(x)-2
           skipVal = 50 #22*5-6
           gWidth=18
    #skipVal=0  
    #clockVal=350
    fig, (ax1, ax2,ax3, ax4,ax5, ax6,ax7) = plt.subplots(7, 1, sharex=True, sharey=False, figsize=(gWidth, 12))
    #clockVal= len(x)-2 #195
    clock=x[:,0][skipVal:clockVal]
    A=x[:,2][skipVal:clockVal]
    B=x[:,3][skipVal:clockVal]
    C=x[:,4][skipVal:clockVal]
    N0=x[:,5][skipVal:clockVal]
    N1=x[:,6][skipVal:clockVal]
    N2=x[:,7][skipVal:clockVal]
    output=x[:,1][skipVal:clockVal]

    
#    std = np.std(x) 
#    mean = np.mean(x)    
#    plt.plot(norm.pdf(x,mean,std))
#    plt.hist(x,normed=True) 
#    x.sort()
#    xmean = np.mean(x)
#    xstd = np.std(x)
#    pdf = stats.norm.pdf(x, xmean, xstd)
#    plt.plot(x, pdf)
    
#    fig = plt.figure()
#    fig.text(.5, -0.1, 'txt', ha='center')
    padVal=35
    fSize = 20
    ax1.plot(clock, A,'k-')
    ax1.set_ylabel('input A',  rotation=0, fontsize=fSize, labelpad=padVal)
    ax2.plot(clock,B, 'k-')
    ax2.set_ylabel('input B', rotation=0, fontsize=fSize, labelpad=padVal)
    ax3.plot(clock,C, 'k-')
    ax3.set_ylabel('input C', rotation=0, fontsize=fSize, labelpad=padVal)

    
    
    ax4.plot(clock,N0, 'm-')
    ax4.set_ylabel('\nN2\nLock', rotation=0, fontsize=fSize, labelpad=padVal)
    ax5.plot(clock,N1, 'm-')
    ax5.set_ylabel('\nN1\nSwitch', rotation=0, fontsize=fSize, labelpad=padVal)
    ax6.plot(clock,N2, 'm-')
    ax6.set_ylabel('\nN0\nAccept', rotation=0, fontsize=fSize, labelpad=padVal)
   
    
    ax7.plot(clock,output, 'g-')
    ax7.set_ylabel('\nOutput', rotation=0, fontsize=fSize, labelpad=padVal)
    ax7.set_xlabel('Time [ms]', fontsize=fSize)
    
    matplotlib.rc('xtick', labelsize=18) 
    matplotlib.rc('ytick', labelsize=18)
#    plt.title('Voltage traces of network with noise vs. without noise')
#    plt.subplot(3,1,2)
#    plt.plot(clock,valNoise0, 'r-',label='fitness ')
    miny=-100
    maxy=0
    # ax4.set_ylim([miny, maxy])
    # ax5.set_ylim([miny, maxy])
    # ax6.set_ylim([miny, maxy])
    # ax7.set_ylim([miny, maxy])
       
    
#    plt.tight_layout()
    
#    
#    plt.xlabel('Time [ms]')
#    plt.ylabel('Voltage [mV]')
#    ax1.set_xlabel('Vresting EL')
# Make the y-axis label, ticks and tick labels match the line color.
#    ax1.set_ylabel('fitness', color='b')
#    ax1.tick_params('y', colors='b')
#
#    ax2 = ax1.twinx()
##    s2 = np.sin(2 * np.pi * t)
#    ax2.plot(noise, correct, 'g.',label='TP')
#    ax2.plot(noise, wrong, 'r.',label='TN')
#    ax2.set_ylabel('Accuracy', color='g')
#    ax2.tick_params('y', colors='r')

  
#    fig.tight_layout()
#    fig.legend(numpoints=1,             #Set the number of markers in label
#           loc=('upper left'))
    
#    plt.plot(noise,fitness,'b^')
#    plt.plot(noise,correct,'g.',label='TP')
#    plt.plot(noise,wrong,'r.',label='TN')
#    plt.legend(numpoints=1,             #Set the number of markers in label
#           loc=('upper left'))
    

#    prob_over_2 = stats.norm.sf(x=2,loc = 0,scale= xstd) 
#    prob_under_minus2 = stats.norm.cdf(x=-2,loc = 0,scale= xstd) 
##    
##    prob_under_less_than2 = stats.norm.cdf(x=2,loc = 0,scale= 2) 
##    prob_under_minus2 = stats.norm.cdf(x=-2,loc = 0,scale= 2) 
#    prob_1std_dev=1.0-(prob_over_2+prob_under_minus2)
#    plt.text(x=-1, y=0.03, s= round(prob_1std_dev,5))
#    plt.text(x=-3.6, y=0.03, s= round(prob_under_minus2,3))
#    plt.text(x=2.2, y=0.03, s= round(prob_over_2,3))
#    
#    plt.text(x=-8, y = 0.18,s='std dev='+str(round(xstd,3)));
#    plt.text(x=-8, y = 0.160,s='mean='+str(round(xmean,3)));
#    
#    plt.title('Adding 2mv Guassian Noise' + fname)
#    plt.axvline(x=-2, color='g', linestyle='--', alpha = 0.3)
#    plt.axvline(x=2, color='g', linestyle='--', alpha = 0.3)
#    plt.axhline(y=0.120, color='r', linestyle='--')
##    plt.xlabel('Noise to Network (Vrest)')
##    plt.ylabel('Fitness')  
#    plt.grid(True)#,which='major',color='k')
#    plt.minorticks_on()
      
    plt.savefig(fname+".png",bbox_inches='tight',dpi=120)
    #plt.savefig("plot.png",bbox_inches='tight',dpi=300)
    plt.show()
    plt.close()
    
    return; 
        
rootDir = os.getcwd()
for dirName, subdirList, fileList in os.walk(rootDir):
    print('In the Directory: %s' % dirName)
    for fname in fileList:
     if fname.endswith(".dat"):
        x = np.loadtxt(fname,'float')
        plot(x,fname)
#           plotFiringRate(x,fname)