import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
from ament_index_python.packages import get_package_share_directory
import os

class CameraValuePublisher(Node):
    def __init__(self):
        super().__init__('camera_return_z_publisher')
        self.publisher_ = self.create_publisher(Float32, 'camera_return_z', 10)
        timer_period = 0.1  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def get_camera_value(self):
        package_share = get_package_share_directory('camera_sensor')
        file_path = os.path.join(package_share, 'camera_z_data', 'camera_z.txt')
        with open(file_path, 'r') as f: 
            value = float(f.read().strip())
            return value

    def timer_callback(self):
        msg = Float32()
        msg.data = self.get_camera_value()
        self.publisher_.publish(msg)
        self.get_logger().info(f'Publishing camera value: {msg.data:.3f}')

def main(args=None):
    rclpy.init(args=args)
    node = CameraValuePublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
