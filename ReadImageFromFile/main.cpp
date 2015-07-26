//
//  main.cpp
//  ReadImageFromFile
//
//  Created by zhoushiwei on 15/7/26.
//  Copyright (c) 2015年 zhoushiwei. All rights reserved.
//

#include <iostream>
#include <iostream>
#include <sstream>
#include <filesystem.hpp>
#include <filesystem/fstream.hpp>
#include <filesystem/path.hpp>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
using namespace boost;
using namespace filesystem;
vector<pair<string,string> > ObtainFileFromDir(string directory,vector<string> extensions)
{
        path image_directory(directory);
        vector<pair<string, string>> result;
        
        // does the file exist and is it a directory
        if (exists(image_directory) && is_directory(image_directory))
        {
            
            vector<path> file_in_directory;
            copy(directory_iterator(image_directory), directory_iterator(), back_inserter(file_in_directory));
            
            for (vector<path>::const_iterator file_iterator (file_in_directory.begin()); file_iterator != file_in_directory.end(); ++file_iterator)
            {
                // check if the extension matches the provided list of extensions
                if(std::find(extensions.begin(), extensions.end(), file_iterator->extension().string()) != extensions.end())
                {
                    // First in the pair we store the actual location second we store a parsed name
                    
                    // Parse the name
                    string name = file_iterator->filename().stem().string();
                    
                    // Replace underscores with spaces
                    std::replace(name.begin(), name.end(), '_', ' ');
                    
                    result.push_back(pair<string,string>(file_iterator->string(), name));
                    
                }
            }
        }
        return result;
    }


int main(int argc, const char * argv[]) {
    vector<string> avatar_extensions;
    avatar_extensions.push_back(".jpg");
    avatar_extensions.push_back(".png");
    vector<pair<string,string> > ImageFiles = ObtainFileFromDir("/Users/zhoushiwei/百度云同步盘/DataBase/Emotion6/images/anger", avatar_extensions);
    for (vector<pair<string,string> >::iterator it=ImageFiles.begin(); it!=ImageFiles.end(); it++) {
        Mat img=imread(it->first.c_str());
        printf("%s\n",it->second.c_str());
        cv::imshow("img", img);
        waitKey();
    }
    return 0;
}
