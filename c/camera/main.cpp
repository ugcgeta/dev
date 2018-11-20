//テストプログラム
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main(int argc, char* argv[])
{
    Mat mat;
    VideoCapture vcap(0);

    if (!vcap.isOpened()){
		puts("ERR");
        return -1;
	}

    while (1) {
        vcap >> mat;
        imshow("aaa", mat);
        if (waitKey(10) >= 0) break;
    }
    return 0;
}
