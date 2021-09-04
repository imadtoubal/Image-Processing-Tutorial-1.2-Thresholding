# Thresholding and binary images

This simple project uses OpenCV in C++ to convert grayscale image to a binary image by thresholding wih a variable number $t$.
$$
I_{binary}(x, y) = 
    \begin{cases}
      0, & \text{if}\ I(x, y) > 0 \\
      255, & \text{otherwise}
    \end{cases}

$$

Where $I_{binary}$ is the output binary image and $I$ is the input grayscale image.

The program uses a double for loop to calculate each pixel independently for simplicity. 

## Compiling and running
1. Compile the program using `cmake` and `make`
    
    ```bash
    cmake .
    make
    ```

1. Run the program
    
    ```
    ./gray2binary input_grayscale_image_filename output_binary_image_filename threshold_value input_ground_truth_image
    ```

You can also use the provided `run.sh` file for an example usage of the output program.