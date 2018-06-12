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
#include <unistd.h>
#include <string>
//g++ -I/usr/local/opencv2/include/ -o Cifar10_to_opencv Cifar10_to_opencv.cpp  -L/usr/local/opencv2/lib -lopencv_objdetect -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_core -lopencv_nonfree
using namespace std;
using namespace cv;

/*bool ReadCifar10DataBatch(const string& dir, const string& batchName, size_t imgCount, vector<Mat>& images, vector<int>& labels)
{
    const int PATCH_SIZE = 32;          //图像块的尺寸: 32*32
    const int N_CHANEL = 3;             //通道数
    const int LINE_LENGTH = PATCH_SIZE * PATCH_SIZE * N_CHANEL + 1;//以字节为单位

    bool isSuccess = false;

    fstream fs(dir + batchName, ios::in | ios::binary);//以二进制方式读取

    if (fs.is_open())
    {
        cout << "成功打开文件: " << batchName << endl;
        char buffer[LINE_LENGTH];
        for (size_t imgIdx = 0; imgIdx < imgCount; imgIdx++)
        {
            fs.read(buffer, LINE_LENGTH);
            int class_label = (int)buffer[0];//类别标签:buffer[0]
            Mat red_img(32, 32, CV_8UC1, &buffer[1]);//红色通道：buffer[1->1024]
            Mat green_img(32, 32, CV_8UC1, &buffer[1025]);//绿色通道：buffer[1025->2048]
            Mat blue_img(32, 32, CV_8UC1, &buffer[2049]);//蓝色通道：buffer[2049->3072]
            vector<Mat> bgrMats;bgrMats.push_back(blue_img); bgrMats.push_back(green_img); bgrMats.push_back(red_img);//OpenCV的通道顺序是BGR
            Mat rgb_img;
            cv::merge(bgrMats, rgb_img);//RGB通道融合
            //将样本和对应的标签加入集合
            images.push_back(rgb_img);
            labels.push_back(class_label);
        }
        isSuccess = true;
    }
    else
    {
        cout << "无法打开文件: " << batchName << endl;
        isSuccess = false;
    }

    fs.close();
    return isSuccess;
}

int main(int argc, char* argv[])
{
    const string dir = "./cifar-10-binary/cifar-10-batches-bin\\";
    const string class_names[10] =
    {
        "airplane", "automobile", "bird", "cat", "deer", "dog", "frog", "horse", "ship", "truck"
    };
    const string batch_names[6] =
    {
        "data_batch_1.bin", "data_batch_2.bin", "data_batch_3.bin",
        "data_batch_4.bin", "data_batch_5.bin", "test_batch.bin"
    };

    size_t ImgCountPerBatch = 10000;
    vector<Mat> images;
    vector<int> labels;
    bool success = ReadCifar10DataBatch(dir, batch_names[2], ImgCountPerBatch, images, labels);
    if (success)
    {
        for (size_t imgIdx = 0; imgIdx < images.size(); imgIdx++)
        {
            Mat BigImg; cv::resize(images[imgIdx], BigImg, Size(128, 128));
            imshow("cifar image", BigImg);
            cout << "image index: "<<imgIdx<<"---->class label,name :" 
                << labels[imgIdx] << "<->" << class_names[labels[imgIdx]] << endl;
            cv::waitKey(5);
        }
    }

    system("pause");
    return 0;
}*/

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
    int yrow = 20;//行图片数
    int xcol = 20;//列图片数
    int image_num;
    //Mat image(32*yrow,32*xcol,CV_8UC3,Scalar::all(0));//opencv 的Mat对象，用来存图片的像素矩阵
    //重点是这个循环
    //Cifar file stream:[[label:(R),(G),(B)],[label:(R),(G),(B)],[label:(R),(G),(B)],[label:(R),(G),(B)]...]
    std::vector<Mat> RES;
    for(int y = 0;y<=yrow-1;y++)//循环行图片
    {
        for(int x = 0;x<=xcol-1;x++)//列图片
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
            //RES.push_back(image);
            //show the image one by one
            //if(y==0 && x==0){imshow("1",image);waitKey(100);}
            //sleep(3);
        }
    }
    //imshow("1",RES[10]);waitKey(100000);
    fclose(fpr);
    //imshow("1",image);//显示图片
    //waitKey(0);//据说没有这个就不能显示图片  没研究><!
    return 0;
}