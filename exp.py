
# class OBJ(object): 
#     # _dict = None;
#     # position=0;
#     # Linked_Output_Nuerons = [];
#     # W_Output              = [];
#     # Linked_Input_Nuerons  = [];
#     # W_Input               = [];
#     # def __new__(cls, *args, **kwargs): 
#     #     obj = super(Nueron).__new__(cls, *args, **kwargs); 
#     #     if cls._dict is None: cls._dict = obj.__dict__;
#     #     else: obj.__dict__ = cls._dict;
#     #     return obj;

#     def out_link(self,nueron):
#         self.Linked_Output_Nuerons.append(nueron);
#         self.W_Output.append(0.0);

#     def in_link(self,nueron):
#         self.Linked_Input_Nuerons.append(nueron);
#         self.W_Input.append(0.0);    

class OBJ(object):
    """docstring for OBJ"""
    #arg =  0;
    #Arr = [];
    def __init__(self, arg):
        super(OBJ, self).__init__()
        self.arg = arg
        self.Arr = [];
        

def exp():
    obj1 = OBJ(1);obj2 = OBJ(2);
    obj1.Arr.append(1);
    print 'Arr of obj1: ' + str(obj1.Arr);
    print 'Arr of obj2: ' + str(obj2.Arr);

if __name__ == '__main__':
    exp();        