#ifndef ros_mia_rqt_plugin_plugin_H
#define ros_mia_rqt_plugin_plugin_H

#include <rqt_gui_cpp/plugin.h>
#include <ros_mia_rqt_plugin/ui_mia_plugin.h>
#include <QWidget>

#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <QString>

#include "ros_mia_driver_msgs/DriveState.h"
//#include "ros_mia_driver/MiaCommand.h"
//#include "ros_mia_driver/MiaControlCommand.h"

namespace ros_mia_rqt_plugin {

class MiaPlugin
    : public rqt_gui_cpp::Plugin
{
  Q_OBJECT
public:
  MiaPlugin();
  virtual void initPlugin(qt_gui_cpp::PluginContext& context);

private:
  Ui::MiaPluginWidget ui_;
  QWidget* widget_;

  ros::NodeHandle nh;
  ros::Subscriber my_subscriber;
  QPushButton *m_button;
  //void ros_data_callback(ros_mia_driver::MiaCommand::ConstPtr const& msg);
  void ros_data_callback1(ros_mia_driver_msgs::DriveState::ConstPtr const& msg);
  //void ros_data_callback2(ros_mia_driver::MiaControlCommand::ConstPtr const& msg);


Q_SIGNALS:
  void setText(const QString );
  void dis_setText(const QString);
  void textChanged(const QString );
  void emerg_textChanged(const QString );
  void mode_textChanged(const QString );
  void setStyleSheet(const QString);
  void throttleBar_valueChanged (int);
  void slid_valueChanged (int);
  void setValue (int);
  void overflow (double);
  void display(double);
  void clicked();
  void released();


private slots:
  void on_pushButton_clicked();
};

}  // namespace
#endif
