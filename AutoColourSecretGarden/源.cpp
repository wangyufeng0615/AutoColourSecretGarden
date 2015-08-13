#include <opencv2/opencv.hpp>
#include <cmath>
#include <ctime>
#include <string>
using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    //载入，OPENCV2.0写法
    if (argc < 2)
    {
        return 0;
    }
    string InputPictureName = argv[1];
    Mat image1 = imread(InputPictureName);
    Mat image2;             //灰度化
    Mat image3;             //二值化
    Mat image4;             //彩色图

    //创建窗口
    namedWindow("AutoColored",0);
    resizeWindow("AutoColored", 600, 600);  //易于浏览但画质差，仅作示意
    
    //灰度化
    cvtColor(image1, image2, CV_BGR2GRAY);

    //二值化
    threshold(image2, image3, 127, 255, THRESH_BINARY);

    //恢复彩色图
    cvtColor(image3, image4, CV_GRAY2BGR);

    //init para
    srand(clock());
    int x = 0;
    int y = 0;
    Scalar temp;        //current point's color
    Scalar scalar1;     //constant parameter
    Rect ccomp;         //constant parameter

    while(1)
    {
        temp = image4.at<Vec3b>(y, x);  //ensure won't draw at frame    //! Mat.at中x和y的位置非主流
       
        //if (temp == Scalar(255, 255, 255))
        if (temp.val[0] > 250 && temp.val[1] > 250 && temp.val[2] > 250)    //如果不巧碰上非255,255,255的白色
        {
            scalar1 = Scalar(rand() % 250, rand() % 250, rand() % 250);     //颜色别太淡了
            floodFill(image4, Point(x, y), scalar1, &ccomp, Scalar(0, 0, 0), Scalar(0, 0, 0));  
        }

        x += 3;    //步进

        //换行
        if (x >= image4.cols) 
        {
            y += 3;
            x = 0;
        }

        //遍历满后退出填充循环
        if (y >= image4.rows)   
        {
            break;
        }

    }

    //在窗口中显示图像
    imshow("AutoColored", image4);

    //输出
    imwrite(InputPictureName + "_output.jpeg", image4);

    waitKey();

    return 0;
}