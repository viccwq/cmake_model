//http://dlib.net/image_ex.cpp.html
#include <iostream>
#include <mutex>
#include <thread>
#include <fstream>

#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/image_transforms.h>

#include "vxlCmakeCfg.h"

#define MULTI_THREAD  0
#define LOOP          1
#define MULTI_DLL     (0 & !MULTI_THREAD)

using namespace dlib;
using namespace std;

#if MULTI_DLL

#else
int FunTest(int threadIdx)
{
    try
    {
        // make sure the user entered an argument to this program
        //if (argc != 2)
        //{
        //    cout << "error, you have to enter a BMP file as an argument to this program" << endl;
        //    return 1;
        //}

        // Here we declare an image object that can store rgb_pixels.  Note that in 
        // dlib there is no explicit image object, just a 2D array and
        // various pixel types.  
        array2d<rgb_pixel> img;

        // Now load the image file into our image.  If something is wrong then
        // load_image() will throw an exception.  Also, if you linked with libpng
        // and libjpeg then load_image() can load PNG and JPEG files in addition
        // to BMP files.
        char filePath[256];
        sprintf(filePath, "%s%s", VXL_TRUNK_DIR, "/data/Lighthouse.jpg");
        load_image(img, string(filePath));


        // Now let's use some image functions.  First let's blur the image a little.
        array2d<unsigned char> blurred_img;
        gaussian_blur(img, blurred_img);

        // Now find the horizontal and vertical gradient images.
        array2d<short> horz_gradient, vert_gradient;
        array2d<unsigned char> edge_image;
        sobel_edge_detector(blurred_img, horz_gradient, vert_gradient);

        // now we do the non-maximum edge suppression step so that our edges are nice and thin
        suppress_non_maximum_edges(horz_gradient, vert_gradient, edge_image);

        // Now we would like to see what our images look like.  So let's use a 
        // window to display them on the screen.  (Note that you can zoom into 
        // the window by holding CTRL and scrolling the mouse wheel)
        image_window my_window(edge_image, "Normal Edge Image");

        // We can also easily display the edge_image as a heatmap or using the jet color
        // scheme like so.
        image_window win_hot(heatmap(edge_image));
        image_window win_jet(jet(edge_image));

        // also make a window to display the original image
        image_window my_window2(img, "Original Image");

        // Sometimes you want to get input from the user about which pixels are important
        // for some task.  You can do this easily by trapping user clicks as shown below.
        // This loop executes every time the user double clicks on some image pixel and it
        // will terminate once the user closes the window.
        point p;
        while (my_window.get_next_double_click(p))
        {
            cout << "User double clicked on pixel:         " << p << endl;
            cout << "edge pixel value at this location is: " << (int)edge_image[p.y()][p.x()] << endl;
        }

        // wait until the user closes the windows before we let the program 
        // terminate.
        win_hot.wait_until_closed();
        my_window2.wait_until_closed();


        // Finally, note that you can access the elements of an image using the normal [row][column]
        // operator like so:
        cout << horz_gradient[0][3] << endl;
        cout << "number of rows in image:    " << horz_gradient.nr() << endl;
        cout << "number of columns in image: " << horz_gradient.nc() << endl;
    }
    catch (exception& e)
    {
        cout << "exception thrown: " << e.what() << endl;
    }
    return 0;
}
#endif

void ThreadFunc0()
{
    unsigned int status = 1;
    status = FunTest(0);
}

void ThreadFunc1()
{
    unsigned int status = 1;
    status = FunTest(1);
}

int main()
{
    int status = 0;

#if !MULTI_THREAD
    const int THREAD_NUM = 1;
    thread threads[THREAD_NUM];

    threads[0] = thread(ThreadFunc0);
#else
    const int THREAD_NUM = 2;
    thread threads[THREAD_NUM];

    threads[0] = thread(ThreadFunc0);
    threads[1] = thread(ThreadFunc1);
#endif

    for (auto & th : threads)
    {
        th.join();
    }

    return status;
}