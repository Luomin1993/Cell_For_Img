#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include <iostream>  
#include <stdio.h>  
//g++ -I/usr/local/opencv2/include/ -o color_feature color_feature.cpp  -L/usr/local/opencv2/lib -lopencv_objdetect -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_core -lopencv_nonfree
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
    int floor_num = 120;  
    //cvtColor(img, img, CV_RGB2GRAY);
    PCA pca(img, Mat(), CV_PCA_DATA_AS_COL, floor_num);  
    //图片大小为400*362  
    //这里按COL的方式降维，保证列数不便，行数降低到120层  
    //所以可以发现打印的均值的规格为1*362  
    cout << "均值的规格：" << pca.mean.size() << endl;//均值  
    cout << "特征值的规格："<<pca.eigenvalues.size() << endl;//特征值  
    cout <<"特征向量的规格：" <<pca.eigenvectors.size() << endl;//特征向量  
  
    Mat dst = pca.project(img);//映射新空间  
    //cout << dst;  
    //Mat src = pca.backProject(dst);//反映射回来  
    saveMatAsVec(dst,"./color.csv");
}

/** @函数 main */  
int main( int argc, char** argv )  
{  
    Mat src, dst;  
    /// 装载图像  
    src = imread( argv[1], 1 );  
    
    if( !src.data )  
      { return -1; }  
     
    /// 分割成3个单通道图像 ( R, G 和 B )  
    vector<Mat> rgb_planes;  
    split( src, rgb_planes );  
     
    /// 设定bin数目  
    int histSize = 255;  
     
    /// 设定取值范围 ( R,G,B) )  
    float range[] = { 0, 255 } ;  
    const float* histRange = { range };  
     
    bool uniform = true; bool accumulate = false;  
     
    Mat r_hist, g_hist, b_hist;  
     
    /// 计算直方图:  
    calcHist( &rgb_planes[0], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );  
    calcHist( &rgb_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );  
    calcHist( &rgb_planes[2], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );  
    Mat rgb_hist;
    hconcat (r_hist,g_hist,rgb_hist);hconcat (rgb_hist,b_hist,rgb_hist);

  
    //创建直方图画布 
    //int hist_w = 400; int hist_h = 400;  
    //int bin_w = cvRound( (double) hist_w/histSize );  
     
    //Mat histImage( hist_w, hist_h, CV_8UC3, Scalar( 0,0,0) );  
     
    /// 将直方图归一化到范围 [ 0, histImage.rows ]  
    //normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );  
    //normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );  
    //normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );  
     
    /// 在直方图画布上画出直方图  
    /*for( int i = 1; i < histSize; i++ )  
    {  
          line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,  
                           Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),  
                           Scalar( 0, 0, 255), 2, 8, 0  );  
          line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,  
                           Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),  
                           Scalar( 0, 255, 0), 2, 8, 0  );  
          line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,  
                           Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),  
                           Scalar( 255, 0, 0), 2, 8, 0  );  
     }*/  
      
     /// 显示直方图  
     //namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );  
     //imshow("calcHist Demo", histImage ); 
     save_pca_vec_to_csv_file(rgb_hist,"./color.csv"); 

     waitKey(0);  
     return 0;
}  

