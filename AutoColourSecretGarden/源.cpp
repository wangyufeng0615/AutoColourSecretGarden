#include <opencv2/opencv.hpp>
#include <cmath>
#include <ctime>
#include <string>
using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    //���룬OPENCV2.0д��
    if (argc < 2)
    {
        return 0;
    }
    string InputPictureName = argv[1];
    Mat image1 = imread(InputPictureName);
    Mat image2;             //�ҶȻ�
    Mat image3;             //��ֵ��
    Mat image4;             //��ɫͼ

    //��������
    namedWindow("AutoColored",0);
    resizeWindow("AutoColored", 600, 600);  //������������ʲ����ʾ��
    
    //�ҶȻ�
    cvtColor(image1, image2, CV_BGR2GRAY);

    //��ֵ��
    threshold(image2, image3, 127, 255, THRESH_BINARY);

    //�ָ���ɫͼ
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
        temp = image4.at<Vec3b>(y, x);  //ensure won't draw at frame    //! Mat.at��x��y��λ�÷�����
       
        //if (temp == Scalar(255, 255, 255))
        if (temp.val[0] > 250 && temp.val[1] > 250 && temp.val[2] > 250)    //����������Ϸ�255,255,255�İ�ɫ
        {
            scalar1 = Scalar(rand() % 250, rand() % 250, rand() % 250);     //��ɫ��̫����
            floodFill(image4, Point(x, y), scalar1, &ccomp, Scalar(0, 0, 0), Scalar(0, 0, 0));  
        }

        x += 3;    //����

        //����
        if (x >= image4.cols) 
        {
            y += 3;
            x = 0;
        }

        //���������˳����ѭ��
        if (y >= image4.rows)   
        {
            break;
        }

    }

    //�ڴ�������ʾͼ��
    imshow("AutoColored", image4);

    //���
    imwrite(InputPictureName + "_output.jpeg", image4);

    waitKey();

    return 0;
}