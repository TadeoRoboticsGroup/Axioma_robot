from setuptools import setup

package_name = 'axioma_node'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='olmerg',
    maintainer_email='olmerg@gmail.com',
    keywords=['ROS'],
    description='Axioma node. Connect to robot throgh specific serial port',
    license='Apache License, Version 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
             'axioma_node = axioma_node.axioma_node:main',
        ],
    },
)
