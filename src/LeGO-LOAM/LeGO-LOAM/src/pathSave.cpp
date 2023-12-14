// svaing trajcetory as tum format
// ? x y z seems not consisident with the  ground truth
#include "utility_legoLoam.h"

// #include "/home/jason/LidarSLAM/legoloam/src/LeGO-LOAM/LeGO-LOAM/include/utility_legoLoam.h"
/* 
              << -odomAftMapped.pose.pose.position.y << " "
              << odomAftMapped.pose.pose.position.z << " "
              << odomAftMapped.pose.pose.position.x << " "

              x
              -z
              -y
 */

bool initialpose_; 
geometry_msgs::Pose init_pose_;

void path_save(const nav_msgs::Odometry::ConstPtr &odomAftMapped_ )
{
 
    std::ofstream pose1(trajPath, std::ios::app);
    pose1.setf(std::ios::scientific, std::ios::floatfield);
    pose1.precision(9);

    static double timeStart = odomAftMapped_->header.stamp.toSec();
    auto T1 =ros::Time().fromSec(timeStart) ;
    pose1<< odomAftMapped_->header.stamp -T1<< " "
        << -odomAftMapped_->pose.pose.position.y << " "
        << odomAftMapped_->pose.pose.position.z << " "
        << odomAftMapped_->pose.pose.position.x << " "
        << odomAftMapped_->pose.pose.orientation.x << " "
        << odomAftMapped_->pose.pose.orientation.y << " "
        << odomAftMapped_->pose.pose.orientation.z << " "
        << odomAftMapped_->pose.pose.orientation.w << std::endl;
    pose1.close();
            
}

/* void gt_odom_save(const nav_msgs::Odometry::ConstPtr& utm_odom)
{
    if(!initialpose_) {
    init_pose_ = utm_odom->pose.pose;
    initialpose_ = true;
  }

    std::ofstream gt(groundTruthPath_odom, std::ios::app);
    gt.setf(std::ios::scientific, std::ios::floatfield);
    gt.precision(9);    
    
    static double timeStart = utm_odom->header.stamp.toSec();
    auto T1 =ros::Time().fromSec(timeStart) ;
    gt<< utm_odom->header.stamp -T1<< " "
        << utm_odom->pose.pose.position.x - init_pose_.position.x<< " "
        << utm_odom->pose.pose.position.y - init_pose_.position.y<< " "
        << utm_odom->pose.pose.position.z - init_pose_.position.z<< " "
        << utm_odom->pose.pose.orientation.x << " "
        << utm_odom->pose.pose.orientation.y << " "
        << utm_odom->pose.pose.orientation.z << " "
        << utm_odom->pose.pose.orientation.w << std::endl;

    gt.close();
} */

void gt_save(const visualization_msgs::MarkerArray::ConstPtr& utm_odom)
{
    std::ofstream gt(groundTruthPath);
    gt.setf(std::ios::scientific, std::ios::floatfield);
    gt.precision(9);    
    
    static double timeStart = utm_odom->markers.back().header.stamp.toSec();
    auto T1 =ros::Time().fromSec(timeStart) ;
    gt<< utm_odom->markers.back().header.stamp -T1<< " "
        << utm_odom->markers.back().points.back().x<< " "
        << utm_odom->markers.back().points.back().y << " "
        << utm_odom->markers.back().points.back().z << " "
        << 0 << " "
        << 0 << " "
        << 0 << " "
        << 1 << std::endl;

    gt.close();
}




int main(int argc, char **argv){
    ros::init(argc, argv, "path_save");
    ros::NodeHandle nh;

    

    ros::Subscriber save_path_aft_mapped = nh.subscribe<nav_msgs::Odometry>("/aft_mapped_to_init",     100, path_save, ros::TransportHints().tcpNoDelay());	    //保存轨迹，a_loam直接订阅话题/aft_mapped_to_init。
    // ros::Subscriber save_path_gt_odom = nh.subscribe<nav_msgs::Odometry>("odom",     100, gt_odom_save);	    
    ros::Subscriber save_path_gt = nh.subscribe<visualization_msgs::MarkerArray>("magellan_proflex500_driver/marker_array",     100, gt_save, ros::TransportHints().tcpNoDelay());	    

    // ros::Subscriber save_path_key_pose
    ros::spin();
     }