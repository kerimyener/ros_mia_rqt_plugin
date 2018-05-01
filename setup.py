# # ! DO NOT MANUALLY INVOKE THIS setup.py, USE CATKIN INSTEAD

from distutils.core import setup
from catkin_pkg.python_setup import generate_distutils_setup

# fetch values from package.xml
setup_args = generate_distutils_setup(
    packages=['ros_mia_rqt_plugin'],
    package_dir={'': 'src'},
    requires=['std_msgs', 'roscpp', 'ros_mia_driver']
)

setup(**setup_args)
