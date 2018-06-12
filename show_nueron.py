#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import random

#⊙◐✺✸

'''
                        ▦--0.7--▧--0.5--▨--0.3--▩
                        |       |       |       |
                       0.2     0.5     0.8     0.3
                        |       |       |       |
                        ▢--0.0--▧--0.1--▨--0.1--▩
                        |       |       |       |
                       0.2     0.5     0.8     0.3
                        |       |       |       |
                        ▦--0.0--▧--0.1--▨--0.1--▩
'''

#▦----▧----▨----▩
#def draw_one_nueron(global_row,global_col,index_i,index_j,activision):
def draw_one_nueron(activision):
    if activision==0:
       return '▢';
    if activision<0.3:
       return '▢';
    if activision<0.7:
       return '▤';   
    return '▩';



def draw(global_row,global_col):
    Mat = np.random.uniform(0,0.8,(global_row,global_col));
    #print Mat;
    for index_i in range(global_row):
        for index_j in range(global_col):
            if index_j == global_col-1:print draw_one_nueron(Mat[index_i,index_j]);continue;
            print draw_one_nueron(Mat[index_i,index_j])+'--',
            print('%.1f'%random.random()),
            print'--',
        print '\n',    
        for index_j in range(global_col):
            print '|         ',
        print '';    
        for index_j in range(global_col):
            #print '0.2     ',
            print('%.1f       '%random.random()),
        print '';    
        for index_j in range(global_col):
            print '|         ',   
        print '';                     

'''
我们的记忆分为长期记忆（long-term memory）和短期记忆（short-term memory）;
其中长期记忆又分为程序性记忆（也称内隐性记忆，implicit memory）和陈述性记忆（也称外显型记忆，explicit memory）;
陈述性记忆又可以分为情景记忆（episodic memory）和语义记忆（semantic memory）;

经过神经科学家多年的探索，从实验和模型的角度均表明，语义记忆在大脑中是以分布式、稀疏编码的形式存在的。

2005年,Quiroga等人在大脑内侧颞叶(medial temporal lobe, MTL)中发现的概念细胞
中发现的概念细胞就是典型的语义记忆编码神经元，概念细胞对某个概念（如苹果）的编码十分稳定，
当你看到不同颜色、不同角度的苹果，甚至是听到有人说“苹果”两个字，或是闻到苹果的味道时，这个苹果概念细胞都会放电。

来自美国的科学家利用统计学的方法分析神经元放电数据,为情景记忆同样采用分布式、稀疏编码的模式提供了证据支持。

这表明,仅有很少的神经元参与了情景记忆的提取,而其余的神经元则受到了这些编码神经元的抑制。

稀疏性可以体现在两个方面：
一方面是一个神经元生命周期的稀疏度（lifetime sparseness），即一个神经元在其生命周期内编码刺激数量的百分比。
另一方面是神经元群体的稀疏度（population sparseness），即参与编码一种刺激的神经元数量的百分比。
大量研究表明，这两方面的稀疏度很相近，因此，人脑对情景记忆的lifetime和population编码稀疏度很可能低于2.5%。

                                   

                                   神经网络是如何生成的
在现代的神经网络算法中，网络都是开始估计一个初值，在不断地试验中，确定一个比较合适的规模。
而生物的生长是从一个细胞开始分化的。人脑也并不是一下子产生了一个巨大的网络，在这个过程中，神经细胞应该也是很早就开始了不停的活动，
DNA和人的生长过程共同决定了人脑的结构，而不仅仅是DNA。比如，小脑的形成可能是因为其处于身体和大脑之间，
由于生长过程中感觉和运动神经末梢不停的刺激，才形成了其独特的结构。在大脑中，由于子宫环境比较简单，大脑能得到的信息单一，但也建立了基本输入输出的反射。
所以，初生婴儿就能对声音和颜色有反应。随着出生后输入信息量的增多，婴儿开始一层层的构建模式，最后一步步产生了智能。
由此，神经网络的层次及模式不是一开始就确定的，是根据输入、输出的信息来决定的。
-----是一个一边训练，一边调整网络结构、层次的过程。-----
当前设计的系统都是有目的性的，所以能够根据全局的目标函数来调整和训练模型。人类的智能的目的虽然还没有共识，但可以先认为人类智能是没有目的的。
人类智能的产生是一个自适应的过程，而不是由全局的目标函数来训练的。
仅依靠全局的信息，无法指导微观上每个部分的分化，网络的神经元分化和连接的调整都应该主要依赖于其局部信息。





一些神经元细胞特性的猜测和讨论，可以有助于把和智能产生相关的部分抽取出来:

神经元细胞的大部分活动是依靠化学反应，有些是不可逆反应。这个过程需要不断的反应物质和能量的供给，一旦能量跟不上，其反应可能变得迟钝。
从这一点来看，神经元的记忆是可以通过其输入输出的变化来调整的，不一定需要通过全局的目标函数来调整。

上一点中提到的物质、能量短缺的影响，不仅会影响神经元细胞本身，也会对周围细胞活动产生抑制。

神经元的树突生长是比较慢的，可能要经过大量的刺激，才能产生有效的突触。

神经元细胞的空间结构。大脑皮层的皱褶展开后是一个平面，这个平面上的灰质细胞也有一定的层数。
对于灰质细胞的层次的作用，也产生了有意思的算法，比如Hierarchal Temporal Memory（HTM，这是我看到的最有趣的一个算法）。

细胞个体的可靠性是没有计算机高的，所以神经元细胞需要更强的冗余性。相邻细胞之间需要通过相互备份来产生冗余。

神经元细胞的生长分化。神经元细胞是在胚胎发育的过程中产生的，所以有从无到有的过程。在当前神经网络的研究中，网络的初始化和如何决定规模都是需要考虑的问题。




人脑中一般不是分层的结构。不分层结构的主要挑战有， 
1）如何抑制整合、激发过程中的振荡。虽然有神经网络算法是不分层的，但很容易发生信号的振荡，环路等，不容易解决实际问题。 
2）如何有意义的创建、删除神经元之间的连接。这里的有意义除了是连接的调整能够有助于解决问题，或简化模型。
另一方面，也需要这些调整是自组织的。所谓自组织，是通过神经元、或模式自身的信息就能够进行调整，而不是依靠大量宏观或外部的信息来进行调整。
如果依靠很多宏观和外部的信息，其实就是把记忆、运算挪到了外部。这就不是一个可扩展的神经网络了。 



人脑里面的模式数量大概在千万级，通过人工的方式，几乎是不可能完成的任务。具体的问题有，
1）如何高效的发现新模式。这里有两种思路，一种是设计一个模式产生器用来产生新的模式，并将其嵌入到已有的系统中。
另一种是让神经网络自身能够产生新的模式。这样产生的模式之间可能并没有清晰的界限，更像是大脑中网络的结构。
2）如何发现类似的模式，并将其合并。这对节省空间、提高计算效率、知识的举一反三都有很重要的意义。
这个问题对于输入输出定义很清晰的模式较容易，如果是人脑这样的没有清晰的模式界限的，就比较挑战了。
3）模型的通用性。大脑有一个一般化的网络结构，其灵活性非常大。即使某些专用区域失去了功能，
如听力相关的区域，其它区域通过一些训练，能够恢复大部分功能。



自组织是大脑非常重要的一个特点。自组织最大的好处是人工介入少，这是对智力生产力的解放，代表了下一代生产力。
系统层次的目标可以是能量最小、冲突最少或者是更高级的目标，如生存等。



'''



'''
P(△Wo|△O);
P(△Wi|△I);
P(0(.)|△O,△I);
P(N(.)|△O,△I);
'''
def Link(nueron_1,nueron_2,link_method):
    if link_method=='1to2':
       nueron_1.Linked_Output_Nuerons.append(nueron_2);
       nueron_1.W_Output.append(0.0);
       nueron_2.Linked_Input_Nuerons.append(nueron_1);
       nueron_2.W_Input.append(0.0);       
       return;
    # if link_method=='2to1':
    #    nueron_1.Linked_Output_Nuerons.append(nueron_2);
    #    nueron_1.W_Output.append(0.0);
    #    nueron_2.Linked_Input_Nuerons.append(nueron_1);
    #    nueron_2.W_Input.append(0.0);       
    #    return;


class Nueron(object):
    """docstring for Nueron"""
    def __init__(self, position):
        super(Nueron, self).__init__()
        self.position = position; #(index_i,index_j);
        self.Linked_Output_Nuerons = [];
        self.W_Output              = [];
        self.Linked_Input_Nuerons  = [];
        self.W_Input               = [];
        self.Input_Value           = 0;
        self.Output_Value          = 0;
        self.ac_value              = 0.5;

    # def out_link(self,nueron):
    #     self.Linked_Output_Nuerons.append(nueron);
    #     self.W_Output.append(0.0);

    # def in_link(self,nueron):
    #     self.Linked_Input_Nuerons.append(nueron);
    #     self.W_Input.append(0.0);    

    def accept(self):
        for i in range(len(self.Linked_Input_Nuerons)):    
            self.Input_Value += self.W_Input[i]*self.Linked_Input_Nuerons[i].Output_Value;

    def send(self):
        #for i in range(len(self.Linked_Output_Nuerons)):
        #    self.Output_Value += self.W_Output[i]*self.Input_Value;
        self.Output_Value = self.activision(self.Input_Value);

    def grow(self,New_Input):
        delta_I = New_Input - self.Input_Value;
        # for index in range(len(self.W_Output)):
        #     #print delta_I;
        #     self.W_Output[index] -= 0.4*delta_I;
        #     that=self.Linked_Output_Nuerons[index];there_i_am = that.Linked_Input_Nuerons.index(self);
        #     self.Linked_Output_Nuerons[index].W_Input[there_i_am] -= 0.4*delta_I;
        # for index in range(len(self.W_Input)):
        #     #print delta_I;
        #     self.W_Input[index] -= 0.4*delta_I;
        #     that=self.Linked_Input_Nuerons[index];there_i_am = that.Linked_Output_Nuerons.index(self);
        #     self.Linked_Input_Nuerons[index].W_Output[there_i_am] -= 0.4*delta_I;    
        for index in range(len(self.W_Input)):
            self.ac_value -= 0.4*delta_I;
        #pass;

            
    def die(self):
        pass;        

    def activision(self,x):
        if (x-self.ac_value)>=0:return 1;
        return 0;    

    def print_info(self):
        print '*Position: '  +str(self.position),
        print '*Output Nuerons: '  +str([nue.position for nue in self.Linked_Output_Nuerons]),
        print '*Input Nuerons: '  +str([nue.position for nue in self.Linked_Input_Nuerons]),
        print '*Output Weights: '  +str(self.W_Output),
        print '*Input Weights: '  +str(self.W_Input);
                
def Link(nueron1,nueron2):
    nueron1.Linked_Output_Nuerons.append(nueron2);
    nueron1.W_Output.append(0.0);
    nueron2.Linked_Input_Nuerons.append(nueron1);
    nueron2.W_Input.append(0.0);       
    return;

def Experiment(num_of_nuerons):
    Nue = [];
    X1 = [];
    X2 = [];
    for i in range(num_of_nuerons):
        if i%2:X1.append(1);X2.append(0.6);continue;
        X1.append(0);X2.append(0.4);

    for position in range(num_of_nuerons):
        Nue.append(Nueron(position));
    #print [nue.position for nue in Nue];
    #print Nue;
    
    for position in range(len(Nue)-1):
        Link(Nue[position],Nue[position+1]);
        #Nue[position].print_info();Nue[position+1].print_info();

    #Link(Nue[0],Nue[1]);#Link(Nue[1],Nue[2]);Link(Nue[2],Nue[3]);
    #Nue[0].print_info();Nue[3].print_info();

    # nue1 = Nueron(1);nue2 = Nueron(2);nue3 = Nueron(3);nue4 = Nueron(4);
    # Link(nue1,nue2);Link(nue2,nue3);Link(nue3,nue4);
    # nue1.print_info();nue2.print_info();nue3.print_info();nue4.print_info();


    Y1  = [];
    Y2  = [];

    for position in range(num_of_nuerons):
        if position == 0:Nue[position].Input_Value=X1[0];continue;Nue[position].grow(X1[0]);Nue[position].send();
        #if position == num_of_nuerons-1:
        Nue[position].Input_Value=X1[position];Nue[position].accept();Nue[position].grow(X1[position]);Nue[position].send();

    for position in range(num_of_nuerons):
        Y1.append(Nue[position].Output_Value);
    print 'X1:'+str(X1);
    print 'Y1:'+str(Y1); 

    Nue.append(Nueron(num_of_nuerons));
    Link(Nue[-2],Nue[-1]);

    for position in range(len(Nue)):
        if position == 0:Nue[position].grow(X2[0]);Nue[position].Input_Value=X2[0];Nue[position].send();Nue[position].print_info();continue;
        #if position == num_of_nuerons-1:
        if position>=len(Nue)-1:Nue[position].grow(X2[-1]);Nue[position].Input_Value=X2[-1];Nue[position].accept();Nue[position].send();Nue[position].print_info();break;
        Nue[position].grow(X2[position]);Nue[position].Input_Value=X2[position];Nue[position].accept();Nue[position].send();Nue[position].print_info();


    for position in range(len(Nue)):
        Y2.append(Nue[position].Output_Value);
    print 'X2:'+str(X2);
    print 'Y2:'+str(Y2); 

if __name__ == '__main__':
    #draw(7,7); 
    print '=====================================================';
    #print '======== Experiment: P(N(.)|△O,△I)        ===========';
    #print '======== Experiment: P(△Wo|△O)            ===========';
    #print '======== Experiment: P(△Wi|△I)            ===========';
    print '======== Experiment: P(0(.)|△O,△I)        ===========';
    print '=====================================================';          
    Experiment(24);

