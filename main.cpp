#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>

// all from ML
#include "../graph.h"
#include "../matrix.h"
#include "../dataset.h"
#include "../k-means.h"

using namespace std;



vector<Mat> getImageChannels(const string& src) {
	olc::Sprite sprite;

	if (!sprite.LoadFromFile(src)) {
		return vector<Mat>();
	}

	int w = sprite.width;
	int h = sprite.height;

	vector<Mat> channels(3, Mat(h, w));

	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			olc::Pixel pixel = sprite.GetPixel(x, y);

			channels[0][y][x] = pixel.r;
			channels[1][y][x] = pixel.g;
			channels[2][y][x] = pixel.b;
		}
	}

	return channels;
}






int main() {

	Graph graph;

	string src;
	int k = 5;

	cout << "Image src: ";
	cin >> src;
	cout << "\n";

	cout << "Number of colors: ";
	cin >> k;
	cout << "\n";

	vector<Mat> channels = getImageChannels(src);

	Dataset img;
	for (size_t i = 0; i < channels[0].row; ++i) {
		for (size_t j = 0; j < channels[0].col; ++j) {
			img.add(DataPoint(Vec({ channels[0][i][j], channels[1][i][j], channels[2][i][j] })));
		}
	}


	Kmeans model(k);

	// only apply k-means on a subset of the dataset
	Dataset sample = Dataset::sample(img, 1000);


	model.fit(sample);


	olc::Sprite sprite(channels[0].col, channels[0].row);
	for (size_t i = 0; i < channels[0].row; ++i) {
		for (size_t j = 0; j < channels[0].col; ++j) {

			Vec color = model.centroids[Vec::argmax(model.predict(img[i * channels[0].col + j].x))];

			sprite.SetPixel(j, i, olc::Pixel(color[0], color[1], color[2]));
		}
	}

	// display the color-quantized image
	graph.addImage(&sprite, 0, 0, 1, 1);

	// waits untill the user closes the graph
	graph.waitFinish();

	return 0;
}
