#include "ros_mia_rqt_plugin/mia_plugin.h"
#include <pluginlib/class_list_macros.h>
#include <QStringList>
#include <QProcess>
//#include <QApplication>

namespace ros_mia_rqt_plugin {

MiaPlugin::MiaPlugin()
  : rqt_gui_cpp::Plugin()
  , widget_(0)
{
  setObjectName("MiaDashBoard");
}

void MiaPlugin::initPlugin(qt_gui_cpp::PluginContext& context)
{
  QStringList argv = context.argv();
  widget_ = new QWidget();
  ui_.setupUi(widget_);
  context.addWidget(widget_);

  ui_.throttleBar->setValue(0);
  ui_.breakBar->setValue(0);
  ui_.throttleBar->setRange(0,50);


  my_subscriber = nh.subscribe("/mia/mia_state", 1, &MiaPlugin::ros_data_callback1, this);


  QObject::connect( this, SIGNAL(setText(const QString)),
                    ui_.drive_display, SLOT(setText(const QString)));
  QObject::connect( this, SIGNAL(setStyleSheet(const QString)),
                    ui_.drive_display, SLOT(setStyleSheet(const QString)));
  QObject::connect( this, SIGNAL(throttleBar_valueChanged(int )),
                    ui_.throttleBar, SLOT(setValue(int )));
  QObject::connect( this, SIGNAL(slid_valueChanged(int )),
                    ui_.horizontalSlider, SLOT(setValue(int )));
  QObject::connect( this, SIGNAL(overflow(double)),
                    ui_.lcdNumber, SLOT(display(double)));
  QObject::connect( this, SIGNAL(textChanged(const QString)),
                    ui_.angle_display, SLOT(setText(const QString)));
  QObject::connect( this, SIGNAL(mode_textChanged(const QString)),
                    ui_.mode_display, SLOT(setText(const QString)));
  QObject::connect( this, SIGNAL(emerg_textChanged(const QString)),
                    ui_.emerg_display, SLOT(setText(const QString)));

  connect(ui_.pushButton, SIGNAL (released()), this, SLOT (on_pushButton_clicked()));
  //ros::spin();
}


void MiaPlugin::ros_data_callback1(ros_mia_driver_msgs::DriveState::ConstPtr const& msg) {
  QString str (QString::number(msg->drive_direction));
  QString str1(QString::number(msg->autonomy_mode));
  QString str2(QString::number(msg->emergency_button));
  QString str3(QString::number(msg->steering_angle*180/3.14));

  emit setText(str);
  emit mode_textChanged(str1);
  emit emerg_textChanged(str2);
  emit textChanged(str3);
  emit throttleBar_valueChanged (10*msg->throttle_actual);
  emit slid_valueChanged (msg->steering_angle*180/3.14);
  emit overflow (msg->speed);


  // another signal is used to set the color of the widget
  if (msg->drive_direction > 0) {
    emit setStyleSheet("color: black; background-color: green;");
  }
  else if (msg->drive_direction == 0) {
    emit setStyleSheet("color: black; background-color: blue;");
  }
  else {
    emit setStyleSheet("color: black; background-color: red;");
  }
}

void MiaPlugin::on_pushButton_clicked(){
  QProcess proc;
  proc.startDetached("roslaunch nodes ndt_matching.launch");
  //system("gnome-terminal -x \"source ~/master_ws/devel/setup.bash;roslaunch nodes tf_localizer.launch\"");


}

} // namespace
PLUGINLIB_DECLARE_CLASS(ros_mia_rqt_plugin, MiaPlugin, ros_mia_rqt_plugin::MiaPlugin, rqt_gui_cpp::Plugin)

