// svaing trajcetory as tum format
// ? x y z seems not consisident with the  ground truth
#include "utility_legoLoam.h"

// #include "/home/jason/LidarSLAM/legoloam/src/LeGO-LOAM/LeGO-LOAM/include/utility_legoLoam.h"
/* 
              << -odomAftMapped.pose.pose.position.y << " "
              << odomAftMapped.pose.pose.position.z << " "
              << odomAftMapped.pose.pose.position.x << " "
 */

bool initialpose_; 
geometry_msgs::Pose init_pose_;
std::ofstream pose1(trajPath);
// std::ofstream pose2(trajPointCloudPath);
std::ofstream gt(groundTruthPath);

void path_save(const nav_msgs::Odometry::ConstPtr &odomAftMapped_ )
{
 
    pose1.setf(std::ios::scientific, std::ios::floatfield);
    pose1.precision(9);

    // static double timeStart = odomAftMapped_->header.stamp.toSec();
    // auto T1 =ros::Time().fromSec(timeStart) ;
    // pose1<< (odomAftMapped_->header.stamp -T1).toSec()<< " "
        pose1 << odomAftMapped_->header.stamp << " "
        << odomAftMapped_->pose.pose.position.z << " "
        << odomAftMapped_->pose.pose.position.x << " "
        << odomAftMapped_->pose.pose.position.y << " "
        << odomAftMapped_->pose.pose.orientation.x << " "
        << odomAftMapped_->pose.pose.orientation.y << " "
        << odomAftMapped_->pose.pose.orientation.z << " "
        << odomAftMapped_->pose.pose.orientation.w << std::endl;
    // pose1.close();
            
}


void gt_odom_save(const nav_msgs::Odometry::ConstPtr& utm_odom)
{
    if(!initialpose_) {
    init_pose_ = utm_odom->pose.pose;
    initialpose_ = true;
  }

    gt.setf(std::ios::scientific, std::ios::floatfield);
    gt.precision(9);    
    
    // static double timeStart = utm_odom->header.stamp.toSec();
    // auto T1 =ros::Time().fromSec(timeStart) ;
    // gt<< (utm_odom->header.stamp -T1).toSec()<< " "
    gt << utm_odom->header.stamp << " "
        << utm_odom->pose.pose.position.z << " "
        << utm_odom->pose.pose.position.x << " "
        << utm_odom->pose.pose.position.y << " "
        << utm_odom->pose.pose.orientation.x << " "
        << utm_odom->pose.pose.orientation.y << " "
        << utm_odom->pose.pose.orientation.z << " "
        << utm_odom->pose.pose.orientation.w << std::endl;
        // << 0 << " "
        // << 0 << " "
        // << 0 << " "
        // << 1 << std::endl;
        

    // gt.close();
}




int main(int argc, char **argv){
    ros::init(argc, argv, "path_save");
    ros::NodeHandle nh;

    ros::Subscriber save_path_aft_mapped = nh.subscribe<nav_msgs::Odometry>("/aft_mapped_to_init", 100, path_save, ros::TransportHints().tcpNoDelay());	    //保存轨迹，a_loam直接订阅话题/aft_mapped_to_init。
    // ros::Subscriber save_path_gt = nh.subscribe<nav_msgs::Odometry>("odom", 100, gt_odom_save, ros::TransportHints().tcpNoDelay());	
    ros::Subscriber save_path_gt = nh.subscribe<nav_msgs::Odometry>("/gps_odom", 100, gt_odom_save, ros::TransportHints().tcpNoDelay());	

        
    // ros::Subscriber save_path_pointCloud = nh.subscribe<sensor_msgs::PointCloud2>("/key_pose_origin", 100, pointCloudCallback);
    // ros::Subscriber save_path_key_pose = nh.subscribe<
    ros::spin();
     }