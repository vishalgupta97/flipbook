#include<stdlib.h>
#include<stdint.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<iostream>
#include "flipbook.tab.h"
#include "flipbook.h"
#include<assert.h>
#include "matplotlib-cpp/matplotlibcpp.h"
using namespace std;

namespace plt = matplotlibcpp;

int height = 768;
int width = 1024;
int frame_rate = 2;
int total_frames = 4;

class object
{
public:
	string *image_name;
	int start_posx, start_posy, end_posx, end_posy;
	object(string *image_name, int start_posx, int start_posy, int end_posx, int end_posy):image_name(image_name),start_posx(start_posx),start_posy(start_posy),end_posx(end_posx),end_posy(end_posy) {}
};

vector<vector<object> > to_draw; 

unsigned char* readBMP(char* filename, int &fig_width, int &fig_height)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];

    // read the 54-byte header
    fread(info, sizeof(unsigned char), 54, f); 

    // extract image height and width from header
    fig_width = *(int*)&info[18];
    fig_height = *(int*)&info[22];

    // allocate 3 bytes per pixel
    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size];

    // read the rest of the data at once
    fread(data, sizeof(unsigned char), size, f); 
    fclose(f);

    for(i = 0; i < size; i += 3)
    {
            // flip the order of every 3 bytes
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
    }

    return data;
}



void process_base_stmt(FB_stmt *it)
{
		for(auto jt:*(((Base_stmt*)it)->properties))
				{
					cout << jt->pname << endl;
					if(jt->pname == HEIGHT_T)
						height = jt->val1;
					else if(jt->pname == WIDTH_T)
						width = jt->val1;
					else if(jt->pname == FRAME_RATE_T)
						frame_rate = jt->val1;
					else if(jt->pname == TOTAL_FRAMES_T)
						total_frames = jt->val1;
				}
	cout << height << " " << width << " " << frame_rate << " " << total_frames << endl;
				to_draw.resize(total_frames);

}

void process_still_stmt(FB_stmt *it)
{
int frame_start = 1, frame_end = total_frames;
				object curr(NULL, 0,0, height, width);
				for(auto jt:*(((Still_stmt*)it)->properties))
				{
					if(jt->pname == IMAGE_NAME_T)
					{
						cout << "img" << *(jt->str) << endl;
						curr.image_name = jt->str;
					}
					else if(jt->pname == FRAME_START_T)
						frame_start = jt->val1;
					else if(jt->pname == FRAME_END_T)
						frame_end = jt->val1;
					else if(jt->pname == START_POS_T)
					{
						curr.start_posx = jt->val1;
						curr.start_posy = jt->val2;
					}
					else if(jt->pname == END_POS_T)
					{
						curr.end_posx = jt->val1;
						curr.end_posy = jt->val2;
					}
				}
				for(int i = frame_start - 1; i < frame_end; i++)
					to_draw[i].push_back(curr);

}

void process_line_stmt(FB_stmt *it)
{
	int frame_start = 1, frame_end = total_frames;
				object curr(NULL, 0,0, height, width);
				for(auto jt:*(((Line_stmt*)it)->properties))
				{
					if(jt->pname == IMAGE_NAME_T)
					{
						cout << "img" << *(jt->str) << endl;
						curr.image_name = jt->str;
					}
					else if(jt->pname == FRAME_START_T)
						frame_start = jt->val1;
					else if(jt->pname == FRAME_END_T)
						frame_end = jt->val1;
					else if(jt->pname == START_POS_T)
					{
						curr.start_posx = jt->val1;
						curr.start_posy = jt->val2;
					}
					else if(jt->pname == END_POS_T)
					{
						curr.end_posx = jt->val1;
						curr.end_posy = jt->val2;
					}
				}
				int ax = (curr.end_posx - curr.start_posx) / (frame_end - frame_start);
				int ay = (curr.end_posy - curr.start_posy) / (frame_end - frame_start);

				to_draw[frame_start - 1].push_back(curr);
				for(int i = frame_start; i < frame_end; i++)
				{
					curr.start_posx += ax;
					curr.start_posy += ay;
					to_draw[i].push_back(curr);
				}

}

void process_square_stmt(FB_stmt *it)
{
	int frame_start = 1, frame_end = total_frames;
				int centerx = height/2, centery = width/2;
				int side = height/5;
				object curr(NULL, 0,0, height, width);
				for(auto jt:*(((Square_stmt*)it)->properties))
				{
					if(jt->pname == IMAGE_NAME_T)
					{
						cout << "img" << *(jt->str) << endl;
						curr.image_name = jt->str;
					}
					else if(jt->pname == FRAME_START_T)
						frame_start = jt->val1;
					else if(jt->pname == FRAME_END_T)
						frame_end = jt->val1;
					else if(jt->pname == START_POS_T)
					{
						curr.start_posx = jt->val1;
						curr.start_posy = jt->val2;
					}
					else if(jt->pname == SIDE_T)
					{
						side = jt->val1;
					}
				}
				vector<pair<int, int> > locations;
				locations.push_back({curr.start_posx, curr.start_posy});
				locations.push_back({curr.start_posx, curr.start_posy + side});
				locations.push_back({curr.start_posx + side, curr.start_posy + side});
				locations.push_back({curr.start_posx + side, curr.start_posy});
				locations.push_back({curr.start_posx, curr.start_posy});
				to_draw[frame_start - 1].push_back(curr);
				int gap = frame_end - frame_start;
				int frame_number = frame_start;
				for(int i = 1; i < 5; i++)
				{
					for(int j = 0; j < gap/4; j++)
					{
						int ax = (locations[i].first - locations[i-1].first) / (gap/4);
						int ay = (locations[i].second - locations[i-1].second) / (gap/4);
						curr.start_posx += ax;
						curr.start_posy += ay;
						to_draw[frame_number++].push_back(curr);
					}
				}

}
int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		return -1;
	}
	
	int fd = open(argv[1], O_RDONLY);
	struct stat sb;
	fstat(fd, &sb);
	char* memblock = (char*)mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
	
	yyscan_t scanner;
	yylex_init(&scanner);
	yyset_in(fmemopen(memblock, sb.st_size, "r"), scanner);
	vector<FB_stmt*> *list;
	int yacc_err = yyparse(scanner, &list);
	yylex_destroy(scanner);
	if(yacc_err > 0)
	{
		cout << "Parsing Error\n" << endl;
	}
	else
	{
		bool base_done = false;
		for(auto it:*list)
		{
			if(it->type == 1) // Base statement
			{
				process_base_stmt(it);
				base_done = true;
			}
			else if(it->type == 2) //Still statement
			{
				assert(base_done);
				process_still_stmt(it);
			}
			else if(it->type == 3) //Line statement
			{
				assert(base_done);
				process_line_stmt(it);
			}
			else if(it->type == 4) //Square statement
			{
				assert(base_done);
				process_square_stmt(it);
			}
		}
		plt::figure_size(width, height);
		unsigned char* buffer = new unsigned char[3*width*height];
		for(int i = 0 ; i < to_draw.size(); i++)
		{
			cout << "Frame " << i+1 << " objects: " << to_draw[i].size() << endl;
			for(int j = 0; j < 3*width*height; j++)
				buffer[j] = 255;
			cout << "Here" << endl;
			plt::xlim(0,width);
			plt::ylim(0,height);
			for(auto jt: to_draw[i])
			{
				if(jt.image_name == NULL)
				{
					cout << "No image" << endl;
					continue;
				}
				cout << "here1" << endl;
				cout << *(jt.image_name) << jt.start_posy << " " << jt.start_posx << endl;
				cout << "here2" << endl;
				int fig_width = 0, fig_height = 0;
				char *filename = new char[jt.image_name->size()+1];
				strcpy(filename, jt.image_name->c_str());
				cout << "Read bmp: " << endl;
				unsigned char* fig_data = readBMP(filename, fig_width, fig_height);				
				cout << "Read bmp : " << fig_width << " " << fig_height << endl;
				int temp_pos = 0;
				for(int j = 0; j < fig_height; j++)
				{
					int cur_pos = ((jt.start_posy+j)*width*3+jt.start_posx*3);
					for(int k = 0; k < 3*fig_width; k++)
					{
							buffer[cur_pos+k] = fig_data[temp_pos++];
					}
				}
				delete(fig_data);
				//plt::imshow(fig_data, fig_height, fig_width, 3);
				cout << "Copied to buffer " << endl;
			}
			plt::imshow(buffer,height,width,3);
			plt::save(string("frame"+to_string(1000+i)).c_str());
			plt::cla();
			plt::clf();	
		}
	}	
}



















