// main thread: through the camera to detect aruco in the environment, mark any aruco marker
// draw the coordinate on the marker, and accuqire the relative coordinate from the camera frame 
// sub thread: send the marker to the robot 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <ros/ros.h>
#include <string.h> 
#include <stdio.h>
#include <pthread.h>

#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/opencv.hpp>  
#include <opencv2/highgui/highgui.hpp>  

#include <sensor_msgs/image_encodings.h>

#include<aruco/aruco.h>
#include <aruco/cvdrawingutils.h>
#include <aruco/posetracker.h>

#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#include <math.h>  
#include <vector>
#include <Eigen/Eigen>
#include <Eigen/StdVector>
#include <Eigen/Geometry>
#include <Eigen/Core>
#include <unistd.h>
//#include "highgui.h"  
//#include <cv.h>  

using namespace std;
using namespace cv;
using namespace aruco;
using namespace Eigen;

//global variables
float Rotat_Vec_Arr[3];//rotational vector array
float Rotat_M[9];//rotational matrix array
float Trans_M[3];//translation vector array

pthread_mutex_t IK_Solver_Lock;

class arucoFinder
{
    ros::NodeHandle nh_; 
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;

    tf::TransformBroadcaster broadcaster;
	tf::TransformListener listener(ros::Duration(10));

    Mat image; 

    public:

    arucoFinder() : it_(nh_)
    {
        image_sub_ = it_.subscribe("/nao_robot/camera/top/camera/image_raw", 1, &arucoFinder::imageCb, this);
        image_pub_ = it_.advertise("/aruco:coordinate", 1);
        cv::namedWindow("/arucoOutput");
    }

     ~arucoFinder()
    {
        cv::destroyAllWindows();
    }

    void imageCb(const sensor_msgs::ImageConstPtr& top_camera_message )
    {
        cv_bridge::CvImagePtr cv_ptr; 
		Mat gray_image;
        Mat croped_image; 
        try
		{
			cv_ptr= cv_bridge::toCvCopy(top_camera_message,sensor_msgs::image_encodings::BGR8); // copy the captured picture to a new pointer
			image = cv_ptr-> image.clone();
		}
		catch (cv_bridge::Exception& e )
		{
			ROS_ERROR("cv_bridge exception &s",e.what());
			return;
		}

        image=cv_ptr-> image; 
		cv::cvtColor(image, gray_image, COLOR_BGR2GRAY); 
        int thread_return; 
        pthread_t Message_Send_Thread_ID;
        //init thread lock
        pthread_mutex_init(&IK_Solver_Lock, NULL);
        //creat new thread 
        thread_return = pthread_create(&Message_Send_Thread_ID,NULL,Thread_Func_Message_Send,NULL);

        //import the camera param (CameraMatrix)
        float camera_matrix_array[9] = { 551.543059, 0., 327.382898, 
                                    0.0, 553.736023, 225.026380, 
                                    0.0, 0.0, 1.0 };

        cv::Mat Camera_Matrix(3,3,CV_32FC1);
        arucoFinder.InitMat(Camera_Matrix,camera_matrix_array);
        cout << "Camera_Matrix = " << endl << "" << Camera_Matrix << endl ;

        //import the camera param (Distorsion)
        float Distorsion_array[5] = {-0.066494,0.095481,-0.000279, 0.002292,0.000000};
        cv::Mat Distorsion_M(1,5,CV_32FC1);
        InitMat(Distorsion_M,Distorsion_array);
        cout << "Distorsion_M = " << endl << "" << Distorsion_M << endl ;
        CameraParameters NaoCameraParameter;

        //Camera read from documentation;
        NaoCameraParameter.CameraMatrix = Camera_Matrix.clone();
        NaoCameraParameter.Distorsion = Distorsion_M.clone();
        NaoCameraParameter.CamSize.width = 640;
        NaoCameraParameter.CamSize.height = 480;

        float MarkerSize = 0.04; 
        int Marker_ID;
        aruco::MarkerDetector MDetector;
        // param1: blockSize of the pixel neighborhood that is used to calculate a threshold value for the pixel param
        // 2: The constant subtracted from the mean or weighted mean
        MDetector.setThresholdParams(7, 7);
        // MDetector.setThresholdParamRange(2, 0);

        CvDrawingUtils MDraw;

        //read the input image
        VideoCapture cap(0); // open the default camera 
            if(!cap.isOpened())  // check if we succeeded  
                return -1; 

        cv::Mat frame;
        cv::Mat Rvec;//rotational vector
        CvMat Rvec_Matrix;//temp matrix
        CvMat R_Matrix;//rotational matrixs
        cv::Mat Tvec;//translation vector

        cap>>frame;//get first frame
        //NaoCameraParameter.resize(frame.size());

        printf("%f, %f\n",cap.get(CV_CAP_PROP_FRAME_WIDTH),cap.get(CV_CAP_PROP_FRAME_HEIGHT));  
        cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);  
        cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);  
        //cap.set(CV_CAP_PROP_FPS, 10);  
        printf("%f, %f\n",cap.get(CV_CAP_PROP_FRAME_WIDTH),cap.get(CV_CAP_PROP_FRAME_HEIGHT)); 

        while(1)
        {
            //get current frame
            cap>>frame;
            //Ok, let's detect
            vector< Marker > Markers= MDetector.detect(frame, NaoCameraParameter, MarkerSize);
            //printf("marker count:%d \n",(int)(Markers.size()));

            //for each marker, estimate its ID and if it is  100 draw info and its boundaries in the image
            for (unsigned int j=0;j<Markers.size();j++)
            {
                
                //marker ID test
                Marker_ID = Markers[j].id;
                printf("Marker ID = %d \n",Marker_ID);

                //cout<<Markers[j]<<endl;
                Markers[j].draw(frame,Scalar(0,0,255),2);

                Markers[j].calculateExtrinsics(MarkerSize, NaoCameraParameter, false);
                //calculate rotational vector
                Rvec = Markers[j].Rvec;
                cout << "Rvec = " << endl << "" << Rvec << endl ;
                //calculate transformation vector
                Tvec = Markers[j].Tvec;
                cout << "Tvec = " << endl << "" << Tvec << endl ;

                //lock to update global variables: Rotat_Vec_Arr[3]  Rotat_M[9]  Trans_M[3]
                pthread_mutex_lock(&IK_Solver_Lock);

                //save rotational vector to float array
                for (int r = 0; r < Rvec.rows; r++)  
                {  
                    for (int c = 0; c < Rvec.cols; c++)  
                    {     
                        //cout<< Rvec.at<float>(r,c)<<endl;  
                        Rotat_Vec_Arr[r] = Rvec.at<float>(r,c);
                    }     
                }
                printf("Rotat_Vec_Arr[3] = [%f, %f, %f] \n",Rotat_Vec_Arr[0],Rotat_Vec_Arr[1],Rotat_Vec_Arr[2]);

                //save array data to CvMat and convert rotational vector to rotational matrix
                cvInitMatHeader(&Rvec_Matrix,1,3,CV_32FC1,Rotat_Vec_Arr,CV_AUTOSTEP);//init Rvec_Matrix
                cvInitMatHeader(&R_Matrix,3,3,CV_32FC1,Rotat_M,CV_AUTOSTEP);//init R_Matrix and Rotat_M
                cvRodrigues2(&Rvec_Matrix, &R_Matrix,0);
                printf("Rotat_M = \n[%f, %f, %f, \n  %f, %f, %f, \n  %f, %f, %f] \n",Rotat_M[0],Rotat_M[1],Rotat_M[2],Rotat_M[3],Rotat_M[4],Rotat_M[5],Rotat_M[6],Rotat_M[7],Rotat_M[8]);
                
                //save transformation vector to float array
                for (int r = 0; r < Tvec.rows; r++)
                {  
                    for (int c = 0; c < Tvec.cols; c++)  
                    {
                        Trans_M[r] = Tvec.at<float>(r,c);
                    }
                }
                printf("Trans_M[3] = [%f, %f, %f] \n",Trans_M[0],Trans_M[1],Trans_M[2]);

                //unlock 
                pthread_mutex_unlock(&IK_Solver_Lock);

                // draw a 3d cube in each marker if there is 3d info
                if (NaoCameraParameter.isValid() && MarkerSize != -1)
                {
                    MDraw.draw3dAxis(frame,NaoCameraParameter,Rvec,Tvec,0.04);
                }

                

            }

            //*/
            cv::waitKey(150);//wait for key to be pressed
            cv::imshow("Frame",frame);

        }


        //wait for the IK solver thread close and recover resources
        pthread_join(Message_Send_Thread_ID,NULL);

        pthread_mutex_destroy(&IK_Solver_Lock); //destroy the thread lock

    }
    /**********************************************************
    function: new thread to send messages 
    input: void
    return :null
    ***********************************************************/
    void *Thread_Func_Message_Send(void *arg)//thread_function
    {
        printf("IK solver thread is running!\n");
        //original pose and position
        float P_original[4];
        float N_original[4];
        float O_original[4];
        float A_original[4];
        //final pose and position 
        float P[3];
        float N[3];
        float O[3];
        float A[3];

        P_original[3] = 1;
        N_original[3] = 0;
        O_original[3] = 0;
        A_original[3] = 0;

        while (1)
        {
            //get the spacial pose
            pthread_mutex_lock(&IK_Solver_Lock);
            //memcpy(P_original, Trans_M, sizeof(Trans_M));
            for(int i=0;i<3;i++)
            {
                P_original[i] = Trans_M[i];
                N_original[i] = Rotat_M[3*i];
                O_original[i] = Rotat_M[3*i+1];
                A_original[i] = Rotat_M[3*i+2];
            }
            pthread_mutex_unlock(&IK_Solver_Lock);
            //debug printf
            ///*
            printf("N_original[4] = [%f, %f, %f, %f]  \n",N_original[0],N_original[1],N_original[2],N_original[3]);
            printf("O_original[4] = [%f, %f, %f, %f]  \n",O_original[0],O_original[1],O_original[2],O_original[3]);
            printf("A_original[4] = [%f, %f, %f, %f]  \n",A_original[0],A_original[1],A_original[2],A_original[3]);
            printf("P_original[4] = [%f, %f, %f, %f]  \n",P_original[0],P_original[1],P_original[2],P_original[3]);
            //*/

            printf("I send the message to robot here! \n");
            /*
            add message send function here!
            */
            //uodate every 5 s
            sleep(5);
        }

        //kill the message send thread
        pthread_exit(0);
        
    }

    void InitMat(Mat& m,float* num)
    {
        for(int i=0;i<m.rows;i++)
        for(int j=0;j<m.cols;j++)
        m.at<float>(i,j)=*(num+i*m.rows+j);
    }
    /********************************* 
    function  PrintMat(CvMat *matrix) (print the cvMat on screen) 
    input：matrix point
    return：null
    **********************************/  
    void PrintMat(CvMat *matrix, bool save_or_show =false,FILE *fp=NULL)  
    {  
        int i=0;  
        int j=0;  
        for(i=0;i < matrix->rows;i++)//行  
        {  
            if (save_or_show)  
            {  
                fprintf(fp,"\n");  
            }   
            else  
            {  
                printf("\n");  
            }  
            switch(matrix->type&0X07)  
            {  
                case CV_32F:   
                case CV_64F:  
                    {  
                        for(j=0;j<matrix->cols;j++)//列  
                        {  
                            if (save_or_show)  
                            {  
                                fprintf(fp,"%9.3f ",(float)cvGetReal2D(matrix,i,j));  
                            }   
                            else  
                            {  
                                printf("%9.3f ",(float)cvGetReal2D(matrix,i,j));  
                            }  
                        }  
                        break;  
                    }  
                case CV_8U:  
                case CV_16U:  
                    {  
                        for(j=0;j<matrix->cols;j++)  
                        {  
                            printf("%6d  ",(int)cvGetReal2D(matrix,i,j));  
                            if (save_or_show)  
                            {  
                                fprintf(fp,"%6d  ",(int)cvGetReal2D(matrix,i,j));  
                            }   
                            else  
                            {  
                                printf("%6d  ",(int)cvGetReal2D(matrix,i,j));  
                            }  
                        }  
                    break;  
                    }  
                default:  
                break;  
            }
        } 
    }  

    void InitMat(Mat& m,float* num)
    {
        for(int i=0;i<m.rows;i++)
        for(int j=0;j<m.cols;j++)
        m.at<float>(i,j)=*(num+i*m.rows+j);
    }

    void transformPoint(const tf::TransformListener& listener)
	{
		//we'll create a point in the base_laser frame that we'd like to transform to the base_link frame
		geometry_msgs::PointStamped laser_point;
		laser_point.header.frame_id = "base_laser";

		//we'll just use the most recent transform available for our simple example
		laser_point.header.stamp = ros::Time();

		//just an arbitrary point in space
		laser_point.point.x = 1.0;
		laser_point.point.y = 0.2;
		laser_point.point.z = 0.0;

		try
		{
			geometry_msgs::PointStamped base_point;
			// three arguments. 1. to the frame we want to transform 2. the point we are transforming 3. the storage of the transformed point
			listener.transformPoint("base_link", laser_point, base_point);

			ROS_INFO("base_laser: (%.2f, %.2f. %.2f) -----> base_link: (%.2f, %.2f, %.2f) at time %.2f",
				laser_point.point.x, laser_point.point.y, laser_point.point.z,
				base_point.point.x, base_point.point.y, base_point.point.z, base_point.header.stamp.toSec());
		}
		catch(tf::TransformException& ex)
		{
			ROS_ERROR("Received an exception trying to transform a point from \"base_laser\" to \"base_link\": %s", ex.what());
		}
	}

    void main_loop(ros::Rate rate_sleep)
    {
        while(nh_.ok())
		{
			ROS_INFO("Stop and detect the new dark spot");
			
			// Sending a transform with a TransformBroadcaster requires five arguments
			// 1. rotation transform Quaternion for any rotation between two frames
			// 2. Vector3 for any translation
			// 3. give the transform being published a timestamp
			// 4. parent node
			// 5. child node 
			broadcaster.sendTransform(
         		tf::StampedTransform( 
					tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.1, 0.0, 0.2)), ros::Time::now(),"base_link", "base_laser"));

			ros::Timer timer = nh_.createTimer(ros::Duration(1.0), boost::bind(&transformPoint, boost::ref(listener)));

			rate_sleep.sleep();
		}
    }

};