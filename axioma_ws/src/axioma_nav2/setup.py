from setuptools import setup
from glob import glob

package_name = 'axioma_nav2'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name, glob('launch/*.py')),
  	    ('share/' + package_name+'/param/', glob('param/*')),
  	    ('share/' + package_name+'/rviz/', glob('rviz/*')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='robot',
    maintainer_email='olmerg@gmail.com',
    description='Paquete que sirve de brigde de nav2',
    license='BSD',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        ],
    },
)
