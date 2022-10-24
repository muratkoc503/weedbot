# weedbot
Otonom Yabancı Ot Ayıklama Robotu ROS2 workspace'idir.
![Screenshot from 2022-10-24 16-59-02](https://user-images.githubusercontent.com/75611653/197543959-4bbef737-e40c-40c4-b89f-c403b651c3b7.png)

## Install 
**1)** ROS-Galactic <br/>
**2)** Gazebo (verion 11) <br/>
**3)** Another dependet packages (sonra açıklanabilir.) <br/>


```
sudo apt update && sudo apt upgrade
```
```
git clone https://github.com/muratkoc503/weedbot.git
```

## Build & Run
Build:
```
cd ~weedbot && colcon build
```
Run:
```
cd ~weedbot && source install/local_setup.bash
ros2 launch weed_simulation weedbot_world.py
```
