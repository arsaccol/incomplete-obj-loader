#include <vector>
#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>
#include <algorithm>
#include <functional>


//std::vector<std::string> split_string(const std::string& input_str, const std::string& separator)
//{
//    std::vector<std::string> subdivisions;
//    std::stringstream stream{input_str};
//
//    //std::getline(stream, 
//
//    return subdivisions;
//}


struct vector3_t
{
    float x;
    float y;
    float z;
};

struct vector2_t
{
    float x;
    float y;
};

struct model_t
{
    std::vector<vector3_t> positions;
    std::vector<vector3_t> normals;
    std::vector<vector2_t> texture_coords;
    std::vector<int> position_indices;
    std::vector<int> normal_indices;
    std::vector<int> uv_indices;
};


std::string scan_line(const std::string filename)
{
    return "";
}


// parse triangle face line from obj model
// e.g. "f 1/2/3 4/5/6 7/8/9"
// where <number>/<number>/<number> are *indices* for, respectively,
// the vertex position (v), texture coordinates (vt), and the normal (vn)

void parse_face(model_t& model, std::istringstream& rest_of_line_ss)
{
    std::stringstream vertex_indices_stream;

    std::vector<std::string> face_index_strings{
        std::istream_iterator<std::string>{rest_of_line_ss},
            std::istream_iterator<std::string>{}
    };

    for(const std::string& single_vertex_indices : face_index_strings)
    {
        std::stringstream vertex_ss{single_vertex_indices};
        int position, uv, normal; position = uv = normal = -1337;

        auto stream_face_index = [&]() {
            std::string single_index_component;
            std::getline(vertex_ss, single_index_component, '/');
            return std::atoi(single_index_component.c_str());
        };

        position = stream_face_index();
        uv = stream_face_index();
        normal = stream_face_index();

        model.position_indices.push_back(position);
        model.uv_indices.push_back(uv);
        model.normal_indices.push_back(normal);

        std::cout << position << " " << uv << " " << normal << std::endl;
    }
    

    std::cout << "End of face line" << std::endl;
}


// very incorrect but alas
model_t load_obj(std::ifstream& opened_file)
{
    std::string line;

    model_t model;

    std::string vertex_type;
    float x, y, z;

    while(std::getline(opened_file, line))
    {
        std::istringstream iss{line};
        iss >> vertex_type; 

         //comments start with #, ignore them
        if(vertex_type == "#") 
        {
            continue;
        }
        if(vertex_type == "v") 
        {
            iss >> x >> y >> z;

            std::cout << x << " " << y << " " << z << std::endl;

            model.positions.push_back({x, y, z});
        }
        else if (vertex_type == "vn") 
        {
            iss >> x >> y >> z;
            model.normals.push_back({x, y, z});
        }
        else if (vertex_type == "vt") 
        {
            iss >> x >> y;
            model.texture_coords.push_back({x, y});
        }
        else if (vertex_type == "f")
        {
            parse_face(model, iss);
        }
    }

    return model;
}
