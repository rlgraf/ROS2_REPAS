from setuptools import find_packages, setup
import os
from glob import glob

package_name = 'camera_sensor'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'camera_z_data'), glob('camera_z_data/*')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='russell',
    maintainer_email='rlgraf@ucdavis.edu',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'camera_return_z_publisher = camera_sensor.camera_return_z:main',
        ],
    },
)
