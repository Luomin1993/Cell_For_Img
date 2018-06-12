#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include <iostream>  
#include <stdio.h>  
//g++ -I/usr/local/opencv2/include/ -o texture_feature texture_feature.cpp  -L/usr/local/opencv2/lib -lopencv_objdetect -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_core -lopencv_nonfree
using namespace std;  
using namespace cv;  
  
//vconcat (B,C,A); //等同于A=[B;C]列数不变
//hconcat (B,C,A); //等同于A=[B C]行数不变

void saveMat(cv::Mat inputMat,char* filename)
{
    FILE* fpt = fopen(filename,"a");
    int rows = inputMat.rows;
    int clos = inputMat.cols;
    for (int i = 0; i < rows;i++)
    {
          for(int j = 0;j<clos;j++)
          {
               if (j < clos-1)
                  fprintf(fpt,"%f,",inputMat.at<float>(i,j));
               else
                  fprintf(fpt,"%f\n",inputMat.at<float>(i,j));
          }
    }
    fclose(fpt);
}

void saveMatAsVec(cv::Mat inputMat,char* filename)
{
    FILE* fpt = fopen(filename,"a");
    int rows = inputMat.rows;
    int clos = inputMat.cols;
    for (int i = 0; i < rows;i++)
    {
          for(int j = 0;j<clos;j++)
          {
               /*if (j < clos-1)
                  fprintf(fpt,"%f,",inputMat.at<float>(i,j));
               else
                  fprintf(fpt,"%f\n",inputMat.at<float>(i,j));*/
               fprintf(fpt,"%f,",inputMat.at<float>(i,j));
          }
    }
    fprintf(fpt,"\n");
    fclose(fpt);
}

void save_pca_vec_to_csv_file(cv::Mat img,char* filename)
{
    int floor_num = 20;  
    cvtColor(img, img, CV_RGB2GRAY);
    PCA pca(img, Mat(), CV_PCA_DATA_AS_COL, floor_num);  
    //图片大小为400*362  
    //这里按COL的方式降维，保证列数不便，行数降低到120层  
    //所以可以发现打印的均值的规格为1*362  
    cout << "均值的规格：" << pca.mean.size() << endl;//均值  
    cout << "特征值的规格："<<pca.eigenvalues.size() << endl;//特征值  
    cout <<"特征向量的规格：" <<pca.eigenvectors.size() << endl;//特征向量  
  
    //Mat dst = pca.project(img);//映射新空间  
    //cout << dst;  
    //Mat src = pca.backProject(dst);//反映射回来  
    saveMatAsVec(pca.eigenvalues,filename);
}

/*Mat* cvSampleImageTextureExtraction(IplImage* img,IplImage* dst)
{  
    uchar* data=(uchar*)img->imageData;  
    int step=img->widthStep;  
    //IplImage* dst=cvCreateImage(cvSize(img->width,img->height),img->depth,1);  
    dst->widthStep=img->widthStep;  
  
    CvScalar s;  
    int tmp[8]={0};  
    int sum=0;int k=0;  
      
    for(int i=1;i<img->height-1;i++)  
        for(int j=1;j<img->width-1;j++)
        {  
            if(data[(i-1)*step+j-1]>data[i*step+j])  
                tmp[0]=1;  
            else   
                tmp[0]=0;  
            if(data[i*step+(j-1)]>data[i*step+j])   
                tmp[1]=1;  
            else   
                tmp[1]=0;  
            if(data[(i+1)*step+(j-1)]>data[i*step+j])   
                tmp[2]=1;  
            else   
                tmp[2]=0;  
            if (data[(i+1)*step+j]>data[i*step+j])   
                tmp[3]=1;  
            else   
                tmp[3]=0;  
            if (data[(i+1)*step+(j+1)]>data[i*step+j])   
                tmp[4]=1;  
            else tmp[4]=0;  
            if(data[i*step+(j+1)]>data[i*step+j])   
                tmp[5]=1;  
            else   
                tmp[5]=0;  
            if(data[(i-1)*step+(j+1)]>data[i*step+j])   
                tmp[6]=1;  
            else   
                tmp[6]=0;  
            if(data[(i-1)*step+j]>data[i*step+j])   
                tmp[7]=1;  
            else   
                tmp[7]=0;  
  
            for(k=0;k<=7;k++)  
                sum+=abs(tmp[k]-tmp[k+1]);  
            sum=sum+abs(tmp[7]-tmp[0]);  
            if (sum<=2)  
                s.val[0]=(tmp[0]*128+tmp[1]*64+tmp[2]*32+tmp[3]*16+tmp[4]*8+tmp[5]*4+tmp[6]*2+tmp[7]);  
            else   
                s.val[0]=59;   
            cvSet2D(dst,i,j,s);  
        }  
        Mat res = Mat(const IplImage* dst, bool copyData=true);
        return &res;
} */

/** @函数 main */  
int main( int argc, char** argv )  
{  
    Mat src, dst;  
    /// 装载图像  
    src = imread( argv[1], 1 );  
    
    if( !src.data )  
    { return -1; }  
    
    //dst = cvSampleImageTextureExtraction(&IplImage(src),&IplImage(src));
    cv::Sobel(src,dst,CV_8U,1,0,3,0.4,128);
    //namedWindow("sobel", CV_WINDOW_AUTOSIZE );  
    //imshow("sobel", dst );
    //waitKey(0);
    save_pca_vec_to_csv_file(dst,"./texture.csv"); 
    return 0;
}  

