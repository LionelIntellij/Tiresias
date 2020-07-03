#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Sun Sep  9 02:09:33 2018

@author: lionel
"""
import nltk
from re import split
import itertools
import numpy as np
from pandas import read_csv
import scipy as sci
from sklearn.feature_selection import chi2

class compute_ngram(object):
    def __init__(self,ngram ,file_gram = None):
        if file_gram:
           self.grams = self.set_gram(file_gram);
        else:
           self.grams = None
        self.ngram = ngram 
        
    def set_gram(self,file_gram):
        list_grams = []
        with open(file_gram,"r") as file: 
             for gram in file:
                 list_grams.append(gram.strip())
        return list_grams
    
    def set_gram_list(self , grams):
        self.grams = grams
        
    def update(self):
        instance_gram_new = {}
        for gram in self.grams:
            instance_gram_new[gram.strip().upper()] = 0
        return instance_gram_new
            
    def compute_gram(self,filename_referential , filename_feature , nbr_analysis ,label):
        instance_gram = self.update()
        Data_learn = read_csv(filename_referential,header=None)
        file_feature = open(filename_feature,"a")
        feature = []
        for Blocks_address in self.random_sampling(len(Data_learn),nbr_analysis):
            for Address in Blocks_address:
                for word in split('[^A-Z]',Data_learn[0][Address].strip()):
                    if len(word) < self.ngram:
                        continue
                    else:
                        gram = nltk.ngrams(word,self.ngram)
                        for list_gram in gram:
                            ngram = ''.join(list_gram)
                            if ngram in instance_gram:
                               instance_gram[ngram]+=1
            
            for gram in self.grams:
                feature.append(str(instance_gram[gram]))
            file_feature.write(';'.join(feature)+';'+label+'\n')
            feature = []
        file_feature.close()
        return instance_gram

    def compute_just_gram(self ,row):
        instance ={}
        for word in split('[^A-Z]',row.strip()):
            if len(word) < self.ngram:
                continue
            else:
                gram = nltk.ngrams(word,self.ngram)
                for list_gram in gram:
                    ngram = ''.join(list_gram)
                    if ngram in instance:
                       instance[ngram]+=1
                    else:
                       instance[ngram]=1
        return instance


    def random_sampling(self,nbr_individus ,nbr_analysis):  
        """
        Description :
        
        Args :
        """
        DifferentRecords = nbr_individus -nbr_analysis 
        if  DifferentRecords:
            nbr_value = int(nbr_individus/nbr_analysis)
            Adress = np.arange(0,nbr_individus)
            np.random.shuffle(Adress)
            for index in range(nbr_value):
                ind = index*nbr_analysis 
                yield Adress[ind:ind+nbr_analysis ]
        else:
            raise ValueError("incorrect argument")

  
def compute_khi2(X , Y,target_class):
    Y[Y!=target_class] = -1
    Y[Y!=-1] = 0
    Y[Y==-1] = 1
    return chi2(X,Y)
    
        
def compute_frequency(file_referential ,grams):
    compute_gram = compute_ngram(3)
    compute_gram.set_gram_list(grams)
    instance_gram = compute_gram.update()
    nbr_element= 0
    with open(file_referential ,"r") as file:
         for row in file:
             instance = compute_gram.compute_just_gram(row)
             nbr_element+=1
             for key ,value in instance.iteritems():
                 if key in instance_gram:
                    instance_gram[key]+=value;       
    return instance_gram ,nbr_element        
                         
    
def compute_all_gram(file_referential):
    compute_gram = compute_ngram(3);
    alphabetic = "abcdefghijklmnopqrstuvwxyz";
    all_grams = map(''.join, itertools.product(alphabetic.upper(), repeat=3))
    compute_gram.set_gram_list(all_grams)
    instance_gram = compute_gram.update()
    all_grams_keep = []
    with open(file_referential ,"r") as file:
         for row in file:
             instance = compute_gram.compute_just_gram(row)
             for key ,value in instance.iteritems():
                 if key in instance_gram:
                    instance_gram[key]+=value;
    for key , value in instance_gram.iteritems():
        if value > 1:
            all_grams_keep.append(key)
    return all_grams_keep        
    
                       
def get_contigence_chi2(filename_referential , grams):
    features =[]  
    nbr_elements = []
    target = range(len(filename_referential))
    for referential in filename_referential:
        instance ,nbr_element  = compute_frequency(referential ,grams )
        features.append(instance.values())
        nbr_elements.append(nbr_element)
    features_normalized = []
    for feature ,nbr_element in zip(features , nbr_elements):
        features_normalized.append(normalize_nbr_element(feature , 
                                                         nbr_element))
    return features_normalized, target 

def create_file_extract_gram(filename_referential ,filename_feature_chi2, all_gram ,nbr_analysis):
    compute_gram =compute_ngram(3)
    compute_gram.set_gram_list(all_gram)
    label = 0
    for referential in filename_referential:
        compute_gram.compute_gram(referential , filename_feature_chi2 
                                   , nbr_analysis ,str(label))
        label+=1
        
    
def normalize_nbr_element(feature ,nbr_element):
    feature_normalized = []
    for element in feature:
        feature_normalized.append((element / float(nbr_element)))
    return feature_normalized

if __name__ == '__main__':
   import pylab as pl
   all_gram = compute_all_gram("DicoFirstName.ref")   
   file_referential  =["DicoLastName.ref" ,"DicoFirstName.ref","DicoLocality.ref"]
   features , target = get_contigence_chi2(file_referential,all_gram)
   X = np.array(features)
   Y = np.array(target)
   liberty_degree = (len(Y)-1) * (X[0].size-1)
   critic_value = sci.stats.chi2.ppf(q = 0.95,df = liberty_degree) 
   stat = compute_khi2(X,Y,1)
   pl.figure(1)
   pl.plot(stat[0])
   print(critic_value)
   pl.figure(2)
   pl.plot(stat[1])
   
   #key = data.keys()
   #compute_chi2(data[:-1],data[])
   """
   all_gram = compute_all_gram("DicoFirstName.ref")     
   print(all_gram)
   nbr_analysis = 100
   file_referential  =["DicoLastName.ref" ,"DicoFirstName.ref","DicoLocality.ref"]
   filename_feature_chi2 = "feature_chi2_"+str(nbr_analysis)+".csv"
   create_file_extract_gram(file_referential ,
                            filename_feature_chi2, 
                            all_gram,nbr_analysis)
   Chi2_value = read_csv(filename_feature_chi2 ,sep=";" ,header =None)
   key= Chi2_value.keys()
   X= Chi2_value[key[:-1]].values
   Y= Chi2_value[key[-1]].values
   stat = compute_khi2(X ,Y , 1)
   pl.plot(stat[0])
   """
   
   
   """
   pas = 1000
   size_gram = len(all_gram)
   size_treated = pas
   size = min(size_gram ,size_gram)
   create_file_extract_gram(      all_gram[:size_gram])
   while (size_gram> size_treated)
   print(len(all_gram))
   """ 