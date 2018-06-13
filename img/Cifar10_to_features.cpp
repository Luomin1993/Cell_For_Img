#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
//#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
//g++ -I/usr/local/opencv2/include/ -o Cifar10_to_features Cifar10_to_features.cpp  -L/usr/local/opencv2/lib -lopencv_objdetect -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_core -lopencv_nonfree
using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    FILE *fpr = fopen("./cifar-10-batches-bin/data_batch_1.bin","rb");//打开cifar-10的一个文件
    if(fpr==NULL)
    {
        cout<<"文件打开失败!"<<endl;
        fclose(fpr);
        return 0;
    }
    int labelr(0);//存label
    char buffer = 0;//缓存
    int yrow = 2;//行图片数
    int xcol = 2;//列图片数
    int image_num;
    //Mat image(32*yrow,32*xcol,CV_8UC3,Scalar::all(0));//opencv 的Mat对象，用来存图片的像素矩阵
    //重点是这个循环
    //Cifar file stream:[[label:(R),(G),(B)],[label:(R),(G),(B)],[label:(R),(G),(B)],[label:(R),(G),(B)]...]
    std::vector<Mat> RES;
    FILE* fp_csv = fopen("label.csv","a");
    for(int y = 1;y<=yrow;y++)//循环行图片
    {
        for(int x = 1;x<=xcol;x++)//列图片
        {
            Mat image(32,32,CV_8UC3,Scalar::all(0));//opencv 的Mat对象，用来存图片的像素矩阵
            fread(&labelr,sizeof(char),1,fpr);//获取每张图片前的label  不要忘记了
            cout<<"label:"<<labelr<<endl;
            for(int b = 2;b>=0;b--)//循环RGB颜色
            {
                for(int j = 0;j<32;j++)//循环行像素
                {
                    for(int i = 0;i<32;i++)//循环列像素
                    {
                        fread(&buffer,sizeof(char),1,fpr);
                        image.at<Vec3b>(j,i)[b] = buffer;//用at来获取数据 ,还有其他办法，大家可以找找
                    }
                }
            }
            imwrite("./CIFAR10/"+std::to_string(x*y)+".jpg", image);
            fprintf(fp_csv,"%d\n",labelr);
            char cmd[512];
            
            string cmd_str_1 = "./color_feature ./CIFAR10/"+std::to_string(x*y)+".jpg";
            sprintf(cmd, cmd_str_1.data());
            //popen(cmd, "r");
            system(cmd);
            
            string cmd_str_2 = "./shape_feature ./CIFAR10/"+std::to_string(x*y)+".jpg";
            sprintf(cmd, cmd_str_2.data());
            //popen(cmd, "r");
            system(cmd);

            string cmd_str_3 = "./texture_feature ./CIFAR10/"+std::to_string(x*y)+".jpg";
            sprintf(cmd, cmd_str_3.data());
            //popen(cmd, "r");
            system(cmd);
            //RES.push_back(image);
            //show the image one by one
            //if(y==0 && x==0){imshow("1",image);waitKey(100);}
            //sleep(3);
        }
    }
    //imshow("1",RES[10]);waitKey(100000);
    fclose(fpr);
    fclose(fp_csv);
    return 0;
}