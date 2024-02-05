# Color Quantization
Simple implementation of color quantization using k-means.

The idea is that every pixel on the screen will be a 3 dimensional data point with it's coordinates being it's rgb value. We can than apply the k-means algorithm on the dataset with k being the number of colors we want in the color-quantized image, and it will find clusters of the most important colors. The centroids of the clusters will be the quantized colors, and to get the color-quantized image we can set each pixel color to be the coordinates of it's cluster's centroid.
