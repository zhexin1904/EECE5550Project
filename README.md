# Dependency

LeGO-LOAM:

- ROS Noetic
- [GTSAM](https://gtsam.org/) 4.00-alpha2 
- PCL
- OpenCV

GNSS process:

- [Geographiclib](https://github.com/geographiclib/geographiclib ) (used for LLA to local Cartesian frame conversion)

Visualization on Google Map:

- [rviz_satellite](https://github.com/nobleo/rviz_satellite) 

Some packages are required for [utbm](https://github.com/epan-utbm/utbm_robocar_dataset) dataset will be listed on Dataset section

# Build

```
cd ~/catkin_ws/src
git clone https:
cd ..
catkin_make -j
```

# Dataset

## [utbm](https://github.com/epan-utbm/utbm_robocar_dataset)


![image](https://github.com/zhexin1904/EECE5550Project/blob/main/pic/utbm/global_map.png)

Dependency:

- (used to process the GNSS data of utbm dataset)

[magellan_proflex500_driver](https://github.com/epan-utbm/utbm_robocar_dataset/tree/baselines/drivers/magellan_proflex500/magellan_proflex500_driver)

[utbm_nmea_msgs](https://github.com/epan-utbm/utbm_robocar_dataset/tree/baselines/drivers/magellan_proflex500/utbm_nmea_msgs)

- You may need Velodyne(Used to convert raw Velodyne data [packets](http://docs.ros.org/en/api/velodyne_msgs/html/msg/VelodyneScan.html) to [sensor_msgs/PointCloud2](http://docs.ros.org/en/api/sensor_msgs/html/msg/PointCloud2.html))
- [velodyne_pointcloud](http://wiki.ros.org/velodyne_pointcloud)(If you are also using Noetic, there might be errors due to missing functions. Please consider using a lower version of the library.)

## [Mulran](https://sites.google.com/view/mulran-pr/dataset)

![image](https://github.com/zhexin1904/EECE5550Project/blob/main/pic/mulran/mulran_gps.png)

Dependency:

- [file_player_mulran](https://github.com/RPM-Robotics-Lab/file_player_mulran)(Used to play the data of Mulran, raw data is not provided in rosbag)

# Usage

## run in utbm

```
# cd your workspace
source devel/setup.bash
roslaunch lego_loam lego_loam_utbm.launch
```

## run in Mulran

```
# cd your workspace
source devel/setup.bash
roslaunch lego_loam lego_loam_mulran.launch 
```

# Evaluation

## trajectory

Using [evo](https://github.com/MichaelGrupp/evo) to evaluate the trajectory (ATE, RTE...)

For utmb, groundtruth need to subscribe GNSS message, and convert to TUM fomart(our code provided)

For Mulran, please access the groundtruth in their webpage 

## pcd map

Here, we use a simple way to save the pcd map:

- record the global map message in a ros bag, when the dataset is almost over
- using [pcl_ros](http://wiki.ros.org/pcl_ros) to convert rosbag to pcd 

# Configure your dataset!

Besides the basic config of Lidar SLAM(point cloud topic, Lidar type, imu topic......) in `utility_legoLoam.h`, (may be will convert a better config format :) , like `yaml`) for our GPS-module , several configuration need to do in:

`gpsTopic`(your gps topic)

`gpsCovThreshold`(a manually set threshold to reject bad gps measurement)

`gpsFrequence`(used in synchronization, but not need to set really strictly)

......

# Acknowledgement

This work is built based on [LeGO-LOAM](https://github.com/RobustFieldAutonomyLab/LeGO-LOAM)

Thanks for these great works from which we learned to 

[LIO-SAM](https://github.com/TixiaoShan/LIO-SAM)

[hdl_graph_slam](https://github.com/koide3/hdl_graph_slam)

[LIO_SAM_6AXIS](https://github.com/JokerJohn/LIO_SAM_6AXIS)

