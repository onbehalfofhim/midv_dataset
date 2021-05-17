#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

vector<Point> parser_main(FileNode root) {
	vector<Point> img_xy;

	FileNode region = root["quad"];

	for (int j(0); j < region.size(); ++j) {
		img_xy.push_back(Point(region[j][0],region[j][1]));

		//cout << img_xy[j] << "\n";
	}

	return img_xy;
}


vector<Point> parser(string file_name) {
	vector<Point> img_xy;

	FileStorage fs("../data/" + file_name, 0);

	FileNode region = fs["quad"];

	for (int j(0); j < region.size(); ++j) {
		img_xy.push_back(Point(region[j][0], region[j][1]));

		//cout << img_xy[j];
	}

	return img_xy;
}

Mat homography(string file_name, vector<Point> dst, const Mat& img_filt, const Mat& refer) {
	vector<Point> img_xy;
	img_xy = parser(file_name);

	Mat H = findHomography(img_xy, dst);
	cout << "H:\n" << H << endl;

	Mat transform(img_filt.size(), img_filt.type());
	warpPerspective(img_filt, transform, H, refer.size());

	return transform;
}

Mat crop(size_t i, Mat& photo) {
	FileStorage fs("../data/refer/via_refers.json", 0);

	FileNode name = fs["_via_image_id_list"];
	FileNode root = fs["_via_img_metadata"][name[i].string()]["regions"][0]["shape_attributes"];
	FileNode points_x = root["all_points_x"];
	FileNode points_y = root["all_points_y"];

	vector<Point> xy;
	for (int j(0); j < points_x.size(); ++j) {
		xy.push_back(Point(points_x[j], points_y[j]));
	}

	Mat cropedImage = photo(Rect(xy[3], xy[1]));

	return cropedImage;
}

int main() {
	vector<vector<Point>> ref_xy; //parser_main(fs_ref["photo"]);

	//Mat ref = imread("../data/refer/02.png");
	//Mat ref = imread("../data/refer/03.png");
	//Mat ref = imread("../data/refer/04.png");
	//Mat ref = imread("../data/refer/10.png");
	//Mat ref = imread("../data/refer/14.png");
	//Mat ref = imread("../data/refer/22.png");
	//Mat ref = imread("../data/refer/26.png");
	//Mat ref = imread("../data/refer/31.png");

	vector<String> fn_r;
	glob("../data/refer/*.png", fn_r, false);

	size_t count_r = fn_r.size();
	vector<Mat> ref;
	for (size_t i(0); i < count_r; ++i) {
		ref.push_back(imread(fn_r[i]));
		ref_xy.push_back(vector<Point>{ Point(0, 0), Point(ref[i].cols, 0), Point(ref[i].cols, ref[i].rows), Point(0, ref[i].rows) });
	}

	

	//imgs.push_back(imread("../data/02/02_01.png"));
	//imgs.push_back(imread("../data/02/02_02.png"));
	//imgs.push_back(imread("../data/02/02_03.png"));
	//imgs.push_back(imread("../data/02/02_04.png"));
	//imgs.push_back(imread("../data/02/02_05.png"));
	//imgs.push_back(imread("../data/02/02_06.png"));
	//ref_xy.push_back(Point(0, 0));
	//ref_xy.push_back(Point(460, 0));
	//ref_xy.push_back(Point(460, 290));
	//ref_xy.push_back(Point(0, 290));

	//imgs.push_back(imread("../data/03/03_01.png"));
	//imgs.push_back(imread("../data/03/03_02.png"));
	//imgs.push_back(imread("../data/03/03_03.png"));
	//imgs.push_back(imread("../data/03/03_04.png"));
	//imgs.push_back(imread("../data/03/03_05.png"));
	//ref_xy.push_back(Point(0, 0));
	//ref_xy.push_back(Point(599, 0));
	//ref_xy.push_back(Point(599, 369));
	//ref_xy.push_back(Point(0, 369));
	
	//imgs.push_back(imread("../data/04/04_01.png"));
	//imgs.push_back(imread("../data/04/04_02.png"));
	//imgs.push_back(imread("../data/04/04_03.png"));
	//imgs.push_back(imread("../data/04/04_04.png"));
	//imgs.push_back(imread("../data/04/04_05.png"));
	//imgs.push_back(imread("../data/04/04_06.png"));
	//imgs.push_back(imread("../data/04/04_07.png"));
	//imgs.push_back(imread("../data/04/04_08.png"));
	//imgs.push_back(imread("../data/04/04_09.png"));
	//ref_xy.push_back(Point(0, 0));
	//ref_xy.push_back(Point(504, 0));
	//ref_xy.push_back(Point(504, 318));
	//ref_xy.push_back(Point(0, 318));

	//imgs.push_back(imread("../data/10/10_01.png"));
	//imgs.push_back(imread("../data/10/10_02.png"));
	//imgs.push_back(imread("../data/10/10_03.png"));
	//imgs.push_back(imread("../data/10/10_04.png"));
	//imgs.push_back(imread("../data/10/10_05.png"));
	//imgs.push_back(imread("../data/10/10_06.png"));
	//imgs.push_back(imread("../data/10/10_07.png"));
	//imgs.push_back(imread("../data/10/10_08.png"));
	//ref_xy.push_back(Point(0, 0));
	//ref_xy.push_back(Point(669, 0));
	//ref_xy.push_back(Point(669, 420));
	//ref_xy.push_back(Point(0, 420));

	//imgs.push_back(imread("../data/14/14_01.png"));
	//imgs.push_back(imread("../data/14/14_02.png"));
	//imgs.push_back(imread("../data/14/14_03.png"));
	//imgs.push_back(imread("../data/14/14_04.png"));
	//imgs.push_back(imread("../data/14/14_05.png"));
	//imgs.push_back(imread("../data/14/14_06.png"));
	//imgs.push_back(imread("../data/14/14_07.png"));
	//imgs.push_back(imread("../data/14/14_08.png"));
	//ref_xy.push_back(Point(0, 0));
	//ref_xy.push_back(Point(1000, 0));
	//ref_xy.push_back(Point(1000, 628));
	//ref_xy.push_back(Point(0, 628));

	//imgs.push_back(imread("../data/22/22_01.png"));
	//imgs.push_back(imread("../data/22/22_02.png"));
	//imgs.push_back(imread("../data/22/22_03.png"));
	//imgs.push_back(imread("../data/22/22_04.png"));
	//imgs.push_back(imread("../data/22/22_05.png"));
	//imgs.push_back(imread("../data/22/22_06.png"));
	//imgs.push_back(imread("../data/22/22_07.png"));
	//ref_xy.push_back(Point(0, 0));
	//ref_xy.push_back(Point(584, 0));
	//ref_xy.push_back(Point(584, 371));
	//ref_xy.push_back(Point(0, 371));

	//imgs.push_back(imread("../data/26/26_01.png"));
	//imgs.push_back(imread("../data/26/26_02.png"));
	//imgs.push_back(imread("../data/26/26_03.png"));
	//imgs.push_back(imread("../data/26/26_04.png"));
	//imgs.push_back(imread("../data/26/26_05.png"));
	//imgs.push_back(imread("../data/26/26_06.png"));
	//imgs.push_back(imread("../data/26/26_07.png"));
	//imgs.push_back(imread("../data/26/26_08.png"));
	//ref_xy.push_back(Point(0, 0));
	//ref_xy.push_back(Point(486, 0));
	//ref_xy.push_back(Point(486, 306));
	//ref_xy.push_back(Point(0, 306));

	//imgs.push_back(imread("../data/31/31_01.png"));
	//imgs.push_back(imread("../data/31/31_02.png"));
	//imgs.push_back(imread("../data/31/31_03.png"));
	//imgs.push_back(imread("../data/31/31_04.png"));
	//imgs.push_back(imread("../data/31/31_05.png"));
	//imgs.push_back(imread("../data/31/31_06.png"));
	//imgs.push_back(imread("../data/31/31_07.png"));
	//imgs.push_back(imread("../data/31/31_08.png"));
	//imgs.push_back(imread("../data/31/31_09.png"));
	//imgs.push_back(imread("../data/31/31_10.png"));
	//ref_xy.push_back(Point(0, 0));
	//ref_xy.push_back(Point(3264, 0));
	//ref_xy.push_back(Point(3264, 2049));
	//ref_xy.push_back(Point(0, 2049));

	//FileStorage fs_ref("../data/02/02_aut_drvlic_new.json", 0);


	

	for (size_t f(0); f < 8; ++f) {
		vector<String> fn;
		glob("../data/" + to_string(f + 1) + "/*.png", fn, false);

		vector<Mat> imgs;

		size_t count = fn.size();
		for (size_t i(0); i < count; ++i) {
			imgs.push_back(imread(fn[i]));
		}

		vector<Mat> img_hg;

		for (int i(0); i < imgs.size(); ++i) {
			cout << "Image #" << i << '\n';
			img_hg.push_back(homography(to_string(f + 1) + "/" + to_string(f + 1) + "_" + to_string(i + 1) + ".json", ref_xy[f], imgs[i], ref[f]));

			imwrite(to_string(f + 1) + "_" + to_string(i + 1) + "homo.png", img_hg[i]);

			Mat cut = crop(f, img_hg[i]);

			imwrite(to_string(f + 1) + "_" + to_string(i + 1) + ".png", cut);

			cout << "\n\n";
		}
	}
	

	waitKey(0);
	return 0;
}