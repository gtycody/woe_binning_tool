import pandas as pd
import numpy as np
import math

#This package is mean to perform WOE binning for a dataframe with Nan value


# This function calculate WOE value based on the cut method


# data_input type: dataframe with 2 columns and mutiple rows the name of 2nd col must be 'tag'
# cut_num: total cuts number/ total segment minus one
# cut_method: 1: cut by equal distance / 2: cut bu equal sample size

def _woe_calculation(data_input, cut_num, cut_method):
    temp_df = data_input
    target_col_name = data_input.columns[0]
    print(data_input.dtypes[0])
    
    #performing WOE for categorical characteristics
    if data_input.dtypes[0] == "object":
        temp = data_input
        print("This col type is object\n")
        print(temp_df)
        value_count = temp_df.groupby(by = [target_col_name,'tag'])
        value_count = value_count.size()
        
        tag_count = pd.value_counts(temp_df['tag'])

        # convert value_count to list vcls
        vcls = list(value_count)

        for i in tag_count.index:
            if i == 0:
                tgn = tag_count[i]
            elif i == 1:
                tbn = tag_count[i]
         
        woe_value_ls = list()
        categ_name_ls = list()
        # also record total value to calculating the woe for Nan
        # gun = good user number / bun = bad user number

        #***** if worng plz release all line & print*******
        print(value_count)                               
        print(tag_count)                                 
        #print("tgn: ",tgn ,"tbn", tbn)                   
        #**************************************************
        
        gn, bn = 0,0
        #calculation woe value among different categories
        for i in range(int(len(vcls) / 2)):
            woe_value = math.log((vcls[2 * i] / tgn) / (vcls[2 * i + 1] / tbn))
            gn += vcls[2 * i]
            bn += vcls[2 * i + 1]     
            woe_value_ls.append(woe_value)
                    
        #calculate woe value for nan category
        tmp_name = list(value_count.index)
        for i in range(int(len(vcls) / 2)):
            categ_name_ls.append(tmp_name[2 * i][0])

        #combine two list to a dictionary which is better at changing value
        dc = dict(zip(categ_name_ls,woe_value_ls))

        #Testify if the list contain Nan value, if so calculated it and add 
        if gn < tgn and bn < tbn:
            woe_nan = math.log10(((tgn - gn) / tgn)/((tbn - bn) / tbn ))
            print("woe_nan: ",woe_nan)
            dc1 = {np.nan:woe_nan}
            dc.update(dc1)
    
        #apply value in
        print(dc)
        data_input[target_col_name] = data_input[target_col_name].apply(lambda x: dc[x])
        
        print(data_input)
        
        return data_input


    #performing WOE for numerical characteristics
    else:
        print("This col type is not object\n")
        if cut_method == "qcut":
            data_input[target_col_name] = pd.qcut(data_input[target_col_name],cut_num)
        elif cut_method == "cut":
            data_input[target_col_name] = pd.cut(data_input[target_col_name],cut_num)

        temp_df = data_input
        
        value_count = temp_df.groupby(by = [target_col_name,'tag'])
        value_count = value_count.size()
        
        tag_count = pd.value_counts(temp_df['tag'])

        # convert value_count to list vcls
        vcls = list(value_count)

        for i in tag_count.index:
            if i == 0:
                tgn = tag_count[i]
            elif i == 1:
                tbn = tag_count[i]
         
        woe_value_ls = list()
        categ_name_ls = list()
        # also record total value to calculating the woe for Nan
        # gun = good user number / bun = bad user number

        #***** if worng plz release all line & print*******
        print(value_count)                               
        print(tag_count)                                 
        #print("tgn: ",tgn ,"tbn", tbn)                   
        #**************************************************
        
        gn, bn = 0,0
        #calculation woe value among different categories
        for i in range(int(len(vcls) / 2)):
            woe_value = math.log((vcls[2 * i] / tgn) / (vcls[2 * i + 1] / tbn))
            gn += vcls[2 * i]
            bn += vcls[2 * i + 1]     
            woe_value_ls.append(woe_value)
                    
        #calculate woe value for nan category
        tmp_name = list(value_count.index)
        for i in range(int(len(vcls) / 2)):
            categ_name_ls.append(tmp_name[2 * i][0])

        #combine two list to a dictionary which is better at changing value
        dc = dict(zip(categ_name_ls,woe_value_ls))

        #Testify if the list contain Nan value, if so calculated it and add 
        if gn < tgn and bn < tbn:
            woe_nan = math.log10(((tgn - gn) / tgn)/((tbn - bn) / tbn ))
            print("woe_nan: ",woe_nan)
            dc1 = {np.nan:woe_nan}
            dc.update(dc1)
    
        #apply value in
        print(dc)
        data_input[target_col_name] = data_input[target_col_name].apply(lambda x: dc[x])
        
        print(data_input)
        
        return data_input
 
#def _iv_calculation():

data = pd.read_csv('~/desktop/woe_binning_tool/test2.csv')
_woe_calculation(data, 4, "cut")



#def auto_woe_iv():



#def auto_drop():




